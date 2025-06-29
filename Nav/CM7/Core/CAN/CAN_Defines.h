#ifndef CAN_DEFINES_H_
#define CAN_DEFINES_H_

#include "main.h"

/***** Configuración de Baudrate para FDCAN basado en fCAN = 40 MHz *****/

/* Estructura combinada: (NominalPrescaler << 16) | ((TimeSeg1 - 1) << 8) | (TimeSeg2 - 1) */

#define CAN_BAUDRATE_500_KBPS   0x0002001F  // Prescaler = 2, TimeSeg1 = 31, TimeSeg2 = 8
#define CAN_BAUDRATE_250_KBPS   0x0004001F  // Prescaler = 4, TimeSeg1 = 31, TimeSeg2 = 8
#define CAN_BAUDRATE_125_KBPS   0x0008001F  // Prescaler = 8, TimeSeg1 = 31, TimeSeg2 = 8

/***** Tipos de Frame (Adaptado a FDCAN) *****/
#define CAN_FRAME_DATA      FDCAN_DATA_FRAME
#define CAN_FRAME_REMOTE    FDCAN_REMOTE_FRAME

/***** Tipos de ID (Adaptado a FDCAN) *****/
#define CAN_ID_STANDARD     FDCAN_STANDARD_ID
#define CAN_ID_EXTENDED     FDCAN_EXTENDED_ID

/***** Configuración de Filtros (Adaptado a FDCAN) *****/
#define CAN_FILTER_MASK_MODE        FDCAN_FILTER_MASK
#define CAN_FILTER_LIST_MODE        FDCAN_FILTER_LIST
#define CAN_GLOBAL_FILTER_REJECT    FDCAN_REJECT
#define CAN_GLOBAL_FILTER_ACCEPT    FDCAN_ACCEPT_IN_RX_FIFO0

/***** Configuración de Transmisión (Adaptado a FDCAN) *****/
#define CAN_ESI_ACTIVE      FDCAN_ESI_ACTIVE
#define CAN_BRS_ON          FDCAN_BRS_ON
#define CAN_FD_CAN          FDCAN_FD_CAN
#define CAN_NO_TX_EVENTS    FDCAN_NO_TX_EVENTS

#endif /* CAN_DEFINES_H_ */
