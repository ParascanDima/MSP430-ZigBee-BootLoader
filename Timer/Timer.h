/*
 * Timer.h
 *
 *  Created on: 9 мая 2017 г.
 *      Author: Dumitru
 */

#ifndef TIMER_H_
#define TIMER_H_


/***************************Imports*************************************************/

#include <stdint.h>
#include "Timer_cnf.h"

/***************************Public Macro Definitions********************************/

#define TRUE  1
#define FALSE 0


#define TIME_QUANT   10   /*Timer is configured to 10ms*/

//CORE_TIMER_OVF is configured to 10ms with 2MHz timer frequency
//#define CORE_TIMER_OVF 0x4E20  //0x3A98

//#define ONE_TIMER_TICK          (SYS_FREQ/8)
//#define ONE_MILISECOND          (ONE_TIMER_TICK*(CORE_TIMER_OVF/10))
//#define ONE_SECOND              (SYS_FREQ/8)
//#define MS_TO_CORE_TICKS(x)     (uint16_t)((x)*ONE_SECOND/1000)
// number of core timer ticks since "tick"

//#define CT_TICKS_SINCE(tick) (uint16_t)TickSince(tick)

//static uint16_t CoreTimer;
//#define CT_TICKS_SINCE(tick) \
    (((CoreTimer = ReadCoreTimer()) < tick) ? \
            ((CORE_TIMER_OVF - tick) + CoreTimer) : \
            (CoreTimer - tick))


/***************************Public Type Definitions********************************/



/***************************Public Data Definitions********************************/



/***************************Public Function Definitions****************************/

void        timerTimeQuant_Inc();
uint64_t    timerPlane_Tout(uint16_t planed_ms);
uint8_t     Check_Timeout( uint64_t planed_ms );
uint16_t    ReadCoreTimer();
uint64_t    Get_TimeQuant();
uint8_t     Get_Seconds();
void        Seconds_Inc();
void        Delay_ms(uint16_t miliseconds);
uint64_t    GetMilliseconds(void);
uint32_t    ElapsedTimeSince(uint32_t time);


#endif /* TIMER_H_ */
