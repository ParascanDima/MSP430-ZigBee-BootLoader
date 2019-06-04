/*
 * fls_types.h
 *
 *  Created on: May 14, 2019
 *      Author: dumitru
 */

#ifndef FLS_TYPES_H_
#define FLS_TYPES_H_

#include <stdint.h>
#include <stdbool.h>

typedef enum
{
    enACLK = 0,
    enMCLK,
    enSMCLK,
}FlsClkSourceEnum;

typedef struct
{
    uint8_t ClkDiv;
    bool isLocked;
    FlsClkSourceEnum source;
    void (*EnterCriticalSection)(void);
    void (*ExitCriticalSection)(void);
}FlashConfigType;

typedef enum
{
    enUINT8 = 1,
    enUINT16 = 2,
    enUINT32 = 4
}FlashDataType;

#endif /* FLS_TYPES_H_ */
