/*
 * schm_types.h
 *
 *  Created on: May 15, 2019
 *      Author: dumitru
 */

#ifndef SCHM_TYPES_H_
#define SCHM_TYPES_H_

#include <stdint.h>
#include <stdbool.h>
#include <AUTOSAR31/Std_Types.h>
#include "Fls/fls_types.h"

#define SCH_REQUEST_QUEUE_EMPTY      0x10
#define SCH_REQUEST_QUEUE_FULL       0x11

#define SCH_REQUEST_ERROR            0x20

#define SCH_MAX_QUEUE_SIZE           0x05
#define SCH_INVALID_REQUEST_ID       0xFF

typedef enum
{
    enUndefined = 0,
    enIdle,
    enWaitingFlashing,
    enErasing,
    enReprog,
    enAppRun
}BOOT_STATE;

typedef enum
{
    enSch_Queue_Empty = 0,
    enSch_Queue_Normal,
    enSch_Queue_Full
}SchRequestsQueueStateType;

typedef enum
{
    enNoRequest = 0,
    enReprogRequest,
    enEraseRequest,
    enWaitFlashing
}BootRequestType;

typedef struct
{
    uint16_t reprogAddr;
    uint8_t* reprogData;
    uint16_t reprogDataSize;
    FlashDataType dataType;
}BootRequestInfo;

typedef struct
{
    BootRequestType type;
    BootRequestInfo requestInfo;
    bool newRequest;
    bool requestActive;
    uint8_t requiestId;
}BootRequest_t;


typedef struct
{
    void (*InitHook)(void);
    void (*ShutdownHook)(void);
    void (*ErrorHook)(void);
}SchMConfigType;


typedef struct
{
    BootRequest_t Requests[SCH_MAX_QUEUE_SIZE];
    uint8_t nextFreeRequest;
    uint8_t currentRequest;
    uint8_t requestsInQueue;
    SchRequestsQueueStateType queueState;
    uint8_t requestId;
}SchBootQueueType;

#endif /* SCHM_TYPES_H_ */
