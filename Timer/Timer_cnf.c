/*
 * Timer_cnf.c
 *
 *  Created on: 22 ����. 2017 �.
 *      Author: Dumitru
 */


/**************Imports***********************************/

#include "Timer.h"
#include <stdbool.h>
#include "main.h"

/**************Private Macro Definitions*****************/

#define CAPTURE_TIMER_TICK_US  30

/**************Private Type Definitions******************/



/**************Private Variable Definitions**************/

const TimerCallbackHandler TmCbks = {.A0_EventCallback = NULL_PTR,
                                     .A1_EventCallback = NULL_PTR};
//                                     .A1_EventCallback = Main_10ms};

TimerHandler EventHandler = {.enableTimingHandling = FALSE,
                             .callbackHdl = &TmCbks};

/**************Public Variable Definitions***************/



/**************Private Function Definitions**************/





/**************Public Function Definitions***************/


/*Timer1 10ms configuration */
void TimerA1_Registers_Init(){
    TA1CCTL0 = CM_0 | CCIS_0 | OUTMOD_0 ;

    TA1CCR0 = 14999;

    TA1CTL = TASSEL_2 | ID_3 | MC_1 | TAIE;
}

/*Timer0 is configured to 1Hz frequency interrupt */
void TimerA0_Registers_Init(){
    TA0CCTL0 = CM_0 | CCIS_3 | OUTMOD_0;

    TA0CCR0 = 32767;

    TA0CTL = TASSEL_1 | ID_0 | MC_1 | TAIE;
}

/*TimerB is configured to input capture */
void TimerB_Registers_Init(){
    TBCCTL0 = CM_1 | SCS | CCIS_0 | CAP;

    TBCTL = TBSSEL_1 | ID_0 | MC_2;
}

#pragma vector=TIMER0_A1_VECTOR
__interrupt void TimerA0_Handler()
{
    TA0CTL &= ~(CCIFG);
    Seconds_Inc();
    if(TRUE == EventHandler.enableTimingHandling)
    {
        if (EventHandler.callbackHdl->A0_EventCallback != NULL_PTR)
        {
            EventHandler.callbackHdl->A0_EventCallback();
        }
    }
}


#pragma vector=TIMER1_A1_VECTOR
__interrupt void TimerA1_Handler()
{
    TA1CTL &= ~(CCIFG);
    timerTimeQuant_Inc();
    if(TRUE == EventHandler.enableTimingHandling)
    {
        if (EventHandler.callbackHdl->A1_EventCallback != NULL_PTR)
        {
            EventHandler.callbackHdl->A1_EventCallback();
        }
    }
}
