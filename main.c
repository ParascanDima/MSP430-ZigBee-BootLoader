#include <msp430.h> 
#include <stdint.h>
#include <stdbool.h>
#include "Timer/Timer.h"
#include "Fls/fls_main.h"
#include "SchM/schm_boot.h"
#include "main.h"

extern void JumpToAppl(void);
extern void EraseApplication(void);
extern void CalcCRC(void);
extern void Spi_Init(void);


extern const uint16_t APPLICATION_KEY[];
extern const uint16_t APPLICATION_CRC[];
extern const uint16_t APPLICATION_CODE[];


const uint16_t AppAddr = (uint16_t)APPLICATION_CODE;


void ClockInit(){

    BCSCTL2 = XT2OFF | SELM_0 | DIVM_0 | DIVS_0;

    if (CALBC1_12MHZ != 0xFF) {
            /* Adjust this accordingly to your VCC rise time */
        //__delay_cycles(100000);

        /* Follow recommended flow. First, clear all DCOx and MODx bits. Then
         * apply new RSELx values. Finally, apply new DCOx and MODx bit values.
         */
        DCOCTL = 0x00;
        BCSCTL1 = CALBC1_12MHZ;     /* Set DCO to 12MHz */
        DCOCTL = CALDCO_12MHZ;
    }

    BCSCTL1 |= DIVA_0;
    BCSCTL3 = XT2S_0 | LFXT1S_0 | XCAP_1;
    IFG1 &= ~OFIFG;
}

void MainPlatformInit(void)
{
    ClockInit();
    TimerA0_Registers_Init();
    Fls_Init(&globalFlashCfg);
    //Spi_Init();
}

void GlobalInterruptsEnable(void)
{
    __bis_SR_register(GIE);
}

void GlobalInterruptsDisnable(void)
{
    __bic_SR_register(GIE);
}


TASK(Main_10ms)
{
    SchM_MainFunction();
    Fls_MainFunction();
}


/**
 * main.c
 */
int main(void)
{
    volatile uint16_t appKey = *APPLICATION_KEY;
    uint16_t string[3] = {0x1234, 0x5678, 0x89AB};
    uint16_t string_1[3] = {0xF1F2, 0xF3F4, 0xF5F6};

	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	SchM_InitPlatform();
    //AppAddr = *APPLICATION;

    __bis_SR_register(GIE);
	if (0xCAFEDEDA == appKey)
	{
	    //SetBootState(enAppRun);
	    //JumpToAppl();
	}
	else
	{
	    while (true)
	    {
	        SchM_MainFunction();
	        Fls_MainFunction();
	    }

	}
	
	return 0;
}



