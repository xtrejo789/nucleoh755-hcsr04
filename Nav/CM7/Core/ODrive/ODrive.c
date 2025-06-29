/*
 * ODrive.c
 *
 *  Created on: Jun 29, 2025
 *      Author: ximen
 */

#include "ODrive.h"
CAN_RX_Typedef RX;

void CAN_Setup(FDCAN_HandleTypeDef *hfdcan, int32_t baudrate_prescaler) {
    hfdcan->Init.FrameFormat = FDCAN_FRAME_CLASSIC;
    hfdcan->Init.Mode = FDCAN_MODE_NORMAL;
    hfdcan->Init.AutoRetransmission = DISABLE;
    hfdcan->Init.TransmitPause = DISABLE;
    hfdcan->Init.ProtocolException = ENABLE;
    hfdcan->Init.NominalPrescaler = baudrate_prescaler;
    hfdcan->Init.NominalSyncJumpWidth = 8;
    hfdcan->Init.NominalTimeSeg1 = 0x1F;
    hfdcan->Init.NominalTimeSeg2 = 8;
    hfdcan->Init.DataPrescaler = 1;
    hfdcan->Init.DataSyncJumpWidth = 1;
    hfdcan->Init.DataTimeSeg1 = 1;
    hfdcan->Init.DataTimeSeg2 = 1;
    hfdcan->Init.StdFiltersNbr = 1;
    hfdcan->Init.ExtFiltersNbr = 0;
    hfdcan->Init.RxFifo0ElmtsNbr = 1;
    hfdcan->Init.RxFifo0ElmtSize = FDCAN_DATA_BYTES_8;
    hfdcan->Init.TxFifoQueueElmtsNbr = 1;
    hfdcan->Init.TxElmtSize = FDCAN_DATA_BYTES_8;

    if (HAL_FDCAN_Init(hfdcan) != HAL_OK) {
        Error_Handler();
    }

    FDCAN_FilterTypeDef sFilterConfig;
    sFilterConfig.IdType = FDCAN_STANDARD_ID;
    sFilterConfig.FilterIndex = 0;
    sFilterConfig.FilterType = FDCAN_FILTER_MASK;
    sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
    sFilterConfig.FilterID1 = 0x000;
    sFilterConfig.FilterID2 = 0x000;

    HAL_FDCAN_ConfigFilter(hfdcan, &sFilterConfig);
    HAL_FDCAN_Start(hfdcan);
    HAL_FDCAN_ActivateNotification(hfdcan, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0);
}

void Set_TX_Header(Axis Axis, uint32_t command, uint8_t len, uint32_t frame_type) {
    TxHeader.Identifier = (Axis.AXIS_ID << 5) | command;
    TxHeader.IdType = FDCAN_STANDARD_ID;
    TxHeader.TxFrameType = frame_type;
    TxHeader.DataLength = (len << 16);
    TxHeader.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
    TxHeader.BitRateSwitch = FDCAN_BRS_ON;
    TxHeader.FDFormat = FDCAN_FD_CAN;
    TxHeader.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
    TxHeader.MessageMarker = 0;
}

void Set_Controller_Modes(Axis Axis, Control_Mode ControlMode, Input_Mode InputMode) {
    Set_TX_Header(Axis, SET_CONTROLLER_MODES, 8, FDCAN_DATA_FRAME);
    memcpy(TxData, &ControlMode, 4);
    memcpy(TxData + 4, &InputMode, 4);
    HAL_FDCAN_AddMessageToTxFifoQ(Axis.hfdcan, &TxHeader, TxData);
}

void Set_Axis_Requested_State(Axis Axis, Axis_State state) {
    Set_TX_Header(Axis, SET_AXIS_REQUESTED_STATE, 4, FDCAN_DATA_FRAME);
    memcpy(TxData, &state, 4);
    HAL_FDCAN_AddMessageToTxFifoQ(Axis.hfdcan, &TxHeader, TxData);
}

void Set_Input_Vel(Axis Axis, float vel, float torqueff) {
    Set_TX_Header(Axis, SET_INPUT_VEL, 8, FDCAN_DATA_FRAME);
    memcpy(TxData, &vel, 4);
    memcpy(TxData + 4, &torqueff, 4);
    HAL_FDCAN_AddMessageToTxFifoQ(Axis.hfdcan, &TxHeader, TxData);
}

void Clear_Errors(Axis Axis) {
    Set_TX_Header(Axis, CLEAR_ERRORS, 0, FDCAN_DATA_FRAME);
    HAL_FDCAN_AddMessageToTxFifoQ(Axis.hfdcan, &TxHeader, TxData);
}

void ODrive_RX_CallBack(Axis *AXIS) {
    if (HAL_FDCAN_GetRxMessage(AXIS->hfdcan, FDCAN_RX_FIFO0, &RxHeader, RxData) == HAL_OK) {
        uint32_t ID = RxHeader.Identifier;
        uint32_t NODE_ID = (ID >> 5);
        uint32_t CMD_ID = (ID & 0x1F);

        if (NODE_ID == AXIS->AXIS_ID) {
            switch (CMD_ID) {
                case ODRIVE_HEARTBEAT_MESSAGE:
                    memcpy(&AXIS->AXIS_Error, &RxData[0], 4);
                    AXIS->AXIS_Current_State = RxData[4];
                    AXIS->Controller_Status = RxData[5];
                    break;
                case ENCODER_ESTIMATES:
                    memcpy(&AXIS->AXIS_Encoder_Pos, &RxData[0], 4);
                    memcpy(&AXIS->AXIS_Encoder_Vel, &RxData[4], 4);
                    break;
            }
        }
    }
}
