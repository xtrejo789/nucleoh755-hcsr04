/*
 * CAN.h
 *
 *  Created on: Jun 29, 2025
 *      Author: ximen
 */

#ifndef SRC_CAN_CAN_H_
#define SRC_CAN_CAN_H_

#include "main.h"
#include "CAN_defines.h"

typedef struct {
	int message_timestamp;
	int data_length;
	uint8_t data[8];
	int filter_index;
	int frame_type;
	int id_type;
	uint32_t ID;
} CAN_RX_Typedef;

typedef struct {
	uint32_t ID;
	int id_type;
	int frame_type;
	int data_length;
	uint8_t data[8];
} CAN_TX_Typedef;

typedef struct {
	uint32_t filter_id;
	int enable;
	int id_type;
	int frame_type;
	int type;
	int scale;
	int bank_id;
	uint32_t ID;
} CAN_Filter_TypeDef;

typedef struct {
	FDCAN_HandleTypeDef *hfdcan;   // Puntero al handle de FDCAN
	uint32_t baudrate_prescaler;
	uint32_t sync_jump_width;
	uint32_t time_seg1;
	uint32_t time_seg2;
	int timestamp_enable;
	int interrupt_enable;
} CAN_Init_Typedef;

int CAN_Init(CAN_Init_Typedef *init);
int CAN_Filter_Init(CAN_Init_Typedef *init, CAN_Filter_TypeDef *filter);
void CAN_Start(CAN_Init_Typedef *init);
void CAN_Send_Packet(CAN_Init_Typedef *init, CAN_TX_Typedef *tx);
int CAN_Get_Packet(CAN_Init_Typedef *init, CAN_RX_Typedef *rx);

#endif /* SRC_CAN_CAN_H_ */
