/*
 * io.h
 *
 *  Created on: 16 мая 2017 г.
 *      Author: Dumitru
 */

#ifndef IO_H_
#define IO_H_


/***************************Imports*************************************************/
#include <stdint.h>
#include "io_cnf.h"

/***************************Public Macro Definitions********************************/


//#define GPIO_PORT_P1                                                          0
//#define GPIO_PORT_P2                                                          1
//#define GPIO_PORT_P3                                                          2
//#define GPIO_PORT_P4                                                          3
//#define GPIO_PORT_P5                                                          4
//#define GPIO_PORT_P6                                                          5
//#define GPIO_PORT_P7                                                          6
//#define GPIO_PORT_P8                                                          7
//#define GPIO_PORT_P9                                                          8
//#define GPIO_PORT_P10                                                         9
//#define GPIO_PORT_P11                                                        10
//#define GPIO_PORT_PA                                                         11
//#define GPIO_PORT_PB                                                         12
//#define GPIO_PORT_PC                                                         13
//#define GPIO_PORT_PD                                                         14
//#define GPIO_PORT_PE                                                         15
//#define GPIO_PORT_PF                                                         16
//#define GPIO_PORT_PJ                                                         17

#define GPIO_PIN0                                                      (0x0001)
#define GPIO_PIN1                                                      (0x0002)
#define GPIO_PIN2                                                      (0x0004)
#define GPIO_PIN3                                                      (0x0008)
#define GPIO_PIN4                                                      (0x0010)
#define GPIO_PIN5                                                      (0x0020)
#define GPIO_PIN6                                                      (0x0040)
#define GPIO_PIN7                                                      (0x0080)
#define GPIO_PIN8                                                      (0x0100)
#define GPIO_PIN9                                                      (0x0200)
#define GPIO_PIN10                                                     (0x0400)
#define GPIO_PIN11                                                     (0x0800)
#define GPIO_PIN12                                                     (0x1000)
#define GPIO_PIN13                                                     (0x2000)
#define GPIO_PIN14                                                     (0x4000)
#define GPIO_PIN15                                                     (0x8000)

#define GPIO_PRIMARY_MODULE_FUNCTION                                     (0x01)
#define GPIO_SECONDARY_MODULE_FUNCTION                                   (0x02)
#define GPIO_TERNARY_MODULE_FUNCTION                                     (0x03)

#define GPIO_HIGH_TO_LOW_TRANSITION                                      (0x01)
#define GPIO_LOW_TO_HIGH_TRANSITION                                      (0x00)

#define GPIO_INPUT_PIN_HIGH                                              (0x01)
#define GPIO_INPUT_PIN_LOW                                               (0x00)


#define ExternalInterruptDisable(port_name, pin)     GPIO_disableInterrupt(port_name, pin)
#define ExternalInterruptEnable(port_name, pin)      GPIO_enableInterrupt(port_name, pin)


/***************************Public Type Definitions********************************/

typedef enum {
    eRisingEdge  =0,
    eFallingEdge = 1
}ExtIntEdgeSelect;

typedef enum{
#if defined(__MSP430_HAS_PORT1_R__)

     GPIO_PORT_P1 = 0 ,

#endif /*__MSP430_HAS_PORT1_R__*/
#if defined(__MSP430_HAS_PORT2_R__)

    GPIO_PORT_P2 = 1 ,

#endif /*__MSP430_HAS_PORT2_R__*/
#if defined(__MSP430_HAS_PORT3_R__)

    GPIO_PORT_P3 = 2 ,

#endif /*__MSP430_HAS_PORT3_R__*/
#if defined(__MSP430_HAS_PORT4_R__)

    GPIO_PORT_P4 = 3 ,

#endif /*__MSP430_HAS_PORT4_R__*/

#if defined(__MSP430_HAS_PORT5_R__)

    GPIO_PORT_P5 = 4 ,

#endif /*__MSP430_HAS_PORT5_R__*/

#if defined(__MSP430_HAS_PORT6_R__)

    GPIO_PORT_P6 = 5 ,

#endif /*__MSP430_HAS_PORT6_R__*/

#if defined(__MSP430_HAS_PORT7_R__)

    GPIO_PORT_P7 = 6 ,

#endif /*__MSP430_HAS_PORT7_R__*/

#if defined(__MSP430_HAS_PORT8_R__)

    GPIO_PORT_P8 = 7 ,

#endif /*__MSP430_HAS_PORT8_R__*/

#if defined(__MSP430_HAS_PORT9_R__)

    GPIO_PORT_P9 = 8 ,

#endif /*__MSP430_HAS_PORT9_R__*/

#if defined(__MSP430_HAS_PORT10_R__)

    GPIO_PORT_P10 = 9 ,

#endif /*__MSP430_HAS_PORT10_R__*/

#if defined(__MSP430_HAS_PORT11_R__)

    GPIO_PORT_P11 = 10,

#endif /*__MSP430_HAS_PORT11_R__*/

#if (defined(__MSP430_HAS_PORTJ_R__))
    #if defined(__MSP430_HAS_PORT5_R__)
        #if defined(__MSP430_HAS_PORT6_R__)
            #if defined(__MSP430_HAS_PORT7_R__)
                #if defined(__MSP430_HAS_PORT8_R__)
                    #if defined(__MSP430_HAS_PORT9_R__)
                        #if defined(__MSP430_HAS_PORT10_R__)
                            #if defined(__MSP430_HAS_PORT11_R__)
                                GPIO_PORT_PJ = 11,
                            #else
                                GPIO_PORT_PJ = 10,
                            #endif /*defined(__MSP430_HAS_PORT11_R__)*/
                        #else
                                GPIO_PORT_PJ = 9,
                        #endif /*defined(__MSP430_HAS_PORT10_R__)*/
                    #else
                                GPIO_PORT_PJ = 8,
                    #endif /*defined(__MSP430_HAS_PORT9_R__)*/
                #else
                                GPIO_PORT_PJ = 7,
                #endif /*defined(__MSP430_HAS_PORT8_R__)*/
            #else
                                GPIO_PORT_PJ = 6,
            #endif /*defined(__MSP430_HAS_PORT7_R__)*/
        #else
                                GPIO_PORT_PJ = 5,
        #endif /*defined(__MSP430_HAS_PORT6_R__)*/
    #else
                                GPIO_PORT_PJ = 4,
    #endif /*defined(__MSP430_HAS_PORT5_R__)*/


#endif /*__MSP430_HAS_PORTJ_R__*/
}GPIO_SUPPORTED_PORTS;

/***************************Public Data Definitions********************************/



/***************************Public Function Definitions****************************/


void     GPIO_Init(void);
void     GPIO_setAsOutputPin(GPIO_SUPPORTED_PORTS selectedPort, uint16_t selectedPins);
void     GPIO_setAsInputPin(GPIO_SUPPORTED_PORTS selectedPort, uint16_t selectedPins);

#ifdef __msp430
void     GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_SUPPORTED_PORTS selectedPort, uint16_t selectedPins, uint8_t mode);
void     GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_SUPPORTED_PORTS selectedPort, uint16_t selectedPins, uint8_t mode);
#endif

void     GPIO_setOutputHighOnPin(GPIO_SUPPORTED_PORTS selectedPort, uint16_t selectedPins);
void     GPIO_setOutputLowOnPin(GPIO_SUPPORTED_PORTS selectedPort, uint16_t selectedPins);
void     GPIO_toggleOutputOnPin(GPIO_SUPPORTED_PORTS selectedPort, uint16_t selectedPins);
void     GPIO_setAsInputPinWithPullDownResistor(GPIO_SUPPORTED_PORTS selectedPort, uint16_t selectedPins);
void     GPIO_setAsInputPinWithPullUpResistor(GPIO_SUPPORTED_PORTS selectedPort, uint16_t selectedPins);
uint8_t  GPIO_getInputPinValue(GPIO_SUPPORTED_PORTS selectedPort, uint16_t selectedPins);
void     GPIO_enableInterrupt(GPIO_SUPPORTED_PORTS selectedPort, uint16_t selectedPins);
void     GPIO_disableInterrupt(GPIO_SUPPORTED_PORTS selectedPort, uint16_t selectedPins);
uint16_t GPIO_getInterruptStatus(GPIO_SUPPORTED_PORTS selectedPort, uint16_t selectedPins);
void     GPIO_clearInterrupt(GPIO_SUPPORTED_PORTS selectedPort, uint16_t selectedPins);
void     GPIO_selectInterruptEdge(GPIO_SUPPORTED_PORTS selectedPort, uint16_t selectedPins, ExtIntEdgeSelect edgeSelect);

void     ExternalInterruptSenseControl(uint8_t interrupt_nr, uint8_t state);

#endif /* IO_H_ */
