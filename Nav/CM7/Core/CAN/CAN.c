/*
 * CAN.c
 *
 *  Created on: Jun 29, 2025
 *      Author: ximen
 */

#include "CAN.h"
#include "main.h"
#include "stdio.h"

int CAN_Init(CAN_Init_Typedef *init)
{
    // Configuración del handle de FDCAN, se asume ya inicializado externamente
    FDCAN_HandleTypeDef *hfdcan = init->hfdcan;

    if (HAL_FDCAN_Start(hfdcan) != HAL_OK)
    {
        return -1;
    }

    if (init->interrupt_enable)
    {
        if (HAL_FDCAN_ActivateNotification(hfdcan, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0) != HAL_OK)
        {
            return -1;
        }
    }

    return 1;
}

int CAN_Filter_Init(CAN_Init_Typedef *init, CAN_Filter_TypeDef *filter)
{
    FDCAN_FilterTypeDef sFilterConfig = {0};

    sFilterConfig.IdType = (filter->id_type == CAN_ID_STANDARD) ? FDCAN_STANDARD_ID : FDCAN_EXTENDED_ID;
    sFilterConfig.FilterIndex = filter->bank_id;
    sFilterConfig.FilterType = (filter->type == CAN_FILTER_MASK_MODE) ? FDCAN_FILTER_MASK : FDCAN_FILTER_RANGE;
    sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;

    if (filter->id_type == CAN_ID_STANDARD)
    {
        sFilterConfig.FilterID1 = filter->ID << 5;
        sFilterConfig.FilterID2 = filter->ID << 5;
    }
    else
    {
        sFilterConfig.FilterID1 = filter->ID << 3;
        sFilterConfig.FilterID2 = filter->ID << 3;
    }

    if (HAL_FDCAN_ConfigFilter(init->hfdcan, &sFilterConfig) != HAL_OK)
    {
        return -1;
    }

    return 1;
}

void CAN_Start(CAN_Init_Typedef *init)
{
    // Ya lo hace CAN_Init con HAL_FDCAN_Start
}

void CAN_Send_Packet(CAN_Init_Typedef *init, CAN_TX_Typedef *tx)
{
    FDCAN_TxHeaderTypeDef TxHeader = {0};

    TxHeader.IdType = (tx->id_type == CAN_ID_STANDARD) ? FDCAN_STANDARD_ID : FDCAN_EXTENDED_ID;
    TxHeader.Identifier = tx->ID;
    TxHeader.TxFrameType = (tx->frame_type == CAN_FRAME_REMOTE) ? FDCAN_REMOTE_FRAME : FDCAN_DATA_FRAME;
    TxHeader.DataLength = tx->data_length << 16; // DLC codificado
    TxHeader.BitRateSwitch = FDCAN_BRS_OFF;
    TxHeader.FDFormat = FDCAN_CLASSIC_CAN;
    TxHeader.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
    TxHeader.MessageMarker = 0;

    if (HAL_FDCAN_AddMessageToTxFifoQ(init->hfdcan, &TxHeader, tx->data) != HAL_OK)
    {
        printf("Error sending CAN frame\r\n");
    }
}

int CAN_Get_Packet(CAN_Init_Typedef *init, CAN_RX_Typedef *rx)
{
    FDCAN_RxHeaderTypeDef RxHeader = {0};

    if (HAL_FDCAN_GetRxMessage(init->hfdcan, FDCAN_RX_FIFO0, &RxHeader, rx->data) != HAL_OK)
    {
        return 0; // No message
    }

    rx->ID = RxHeader.Identifier;
    rx->id_type = (RxHeader.IdType == FDCAN_STANDARD_ID) ? CAN_ID_STANDARD : CAN_ID_EXTENDED;
    rx->frame_type = (RxHeader.RxFrameType == FDCAN_REMOTE_FRAME) ? CAN_FRAME_REMOTE : CAN_FRAME_DATA;
    rx->data_length = (RxHeader.DataLength >> 16) & 0xF;

    return 1;
}



