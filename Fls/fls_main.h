/*
 * fls_main.h
 *
 *  Created on: Apr 11, 2019
 *      Author: dumitru
 */

#ifndef FLS_FLS_MAIN_H_
#define FLS_FLS_MAIN_H_

#include <AUTOSAR31/Std_Types.h>
#include "fls_types.h"


#define FLS_REQUEST_QUEUE_EMPTY      0x10
#define FLS_REQUEST_QUEUE_FULL       0x11

#define FLS_REQUEST_SUCCESS          0x00
#define FLS_REQUEST_BUSY             0x01
#define FLS_REQUEST_FAILED           0x02
#define FLS_REQUEST_NOT_FIND         0x03
#define FLS_REQUEST_STARTED          0x04
#define FLS_REQUEST_NOT_STARTED      0x05


#define FLS_INVALID_REQUEST_ID       0xFF

extern FlashConfigType globalFlashCfg;

void Fls_Init(FlashConfigType* config);
Std_ReturnType Fls_SetEraseRequest(uint16_t addr, uint8_t* requestId);
Std_ReturnType Fls_SetWriteRequest(uint16_t addr, uint8_t* wordsToWrite, FlashDataType data_type, uint16_t blockSize, uint8_t* requestId);
void Fls_MainFunction(void);
uint8_t Fls_GetRequestStatus(uint8_t reqId);

#endif /* FLS_FLS_MAIN_H_ */
