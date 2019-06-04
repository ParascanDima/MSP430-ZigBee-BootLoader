/*
 * fls_main.c
 *
 *  Created on: Apr 11, 2019
 *      Author: dumitru
 */

#include "fls_main.h"
#include "fls_hw.h"

#define FLS_QUEUE_LENGTH  5

typedef enum
{
    enFlsNoReqActive = 0,
    enFlsEraseReq,
    enFlsWriteReq,
}FlsReqType;


typedef struct{
    uint16_t *wordsArray;
    uint8_t dataArraySize;
    FlsReqType type;

    uint16_t addrToWrite;
    union{
        uint8_t *activeU8Ptr;
        uint16_t *activeU16Ptr;
    }cast;
    FlashDataType dataType;
    bool isActiveRequest;
    uint8_t reqID;
    uint8_t reqStatus;
}FlashReqInstType;


typedef struct
{
    FlashReqInstType Requests[FLS_QUEUE_LENGTH];
    uint8_t executingRequest;
    uint8_t nextFree;
    uint8_t queueState;
    uint8_t requestsInQueue;
}FlashRequestQueueType;

FlashRequestQueueType MainRequestQueue;
FlashConfigType* FLS_MainConfigPtr;

uint8_t totalRequests;


Std_ReturnType Fls_AddRequestToQueue(FlashReqInstType* request)
{
    Std_ReturnType result = E_OK;

    if (MainRequestQueue.requestsInQueue < FLS_QUEUE_LENGTH)
    {
        MainRequestQueue.Requests[MainRequestQueue.nextFree] = *request;
        MainRequestQueue.nextFree++;
        MainRequestQueue.requestsInQueue++;
        if (MainRequestQueue.nextFree == FLS_QUEUE_LENGTH)
        {
            MainRequestQueue.nextFree = 0;
        }
        if (totalRequests == FLS_INVALID_REQUEST_ID-1)
        {
            totalRequests = 0;
        }
        else
        {
            totalRequests++;
        }
    }
    else
    {
        MainRequestQueue.queueState = FLS_REQUEST_QUEUE_FULL;
        result = E_NOT_OK;
    }

    return result;
}


void FlsResetReqInstance(void)
{
    FlashReqInstType* lRequest;

    if (MainRequestQueue.requestsInQueue != 0)
    {
        lRequest = &MainRequestQueue.Requests[MainRequestQueue.executingRequest];

        lRequest->cast.activeU16Ptr = NULL_PTR;
        lRequest->addrToWrite = 0;
        lRequest->wordsArray = NULL_PTR;
        lRequest->dataArraySize = 0;
        lRequest->type = enFlsNoReqActive;
        lRequest->isActiveRequest = false;
        lRequest->dataType = enUINT8;

        if (MainRequestQueue.nextFree == FLS_QUEUE_LENGTH-1)
        {
            MainRequestQueue.nextFree = 0;
        }

        MainRequestQueue.requestsInQueue--;
    }
}

uint8_t Fls_GetNextRequest(FlashReqInstType** nextRequest)
{
    uint8_t retVal = E_OK;

    if(MainRequestQueue.requestsInQueue != 0)
    {
        if (MainRequestQueue.executingRequest < FLS_QUEUE_LENGTH-1)
        {
            *nextRequest = &MainRequestQueue.Requests[MainRequestQueue.executingRequest];
            (void)nextRequest;
        }
    }
    else
    {
        retVal = FLS_REQUEST_QUEUE_EMPTY;
    }
    return retVal;
}

void Fls_Init(FlashConfigType* config)
{
    Fls_HwInit(config->ClkDiv, config->source);
    totalRequests = 0;
    FlsResetReqInstance();
    MainRequestQueue.requestsInQueue = 0;
    FLS_MainConfigPtr = config;
}

void Fls_EraseSegment(uint16_t addrInSegment)
{
    uint8_t clockDiv = Fls_GetClkDiv();
    FlsClkSourceEnum clkSource = Fls_GetClkSource();

    /* Configure low frequency for flash driver */
    Fls_SetClkSource(enSMCLK);
    Fls_SetClkDiv(13);
    /* Entering critiacal section */
    FLS_MainConfigPtr->EnterCriticalSection();
    /* Unlock the flash write */
    ReleaseFlashWLock();
    /* Perform dummy write in segment boundaries */
    Fls_EnableErase();
    *(uint16_t*)addrInSegment = 0xAAAA;
    /* Lock flash from write/erase */
    SetFlashWLock();
    /* Exit critiacal section */
    FLS_MainConfigPtr->ExitCriticalSection();
    /* Set flash driver clock configuration back to initialized */
    Fls_SetClkSource(clkSource);
    Fls_SetClkDiv(clockDiv);
}

#pragma CODE_SECTION(Fls_Write, ".TI.ramfunc")
void Fls_Write(FlashReqInstType *pReqInst)
{
    uint8_t dataRemains;
    uint8_t clockDiv = Fls_GetClkDiv();
    FlsClkSourceEnum clkSource = Fls_GetClkSource();

    /* Configure low frequency for flash driver */
    Fls_SetClkSource(enSMCLK);
    Fls_SetClkDiv(13);

    /* Entering critiacal section */
    FLS_MainConfigPtr->EnterCriticalSection();
    if (FLS_REQUEST_NOT_STARTED == pReqInst->reqStatus)
    {
        ReleaseFlashWLock();
        if (pReqInst->dataArraySize > 1)
        {
            switch (pReqInst->dataType) {
            case enUINT8:
                dataRemains = pReqInst->dataArraySize;
                break;
            case enUINT16:
                dataRemains = pReqInst->dataArraySize;
                EnableFlashBlockWrite();
                break;
            case enUINT32:
                dataRemains = pReqInst->dataArraySize*2;
                EnableFlashBlockWrite();
                break;
            default:
                SetFlashWLock();
                return;
            }
        }
        EnableFlashWrite();

        pReqInst->reqStatus = FLS_REQUEST_STARTED;
    }

    while ( dataRemains != 0)
    {
        if (true == isAccessViolated())
        {
            pReqInst->reqStatus = FLS_REQUEST_FAILED;
            break;
        }
        if (pReqInst->dataType == enUINT8)
        {
            ((uint8_t*)pReqInst->addrToWrite)[pReqInst->dataArraySize-dataRemains] = *(pReqInst->cast.activeU8Ptr++);
        }
        else
        {
            *(uint16_t*)(pReqInst->addrToWrite) = *(pReqInst->cast.activeU16Ptr++);
            pReqInst->addrToWrite += 2;
        }
        dataRemains--;
        while (!IsFlsWaiting());
    }
    DisableFlashBlockWrite();
    while(IsFlashControllerBusy());
    DisableFlashWrite();
    SetFlashWLock();
    /* Exit critiacal section */
    FLS_MainConfigPtr->ExitCriticalSection();
    /* Set flash driver clock configuration back to initialized */
    Fls_SetClkSource(clkSource);
    Fls_SetClkDiv(clockDiv);
}


void Fls_MainFunction(void)
{
    FlashReqInstType* nextReq;
    static bool isErrorHandled = false;

    if (FLS_REQUEST_QUEUE_FULL != Fls_GetNextRequest(&nextReq))
    {
        if (nextReq->isActiveRequest == true && false == IsFlashControllerBusy() && false == isAccessViolated())
        {
            isErrorHandled = false;
            switch(nextReq->type)
            {
            case enFlsWriteReq:
                Fls_Write(nextReq);
                nextReq->reqStatus = FLS_REQUEST_SUCCESS;
                break;

            case enFlsEraseReq:
                Fls_EraseSegment(nextReq->addrToWrite);
                nextReq->reqStatus = FLS_REQUEST_SUCCESS;
                break;

            default:
                break;
            }
        }
    }


    if (true == isAccessViolated() && false == isErrorHandled)
    {
        nextReq->reqStatus = FLS_REQUEST_FAILED;
        /* Call the error routine */
        isErrorHandled = true;
    }
}


uint8_t Fls_GetRequestStatus(uint8_t reqId)
{
    uint8_t index;
    bool clearRequestFlag = false;
    uint8_t status = FLS_REQUEST_NOT_FIND;

    for (index = 0; index < FLS_QUEUE_LENGTH; ++index)
    {
        if (MainRequestQueue.Requests[index].reqID == reqId)
        {
            if (true == MainRequestQueue.Requests[index].isActiveRequest && FLS_REQUEST_SUCCESS != MainRequestQueue.Requests[index].reqStatus)
            {
                status = FLS_REQUEST_BUSY;
            }
            else if (FLS_REQUEST_SUCCESS != MainRequestQueue.Requests[index].reqStatus)
            {
                status = FLS_REQUEST_FAILED;
            }
            else
            {
                clearRequestFlag = true;
                status = MainRequestQueue.Requests[index].reqStatus;
            }
            break;
        }
    }

    if (true == clearRequestFlag)
    {
        FlsResetReqInstance();
        MainRequestQueue.executingRequest++;
    }

    return status;
}


Std_ReturnType Fls_SetWriteRequest(uint16_t addr, uint8_t* wordsToWrite, FlashDataType data_type, uint16_t blockSize, uint8_t* requestId)
{
    Std_ReturnType retVal = E_NOT_OK;
    FlashReqInstType lRequest;

    if (false == IsFlashControllerBusy())
    {
        if (wordsToWrite != NULL_PTR)
        {
            if (blockSize != 0)
            {
                lRequest.wordsArray = (uint16_t*)wordsToWrite;
                lRequest.cast.activeU8Ptr = wordsToWrite;
                lRequest.addrToWrite = addr;
                lRequest.dataArraySize = blockSize;
                lRequest.dataType = data_type;
                lRequest.type = enFlsWriteReq;
                lRequest.isActiveRequest = true;
                lRequest.reqStatus = FLS_REQUEST_NOT_STARTED;
                lRequest.reqID = totalRequests;
                *requestId = totalRequests;

                Fls_AddRequestToQueue(&lRequest);
                retVal = E_OK;
            }
        }
    }
    return retVal;
}


Std_ReturnType Fls_SetEraseRequest(uint16_t addr, uint8_t* requestId)
{
    Std_ReturnType retVal = E_NOT_OK;
    FlashReqInstType lRequest;

    if (false == IsFlashControllerBusy())
    {
        if (addr != 0)
        {
            lRequest.addrToWrite = addr;
            lRequest.type = enFlsEraseReq;
            lRequest.isActiveRequest = true;
            *requestId = totalRequests;

            Fls_AddRequestToQueue(&lRequest);
            retVal = E_OK;
        }
    }


    return retVal;
}
