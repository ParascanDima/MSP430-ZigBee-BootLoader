/*
 * io.c
 *
 *  Created on: 16 мая 2017 г.
 *      Author: Dumitru
 */

/**************Imports***********************************/

#include "io.h"
#if defined(__MSP430FR5969__)
#include "msp430fr5xx_6xxgeneric.h"
#endif
#include "reg_access.h"

/**************Private Macro Definitions*****************/




/**************Private Type Definitions******************/



/**************Private Variable Definitions**************/

static const GPIO_PortAddr GPIO_PORT_TO_BASE[] = {


#if defined(__MSP430_HAS_PORT1_R__)
    {
     __MSP430_BASEADDRESS_PORT1_R__, /*Base*/
     P1IN_ADDR  , /*PxIN*/
     P1OUT_ADDR , /*PxOUT*/
     P1DIR_ADDR , /*PxDIR*/
     P1IFG_ADDR , /*PxIFG*/
     P1IES_ADDR , /*PxIES*/
     P1IE_ADDR  , /*PxIE*/
     P1SEL_ADDR , /*PxSEL*/
     P1SEL2_ADDR, /*PxSEL2*/
     P1REN_ADDR   /*PxREN*/
    },
#elif defined(__MSP430_HAS_PORT1__)
    {
     __MSP430_BASEADDRESS_PORT1_R__, /*Base*/
     P1IN_ADDR  , /*PxIN*/
     P1OUT_ADDR , /*PxOUT*/
     P1DIR_ADDR , /*PxDIR*/
     P1IFG_ADDR , /*PxIFG*/
     P1IES_ADDR , /*PxIES*/
     P1IE_ADDR  , /*PxIE*/
     P1SEL_ADDR , /*PxSEL*/
     P1SEL2_ADDR, /*PxSEL2*/
     P1REN_ADDR   /*PxREN*/
    },

#endif

#if defined(__MSP430_HAS_PORT2_R__)
    {
     __MSP430_BASEADDRESS_PORT2_R__, /*Base*/
     P2IN_ADDR  , /*PxIN*/
     P2OUT_ADDR , /*PxOUT*/
     P2DIR_ADDR , /*PxDIR*/
     P2IFG_ADDR , /*PxIFG*/
     P2IES_ADDR , /*PxIES*/
     P2IE_ADDR  , /*PxIE*/
     P2SEL_ADDR , /*PxSEL*/
     P2SEL2_ADDR, /*PxSEL2*/
     P2REN_ADDR   /*PxREN*/
    },
#elif defined(__MSP430_HAS_PORT2__)
    {
     __MSP430_BASEADDRESS_PORT2_R__, /*Base*/
     P2IN_ADDR  , /*PxIN*/
     P2OUT_ADDR , /*PxOUT*/
     P2DIR_ADDR , /*PxDIR*/
     P2IFG_ADDR , /*PxIFG*/
     P2IES_ADDR , /*PxIES*/
     P2IE_ADDR  , /*PxIE*/
     P2SEL_ADDR , /*PxSEL*/
     P2SEL2_ADDR, /*PxSEL2*/
     P2REN_ADDR   /*PxREN*/
    },

#endif

#if defined(__MSP430_HAS_PORT3_R__)
    {
     __MSP430_BASEADDRESS_PORT3_R__, /*Base*/
     P3IN_ADDR   , /*PxIN*/
     P3OUT_ADDR  , /*PxOUT*/
     P3DIR_ADDR  , /*PxDIR*/
     P3IFG_ADDR  , /*PxIFG*/
     P3IES_ADDR  , /*PxIES*/
     P3IE_ADDR   , /*PxIE*/
     P3SEL_ADDR  , /*PxSEL*/
     P3SEL2_ADDR , /*PxSEL2*/
     P3REN_ADDR    /*PxREN*/
    },
#elif defined(__MSP430_HAS_PORT3__)
    {
     __MSP430_BASEADDRESS_PORT3_R__, /*Base*/
     P3IN_ADDR   , /*PxIN*/
     P3OUT_ADDR  , /*PxOUT*/
     P3DIR_ADDR  , /*PxDIR*/
     P3IFG_ADDR  , /*PxIFG*/
     P3IES_ADDR  , /*PxIES*/
     P3IE_ADDR   , /*PxIE*/
     P3SEL_ADDR  , /*PxSEL*/
     P3SEL2_ADDR , /*PxSEL2*/
     P3REN_ADDR    /*PxREN*/
    },

#endif

#if defined(__MSP430_HAS_PORT4_R__)
    {
     __MSP430_BASEADDRESS_PORT4_R__, /*Base*/
     P4IN_ADDR   , /*PxIN*/
     P4OUT_ADDR  , /*PxOUT*/
     P4DIR_ADDR  , /*PxDIR*/
     P4IFG_ADDR  , /*PxIFG*/
     P4IES_ADDR  , /*PxIES*/
     P4IE_ADDR   , /*PxIE*/
     P4SEL_ADDR  , /*PxSEL*/
     P4SEL2_ADDR , /*PxSEL2*/
     P4REN_ADDR    /*PxREN*/
    },
#elif defined(__MSP430_HAS_PORT4__)
    {
     __MSP430_BASEADDRESS_PORT4_R__, /*Base*/
     P4IN_ADDR   , /*PxIN*/
     P4OUT_ADDR  , /*PxOUT*/
     P4DIR_ADDR  , /*PxDIR*/
     P4IFG_ADDR  , /*PxIFG*/
     P4IES_ADDR  , /*PxIES*/
     P4IE_ADDR   , /*PxIE*/
     P4SEL_ADDR  , /*PxSEL*/
     P4SEL2_ADDR , /*PxSEL2*/
     P4REN_ADDR    /*PxREN*/
    },

#endif

#if defined(__MSP430_HAS_PORT5_R__)
    {
     __MSP430_BASEADDRESS_PORT5_R__, /*Base*/
     P5IN_ADDR   , /*PxIN*/
     P5OUT_ADDR  , /*PxOUT*/
     P5DIR_ADDR  , /*PxDIR*/
     P5IFG_ADDR  , /*PxIFG*/
     P5IES_ADDR  , /*PxIES*/
     P5IE_ADDR   , /*PxIE*/
     P5SEL_ADDR  , /*PxSEL*/
     P5SEL2_ADDR , /*PxSEL2*/
     P5REN_ADDR    /*PxREN*/
    },
#elif defined(__MSP430_HAS_PORT5__)
    {
     __MSP430_BASEADDRESS_PORT5_R__, /*Base*/
     P5IN_ADDR   , /*PxIN*/
     P5OUT_ADDR  , /*PxOUT*/
     P5DIR_ADDR  , /*PxDIR*/
     P5IFG_ADDR  , /*PxIFG*/
     P5IES_ADDR  , /*PxIES*/
     P5IE_ADDR   , /*PxIE*/
     P5SEL_ADDR  , /*PxSEL*/
     P5SEL2_ADDR , /*PxSEL2*/
     P5REN_ADDR    /*PxREN*/
    },

#endif

#if defined(__MSP430_HAS_PORT6_R__)
    {
     __MSP430_BASEADDRESS_PORT6_R__, /*Base*/
     P6IN_ADDR   , /*PxIN*/
     P6OUT_ADDR  , /*PxOUT*/
     P6DIR_ADDR  , /*PxDIR*/
     P6IFG_ADDR  , /*PxIFG*/
     P6IES_ADDR  , /*PxIES*/
     P6IE_ADDR   , /*PxIE*/
     P6SEL_ADDR  , /*PxSEL*/
     P6SEL2_ADDR , /*PxSEL2*/
     P6REN_ADDR    /*PxREN*/
    },
#elif defined(__MSP430_HAS_PORT6__)
    {
     __MSP430_BASEADDRESS_PORT6_R__, /*Base*/
     P6IN_ADDR   , /*PxIN*/
     P6OUT_ADDR  , /*PxOUT*/
     P6DIR_ADDR  , /*PxDIR*/
     P6IFG_ADDR  , /*PxIFG*/
     P6IES_ADDR  , /*PxIES*/
     P6IE_ADDR   , /*PxIE*/
     P6SEL_ADDR  , /*PxSEL*/
     P6SEL2_ADDR , /*PxSEL2*/
     P6REN_ADDR    /*PxREN*/
    },

#endif

#if defined(__MSP430_HAS_PORT7_R__)
    {
     __MSP430_BASEADDRESS_PORT7_R__, /*Base*/
     P7IN_ADDR   , /*PxIN*/
     P7OUT_ADDR  , /*PxOUT*/
     P7DIR_ADDR  , /*PxDIR*/
     P7IFG_ADDR  , /*PxIFG*/
     P7IES_ADDR  , /*PxIES*/
     P7IE_ADDR   , /*PxIE*/
     P7SEL_ADDR  , /*PxSEL*/
     P7SEL2_ADDR , /*PxSEL2*/
     P7REN_ADDR    /*PxREN*/
    },
#elif defined(__MSP430_HAS_PORT7__)
    {
     __MSP430_BASEADDRESS_PORT7_R__, /*Base*/
     P7IN_ADDR   , /*PxIN*/
     P7OUT_ADDR  , /*PxOUT*/
     P7DIR_ADDR  , /*PxDIR*/
     P7IFG_ADDR  , /*PxIFG*/
     P7IES_ADDR  , /*PxIES*/
     P7IE_ADDR   , /*PxIE*/
     P7SEL_ADDR  , /*PxSEL*/
     P7SEL2_ADDR , /*PxSEL2*/
     P7REN_ADDR    /*PxREN*/
    },

#endif

#if defined(__MSP430_HAS_PORT8_R__)
    {
     __MSP430_BASEADDRESS_PORT8_R__, /*Base*/
     P8IN_ADDR   , /*PxIN*/
     P8OUT_ADDR  , /*PxOUT*/
     P8DIR_ADDR  , /*PxDIR*/
     P8IFG_ADDR  , /*PxIFG*/
     P8IES_ADDR  , /*PxIES*/
     P8IE_ADDR   , /*PxIE*/
     P8SEL_ADDR  , /*PxSEL*/
     P8SEL2_ADDR , /*PxSEL2*/
     P8REN_ADDR    /*PxREN*/
    },
#elif defined(__MSP430_HAS_PORT8__)
    {
     __MSP430_BASEADDRESS_PORT8_R__, /*Base*/
     P8IN_ADDR   , /*PxIN*/
     P8OUT_ADDR  , /*PxOUT*/
     P8DIR_ADDR  , /*PxDIR*/
     P8IFG_ADDR  , /*PxIFG*/
     P8IES_ADDR  , /*PxIES*/
     P8IE_ADDR   , /*PxIE*/
     P8SEL_ADDR  , /*PxSEL*/
     P8SEL2_ADDR , /*PxSEL2*/
     P8REN_ADDR    /*PxREN*/
    },

#endif

#if defined(__MSP430_HAS_PORT9_R__)
    {
     __MSP430_BASEADDRESS_PORT9_R__, /*Base*/
     P9IN_ADDR   , /*PxIN*/
     P9OUT_ADDR  , /*PxOUT*/
     P9DIR_ADDR  , /*PxDIR*/
     P9IFG_ADDR  , /*PxIFG*/
     P9IES_ADDR  , /*PxIES*/
     P9IE_ADDR   , /*PxIE*/
     P9SEL_ADDR  , /*PxSEL*/
     P9SEL2_ADDR , /*PxSEL2*/
     P9REN_ADDR    /*PxREN*/
    },
#elif defined(__MSP430_HAS_PORT9__)
    {
     __MSP430_BASEADDRESS_PORT9_R__, /*Base*/
     P9IN_ADDR   , /*PxIN*/
     P9OUT_ADDR  , /*PxOUT*/
     P9DIR_ADDR  , /*PxDIR*/
     P9IFG_ADDR  , /*PxIFG*/
     P9IES_ADDR  , /*PxIES*/
     P9IE_ADDR   , /*PxIE*/
     P9SEL_ADDR  , /*PxSEL*/
     P9SEL2_ADDR , /*PxSEL2*/
     P9REN_ADDR    /*PxREN*/
    },

#endif

#if defined(__MSP430_HAS_PORT10_R__)
    {
     __MSP430_BASEADDRESS_PORT10_R__, /*Base*/
     P10IN_ADDR   , /*PxIN*/
     P10OUT_ADDR  , /*PxOUT*/
     P10DIR_ADDR  , /*PxDIR*/
     P10IFG_ADDR  , /*PxIFG*/
     P10IES_ADDR  , /*PxIES*/
     P10IE_ADDR   , /*PxIE*/
     P10SEL_ADDR  , /*PxSEL*/
     P10SEL2_ADDR , /*PxSEL2*/
     P10REN_ADDR    /*PxREN*/
    },
#elif defined(__MSP430_HAS_PORT10__)
    {
     __MSP430_BASEADDRESS_PORT10_R__, /*Base*/
     P10IN_ADDR   , /*PxIN*/
     P10OUT_ADDR  , /*PxOUT*/
     P10DIR_ADDR  , /*PxDIR*/
     P10IFG_ADDR  , /*PxIFG*/
     P10IES_ADDR  , /*PxIES*/
     P10IE_ADDR   , /*PxIE*/
     P10SEL_ADDR  , /*PxSEL*/
     P10SEL2_ADDR , /*PxSEL2*/
     P10REN_ADDR    /*PxREN*/
    },

#endif

#if defined(__MSP430_HAS_PORT11_R__)
    {
     __MSP430_BASEADDRESS_PORT11_R__, /*Base*/
     P11IN_ADDR   , /*PxIN*/
     P11OUT_ADDR  , /*PxOUT*/
     P11DIR_ADDR  , /*PxDIR*/
     P11IFG_ADDR  , /*PxIFG*/
     P11IES_ADDR  , /*PxIES*/
     P11IE_ADDR   , /*PxIE*/
     P11SEL_ADDR  , /*PxSEL*/
     P11SEL2_ADDR , /*PxSEL2*/
     P11REN_ADDR    /*PxREN*/
    },
#elif defined(__MSP430_HAS_PORT11__)
    {
     __MSP430_BASEADDRESS_PORT11_R__, /*Base*/
     P11IN_ADDR   , /*PxIN*/
     P11OUT_ADDR  , /*PxOUT*/
     P11DIR_ADDR  , /*PxDIR*/
     P11IFG_ADDR  , /*PxIFG*/
     P11IES_ADDR  , /*PxIES*/
     P11IE_ADDR   , /*PxIE*/
     P11SEL_ADDR  , /*PxSEL*/
     P11SEL2_ADDR , /*PxSEL2*/
     P11REN_ADDR    /*PxREN*/
    },

#endif

#if defined(__MSP430_HAS_PORTJ_R__)
    {
     __MSP430_BASEADDRESS_PORTJ_R__, /*Base*/
     PJIN_ADDR   , /*PxIN*/
     PJOUT_ADDR  , /*PxOUT*/
     PJDIR_ADDR  , /*PxDIR*/
     PJIFG_ADDR  , /*PxIFG*/
     PJIES_ADDR  , /*PxIES*/
     PJIE_ADDR   , /*PxIE*/
     PJSEL_ADDR  , /*PxSEL*/
     PJSEL2_ADDR , /*PxSEL2*/
     PJREN_ADDR    /*PxREN*/
    },
#elif defined(__MSP430_HAS_PORTJ__)
    {
     __MSP430_BASEADDRESS_PORTJ_R__, /*Base*/
     PJIN_ADDR   , /*PxIN*/
     PJOUT_ADDR  , /*PxOUT*/
     PJDIR_ADDR  , /*PxDIR*/
     PJIFG_ADDR  , /*PxIFG*/
     PJIES_ADDR  , /*PxIES*/
     PJIE_ADDR   , /*PxIE*/
     PJSEL_ADDR  , /*PxSEL*/
     PJSEL2_ADDR , /*PxSEL2*/
     PJREN_ADDR    /*PxREN*/
    },

#endif
};


/**************Public Variable Definitions***************/



/**************Private Function Definitions**************/



/**************Public Function Definitions***************/

void GPIO_Init(void)
{
#if defined(__MSP430_HAS_PORT1_R__)
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
    GPIO_disableInterrupt(GPIO_PORT_P1, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);

    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
#endif

#if defined(__MSP430_HAS_PORT2_R__)
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
    GPIO_disableInterrupt(GPIO_PORT_P2, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);

    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
#endif

#if defined(__MSP430_HAS_PORT3_R__)
    GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
    GPIO_disableInterrupt(GPIO_PORT_P3, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);

    GPIO_setAsOutputPin(GPIO_PORT_P3, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
#endif

#if defined(__MSP430_HAS_PORT4_R__)
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
    GPIO_disableInterrupt(GPIO_PORT_P4, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);

    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
#endif

#if defined(__MSP430_HAS_PORT5_R__)
    GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
    GPIO_disableInterrupt(GPIO_PORT_P5, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);

    GPIO_setAsOutputPin(GPIO_PORT_P5, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
#endif

#if defined(__MSP430_HAS_PORT6_R__)
    GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
    GPIO_disableInterrupt(GPIO_PORT_P6, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);

    GPIO_setAsOutputPin(GPIO_PORT_P6, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
#endif

#if defined(__MSP430_HAS_PORT7_R__)
    GPIO_setOutputLowOnPin(GPIO_PORT_P7, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
    GPIO_disableInterrupt(GPIO_PORT_P7, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);

    GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
#endif

#if defined(__MSP430_HAS_PORT8_R__)
    GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
    GPIO_disableInterrupt(GPIO_PORT_P8, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);

    GPIO_setAsOutputPin(GPIO_PORT_P8, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
#endif

#if defined(__MSP430_HAS_PORT9_R__)
    GPIO_setOutputLowOnPin(GPIO_PORT_P9, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
    GPIO_disableInterrupt(GPIO_PORT_P9, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);

    GPIO_setAsOutputPin(GPIO_PORT_P9, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
#endif

#if defined(__MSP430_HAS_PORTA_R__)
    GPIO_setOutputLowOnPin(GPIO_PORT_PA, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
    GPIO_disableInterrupt(GPIO_PORT_PA, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);

    GPIO_setAsOutputPin(GPIO_PORT_PA, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
#endif

#if defined(__MSP430_HAS_PORTB_R__)
    GPIO_setOutputLowOnPin(GPIO_PORT_PB, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
    GPIO_disableInterrupt(GPIO_PORT_PB, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);

    GPIO_setAsOutputPin(GPIO_PORT_PB, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
#endif

#if defined(__MSP430_HAS_PORTC_R__)
    GPIO_setOutputLowOnPin(GPIO_PORT_PC, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
    GPIO_disableInterrupt(GPIO_PORT_PC, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);

    GPIO_setAsOutputPin(GPIO_PORT_PC, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
#endif

#if defined(__MSP430_HAS_PORTD_R__)
    GPIO_setOutputLowOnPin(GPIO_PORT_PD, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
    GPIO_disableInterrupt(GPIO_PORT_PD, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);

    GPIO_setAsOutputPin(GPIO_PORT_PD, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
#endif

#if defined(__MSP430_HAS_PORTE_R__)
    GPIO_setOutputLowOnPin(GPIO_PORT_PE, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
    GPIO_disableInterrupt(GPIO_PORT_PE, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);

    GPIO_setAsOutputPin(GPIO_PORT_PE, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
#endif

#if defined(__MSP430_HAS_PORTF_R__)
    GPIO_setOutputLowOnPin(GPIO_PORT_PF, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
    GPIO_disableInterrupt(GPIO_PORT_PF, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);

    GPIO_setAsOutputPin(GPIO_PORT_PF, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
#endif

#if defined(__MSP430_HAS_PORTJ_R__)
    GPIO_setOutputLowOnPin(GPIO_PORT_PJ, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7|GPIO_PIN8|GPIO_PIN9|GPIO_PIN10|GPIO_PIN11|GPIO_PIN12|GPIO_PIN13|GPIO_PIN14|GPIO_PIN15);

    GPIO_setAsOutputPin(GPIO_PORT_PJ, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7|GPIO_PIN8|GPIO_PIN9|GPIO_PIN10|GPIO_PIN11|GPIO_PIN12|GPIO_PIN13|GPIO_PIN14|GPIO_PIN15);
#endif

    GPIO_PrjConfig();
}

void GPIO_setAsOutputPin(GPIO_SUPPORTED_PORTS selectedPort, uint16_t selectedPins) {
    const GPIO_PortAddr port = GPIO_PORT_TO_BASE[selectedPort];

    HWREG8(port.PxSEL) &= ~selectedPins;
    HWREG8(port.PxSEL2) &= ~selectedPins;
    HWREG8(port.PxDIR) |= selectedPins;

    return;
}

void GPIO_setAsInputPin(GPIO_SUPPORTED_PORTS selectedPort, uint16_t selectedPins) {
    const GPIO_PortAddr port = GPIO_PORT_TO_BASE[selectedPort];

    HWREG8(port.PxSEL)  &= ~selectedPins;
    HWREG8(port.PxSEL2) &= ~selectedPins;
    HWREG8(port.PxDIR) &= ~selectedPins;
    HWREG8(port.PxREN) &= ~selectedPins;
}

void GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_SUPPORTED_PORTS selectedPort, uint16_t selectedPins, uint8_t mode) {
    const GPIO_PortAddr port = GPIO_PORT_TO_BASE[selectedPort];

    HWREG8(port.PxDIR) |= selectedPins;
    switch(mode)
    {
    case GPIO_PRIMARY_MODULE_FUNCTION:
        HWREG8(port.PxSEL)  |= selectedPins;
        HWREG8(port.PxSEL2) &= ~selectedPins;
        break;
    case GPIO_SECONDARY_MODULE_FUNCTION:
        HWREG8(port.PxSEL)  &= ~selectedPins;
        HWREG8(port.PxSEL2) |= selectedPins;
        break;
    case GPIO_TERNARY_MODULE_FUNCTION:
        HWREG8(port.PxSEL)  |= selectedPins;
        HWREG8(port.PxSEL2) |= selectedPins;
        break;
    }
}

void GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_SUPPORTED_PORTS selectedPort, uint16_t selectedPins, uint8_t mode) {
    const GPIO_PortAddr port = GPIO_PORT_TO_BASE[selectedPort];

    HWREG8(port.PxDIR) &= ~selectedPins;
    switch(mode)
    {
    case GPIO_PRIMARY_MODULE_FUNCTION:
        HWREG8(port.PxSEL)  |= selectedPins;
        HWREG8(port.PxSEL2) &= ~selectedPins;
        break;
    case GPIO_SECONDARY_MODULE_FUNCTION:
        HWREG8(port.PxSEL)  &= ~selectedPins;
        HWREG8(port.PxSEL2) |= selectedPins;
        break;
    case GPIO_TERNARY_MODULE_FUNCTION:
        HWREG8(port.PxSEL)  |= selectedPins;
        HWREG8(port.PxSEL2) |= selectedPins;
        break;
    }
}

void GPIO_setOutputHighOnPin(GPIO_SUPPORTED_PORTS selectedPort, uint16_t selectedPins) {
    const GPIO_PortAddr port = GPIO_PORT_TO_BASE[selectedPort];

    HWREG8(port.PxOUT) |= selectedPins;
}

void GPIO_setOutputLowOnPin(GPIO_SUPPORTED_PORTS selectedPort, uint16_t selectedPins) {
    const GPIO_PortAddr port = GPIO_PORT_TO_BASE[selectedPort];

    HWREG8(port.PxOUT) &= ~selectedPins;
}

void GPIO_toggleOutputOnPin(GPIO_SUPPORTED_PORTS selectedPort, uint16_t selectedPins) {
    const GPIO_PortAddr port = GPIO_PORT_TO_BASE[selectedPort];

    HWREG8(port.PxOUT) ^= selectedPins;
}

void GPIO_setAsInputPinWithPullDownResistor(GPIO_SUPPORTED_PORTS selectedPort, uint16_t selectedPins) {
    const GPIO_PortAddr port = GPIO_PORT_TO_BASE[selectedPort];

    HWREG8(port.PxSEL)  &= ~selectedPins;
    HWREG8(port.PxSEL2) &= ~selectedPins;

    HWREG8(port.PxDIR) &= ~selectedPins;
    HWREG8(port.PxREN) |= selectedPins;
    HWREG8(port.PxOUT) &= ~selectedPins;
}

void GPIO_setAsInputPinWithPullUpResistor(GPIO_SUPPORTED_PORTS selectedPort, uint16_t selectedPins) {
    const GPIO_PortAddr port = GPIO_PORT_TO_BASE[selectedPort];

    HWREG8(port.PxSEL)  &= ~selectedPins;
    HWREG8(port.PxSEL2) &= ~selectedPins;
    HWREG8(port.PxDIR) &= ~selectedPins;
    HWREG8(port.PxREN) |= selectedPins;
    HWREG8(port.PxOUT) |= selectedPins;
}

uint8_t GPIO_getInputPinValue(GPIO_SUPPORTED_PORTS selectedPort, uint16_t selectedPins) {
    const GPIO_PortAddr port = GPIO_PORT_TO_BASE[selectedPort];

    uint16_t inputPinValue = HWREG8(port.PxIN) & (selectedPins);

    if(inputPinValue > 0)
    {
        return (GPIO_INPUT_PIN_HIGH);
    }
    return (GPIO_INPUT_PIN_LOW);
}

void GPIO_enableInterrupt(GPIO_SUPPORTED_PORTS selectedPort, uint16_t selectedPins) {
    const GPIO_PortAddr port = GPIO_PORT_TO_BASE[selectedPort];

    if(port.PxIE != 0xFFFF)
    {
        HWREG8(port.PxIE) |= selectedPins;
    }
}

void GPIO_disableInterrupt(GPIO_SUPPORTED_PORTS selectedPort, uint16_t selectedPins) {
    const GPIO_PortAddr port = GPIO_PORT_TO_BASE[selectedPort];

    if(port.PxIE != 0xFFFF)
    {
        HWREG8(port.PxIE) &= ~selectedPins;
    }
}

uint16_t GPIO_getInterruptStatus(GPIO_SUPPORTED_PORTS selectedPort, uint16_t selectedPins) {
    const GPIO_PortAddr port = GPIO_PORT_TO_BASE[selectedPort];

    if(port.PxIFG != 0xFFFF)
    {
        return (HWREG8(port.PxIFG) & selectedPins);
    }

    return (uint16_t)0x00;
}

void GPIO_clearInterrupt(GPIO_SUPPORTED_PORTS selectedPort, uint16_t selectedPins) {
    const GPIO_PortAddr port = GPIO_PORT_TO_BASE[selectedPort];

    if(port.PxIFG != 0xFFFF){
        HWREG8(port.PxIFG) &= ~selectedPins;
    }
}

void GPIO_selectInterruptEdge(GPIO_SUPPORTED_PORTS selectedPort, uint16_t selectedPins, ExtIntEdgeSelect edgeSelect) {
    const GPIO_PortAddr port = GPIO_PORT_TO_BASE[selectedPort];


    if(port.PxIES != 0xFFFF){
        if(GPIO_LOW_TO_HIGH_TRANSITION == edgeSelect)
        {
            HWREG8(port.PxIES) &= ~selectedPins;
        }
        else
        {
            HWREG8(port.PxIES) |= selectedPins;
        }
    }
}
