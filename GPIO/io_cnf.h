/*
 * io_cnf.h
 *
 *  Created on: 18 сент. 2017 г.
 *      Author: Dumitru
 */

#ifndef IO_CNF_H_
#define IO_CNF_H_

/*This file will be modified by code generator*/


/***************************Imports*************************************************/

#include <msp430.h>

/***************************Public Macro Definitions********************************/

#define __MCU_HAS_PORTS__ 4

#if defined(__msp430)




#endif

#if (!defined(__msp430) && defined (_AVR_IO_H_))

#define ZB_RST_PIN      PD5         //PIN5 PORTD
#define ZB_WAKE_PIN     PD4         //PIN4 PORTD
#define ZB_INT_PIN      PD3         //PIN3 PORTD
#define ZB_SDI_PIN      PB4         //PIN4 PORTB
#define ZB_SCK_PIN      PB5         //PIN5 PORTB
#define ZB_CS_PIN       PB2         //PIN2 PORTB
#define ZB_SDO_PIN      PB3         //PIN3 PORTB


#define ZB_RST_PORT     PORTD       //
#define ZB_RST_DDR      DDRD
#define ZB_WAKE_PORT    PORTD       //
#define ZB_WAKE_DDR     DDRD
#define ZB_INT_PORT     PORTD       //
#define ZB_INT_DDR      DDRD


#define ZB_SDI_PORT     PORTB       //
#define ZB_SDI_DDR      DDRB
#define ZB_SCK_PORT     PORTB       //
#define ZB_SCK_DDR      DDRB
#define ZB_CS_PORT      PORTB       //
#define ZB_CS_DDR       DDRB
#define ZB_SDO_PORT     PORTB       //
#define ZB_SDO_DDR      DDRB


#define ExternalInterruptDisable(x)     (EIMSK &= ~(1 << x))
#define ExternalInterruptEnable(x)      (EIMSK |= (1 << x))
#define ExternalInterruptClearFlag(x)   (EIFR &= ~(1 << x))
#define ExternalInterruptSetFlag(x)     (EIFR |= (1 << x))
#endif

#ifdef USE_LAUNCHPAD_G2553
#define LED_RED                     GPIO_PIN0
#define LED_GREEN                   GPIO_PIN6
#endif /* USE_LAUNCHPAD_G2553 */


#if defined(USE_GSM)

#define GSM_RST                 GPIO_PIN5          //P1.5
#define PWRKEY                  GPIO_PIN4          //P1.4

#endif /*USE_GSM*/


/***************************Public Type Definitions********************************/



/***************************Public Data Definitions********************************/



/***************************Public Function Definitions****************************/
void GPIO_PrjConfig(void);


#endif /* IO_CNF_H_ */
