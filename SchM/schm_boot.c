/*
 * schm_boot.c
 *
 *  Created on: May 15, 2019
 *      Author: dumitru
 */

#include "schm_boot.h"
#include "schm_types.h"
#include "Fls/fls_main.h"
#include "SchM_cfg.h"

#include "Timer/Timer.h"

static BOOT_STATE __boot_state__ = enUndefined;

SchBootQueueType SchBootQueue;


static void SetBootState(BOOT_STATE state)
{
    __boot_state__ = state;
}


BOOT_STATE GetBootState(void)
{
    return __boot_state__;
}


void SetBootRequest(BootRequestType type, uint16_t addr, uint8_t* data, FlashDataType dataType, uint16_t dataSize)
{

    BootRequest_t* nextFreeRequest;

    if (SchBootQueue.requestsInQueue != SCH_MAX_QUEUE_SIZE){
        nextFreeRequest = &SchBootQueue.Requests[SchBootQueue.nextFreeRequest];
        SchBootQueue.requestsInQueue++;
        SchBootQueue.nextFreeRequest++;

        nextFreeRequest->newRequest = TRUE;
        nextFreeRequest->requestActive = FALSE;
        nextFreeRequest->type = type;
        nextFreeRequest->requestInfo.reprogAddr = addr;
        nextFreeRequest->requestInfo.reprogDataSize = dataSize;
        nextFreeRequest->requestInfo.reprogData = data;
        nextFreeRequest->requestInfo.dataType = dataType;
    }
}

uint8_t GetCurrentRequestFromQueue(BootRequest_t **pNextRequest)
{
    uint8_t result = SCH_REQUEST_ERROR;
    uint8_t inQueue = SchBootQueue.requestsInQueue;

    if (0 != inQueue)
    {
        if (inQueue < (uint8_t)SCH_MAX_QUEUE_SIZE)
        {
            *pNextRequest = &(SchBootQueue.Requests[SchBootQueue.currentRequest]);
            result = E_OK;
        }
        else
        {
            result = SCH_REQUEST_QUEUE_FULL;
        }
    }
    else
    {
        result = SCH_REQUEST_QUEUE_EMPTY;
    }

    return result;
}


static void Sch_ClearQueue(void)
{
    uint8_t index;

    for (index = sizeof(SchBootQueueType); index > 0 ; index--)
    {
        ((uint8_t*)&SchBootQueue)[index-1] = 0x00;
    }
}


void ClearBootRequest(BootRequest_t* request)
{
    uint8_t index;

    for (index = sizeof(BootRequest_t); index > 0 ; index--)
    {
        ((uint8_t*)request)[index-1] = 0x00;
    }
    if (SchBootQueue.requestsInQueue > 0)
    {
        SchBootQueue.requestsInQueue--;
    }

    if (SchBootQueue.requestsInQueue != 0)
    {
        SchBootQueue.currentRequest = (SchBootQueue.currentRequest+1)%SCH_MAX_QUEUE_SIZE;
    }
}


void SchM_InitPlatform(void)
{
    SetBootState(enIdle);
    Sch_ClearQueue();
    if(SchM_BootCfg.InitHook != NULL_PTR)
    {
        SchM_BootCfg.InitHook();
    }
}


void SchM_MainFunction(void)
{
    static uint8_t previousValue = 0;
    uint8_t reqState;
    uint8_t tmp;
    uint8_t milis = GetMilliseconds();
    BootRequest_t* lRequest = NULL_PTR;
    BootRequestInfo *lReqInfo = NULL_PTR;

    /* check if 10 milliseconds are passed */
    if (previousValue + 10 >= milis)
    {
        tmp = GetCurrentRequestFromQueue(&lRequest);
        if (E_OK == tmp)
        {
            lReqInfo = &lRequest->requestInfo;
            if(lRequest->newRequest)
            {
                switch (lRequest->type) {
                case enEraseRequest:
                    SetBootState(enErasing);
                    /* Memory erase request */
                    if (E_OK == Fls_SetEraseRequest(lRequest->requestInfo.reprogAddr, &lRequest->requiestId))
                    {
                        lRequest->requestActive = true;
                    }
                    break;
                case enReprogRequest:
                    SetBootState(enReprog);
                    /* Writing to flash starts here */
                    tmp = Fls_SetWriteRequest(lReqInfo->reprogAddr, lReqInfo->reprogData, lReqInfo->dataType, lReqInfo->reprogDataSize, &lRequest->requiestId);

                    if (E_OK == tmp)
                    {
                        lRequest->requestActive = true;
                    }
                    else if (enAppRun == GetBootState())
                    {
                        /* ToDo: 2 requests should be left here for erase and flash */
                    }
                    break;
                default:
                    break;
                }
                lRequest->newRequest = false;
            }
        }

        if (true == lRequest->requestActive)
        {
            reqState = Fls_GetRequestStatus(lRequest->requiestId);

            switch (reqState) {

            case FLS_REQUEST_NOT_FIND:
            case FLS_REQUEST_FAILED:
                lRequest->requestActive = false;
                lRequest->type = enNoRequest;
                /* ToDo: General request error handler should be implemented */
                break;

            case FLS_REQUEST_SUCCESS:
                ClearBootRequest(lRequest);
                break;

            case FLS_REQUEST_BUSY:
            case FLS_REQUEST_NOT_STARTED:
            case FLS_REQUEST_STARTED:
            default:
                break;
            }
        }
        previousValue = milis;
    }
    else
    {

    }
}
