/*
 * Timer_cnf.h
 *
 *  Created on: 20 ����. 2017 �.
 *      Author: Dumitru
 */

#ifndef TIMER_CNF_H_
#define TIMER_CNF_H_


/***************************Imports*************************************************/

#include "msp430.h"
#include <AUTOSAR31/Std_Types.h>

/***************************Public Macro Definitions********************************/


/***************************Public Type Definitions********************************/

typedef struct
{
    void (*A0_EventCallback)(void);
    void (*A1_EventCallback)(void);
}TimerCallbackHandler;

typedef struct
{
    const TimerCallbackHandler * callbackHdl;
    uint8_t enableTimingHandling;
}TimerHandler;

/***************************Public Data Definitions********************************/



/***************************Public Function Definitions****************************/

void TimerA0_Registers_Init(void);
void TimerA1_Registers_Init(void);
void TimerB_Registers_Init();


#endif /* TIMER_CNF_H_ */
