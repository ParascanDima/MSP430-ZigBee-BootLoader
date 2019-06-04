/*
 * Timer.c
 *
 *  Created on: 9 мая 2017 г.
 *      Author: Dumitru
 */


/**************Imports***********************************/

#include <msp430.h>
#include <stdint.h>
#include "Timer.h"

/**************Private Macro Definitions*****************/



/**************Private Type Definitions******************/



/**************Private Variable Definitions**************/


uint64_t time_quant_count = 0;
uint8_t seconds = 0;
uint8_t minutes = 0;
uint8_t hours = 0;


/**************Public Variable Definitions***************/



/**************Private Function Definitions**************/



/**************Public Function Definitions***************/

void timerTimeQuant_Inc(){
    time_quant_count++;
}



/*********************Functions that have to be deleted, MAY BE***************************************/


uint64_t Get_TimeQuant(){
    return time_quant_count;
}

uint8_t Get_Seconds(){
    return seconds;
}

void Seconds_Inc(){
    seconds++;
    if (seconds >= 60){
        seconds = 0;
        minutes++;
        if (minutes >= 60){
            minutes = 0;
            hours++;
            if (hours > 23){
                hours = 0;
            }
        }
    }
}


/**************************************************************************************************/

uint64_t timerPlane_Tout(uint16_t planed_ms){

    if (planed_ms < TIME_QUANT){
        planed_ms = 1;
    }
    else{
        planed_ms /= TIME_QUANT;
    }
    return ((uint64_t)planed_ms + time_quant_count);
}

uint8_t Check_Timeout( uint64_t planed_ms ){
    uint8_t tRsp;
    if (planed_ms < time_quant_count){
        tRsp = FALSE;
    }
    else{
        tRsp = TRUE;
    }
    return tRsp;
}


void Delay_ms(uint16_t miliseconds){
    uint64_t planed_delay = timerPlane_Tout(miliseconds);
    while(Check_Timeout(planed_delay));
}

uint16_t ReadCoreTimer(void){

    return TA0R;
}

uint64_t GetMilliseconds(void){
    return time_quant_count*TIME_QUANT;
}

uint32_t ElapsedTimeSince(uint32_t time){
    uint32_t currentTime = (uint32_t)GetMilliseconds();

    if(currentTime < time){
        return ((UINT16_MAX - time) + currentTime);
    }
    else{
        return (currentTime - time);
    }
}
