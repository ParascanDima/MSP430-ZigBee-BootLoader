/*
 * reg_access.h
 *
 *  Created on: 21 мая 2017 г.
 *      Author: Dumitru
 */

#ifndef REG_ACCESS_H_
#define REG_ACCESS_H_


/***************************Imports*************************************************/


/***************************Public Macro Definitions********************************/

#define HWREG32(x)                                                              \
    (*((volatile uint32_t *)((uint16_t)x)))
#define HWREG16(x)                                                             \
    (*((volatile uint16_t *)((uint16_t)x)))
#define HWREG8(x)                                                             \
    (*((volatile uint8_t *)((uint16_t)x)))

#define OFS_PAIN               (0x0000)
#define OFS_PAOUT              (0x0001)
#define OFS_PADIR              (0x0002)
#define OFS_PAIFG              (0x0003)
#define OFS_PAIES              (0x0004)
#define OFS_PAIE               (0x0005)
#define OFS_PASEL              (0x0006)
#define OFS_PAREN              (0x0007)

#ifdef __MSP430_HAS_PORT1_R__

#define P1IN_ADDR    (uint16_t)(&P1IN)
#define P1OUT_ADDR   (uint16_t)(&P1OUT)
#define P1DIR_ADDR   (uint16_t)(&P1DIR)

#if defined(PORT1_VECTOR)
#define P1IFG_ADDR   (uint16_t)(&P1IFG)
#define P1IES_ADDR   (uint16_t)(&P1IES)
#define P1IE_ADDR    (uint16_t)(&P1IE )
#else
#define P1IFG_ADDR   (uint16_t)(0xFFFF)
#define P1IES_ADDR   (uint16_t)(0xFFFF)
#define P1IE_ADDR    (uint16_t)(0xFFFF)
#endif /*defined(PORT1_VECTOR)*/

#define P1SEL_ADDR   (uint16_t)(&P1SEL)
#define P1SEL2_ADDR  (uint16_t)(&P1SEL2)
#define P1REN_ADDR   (uint16_t)(&P1REN)

#endif /*__MSP430_HAS_PORT1_R__*/

#ifdef __MSP430_HAS_PORT2_R__

#define P2IN_ADDR    (uint16_t)(&P2IN)
#define P2OUT_ADDR   (uint16_t)(&P2OUT)
#define P2DIR_ADDR   (uint16_t)(&P2DIR)

#if defined(PORT2_VECTOR)
#define P2IFG_ADDR   (uint16_t)(&P2IFG)
#define P2IES_ADDR   (uint16_t)(&P2IES)
#define P2IE_ADDR    (uint16_t)(&P2IE )
#else
#define P2IFG_ADDR   (uint16_t)(0xFFFF)
#define P2IES_ADDR   (uint16_t)(0xFFFF)
#define P2IE_ADDR    (uint16_t)(0xFFFF)
#endif /*defined(PORT2_VECTOR)*/

#define P2SEL_ADDR   (uint16_t)(&P2SEL)
#define P2SEL2_ADDR  (uint16_t)(&P2SEL2)
#define P2REN_ADDR   (uint16_t)(&P2REN)

#endif /*__MSP430_HAS_PORT2_R__*/


#if defined(__MSP430_HAS_PORT3_R__)

#define P3IN_ADDR    (uint16_t)(&P3IN)
#define P3OUT_ADDR   (uint16_t)(&P3OUT)
#define P3DIR_ADDR   (uint16_t)(&P3DIR)

#if defined(PORT3_VECTOR)
#define P3IFG_ADDR   (uint16_t)(&P3IFG)
#define P3IES_ADDR   (uint16_t)(&P3IES)
#define P3IE_ADDR    (uint16_t)(&P3IE )
#else
#define P3IFG_ADDR   (uint16_t)(0xFFFF)
#define P3IES_ADDR   (uint16_t)(0xFFFF)
#define P3IE_ADDR    (uint16_t)(0xFFFF)
#endif /*defined(PORT3_VECTOR)*/

#define P3SEL_ADDR   (uint16_t)(&P3SEL)
#define P3SEL2_ADDR  (uint16_t)(&P3SEL2)
#define P3REN_ADDR   (uint16_t)(&P3REN)

#endif /*__MSP430_HAS_PORT3_R__*/

#if defined(__MSP430_HAS_PORT4_R__)

#define P4IN_ADDR    (uint16_t)(&P4IN)
#define P4OUT_ADDR   (uint16_t)(&P4OUT)
#define P4DIR_ADDR   (uint16_t)(&P4DIR)

#if defined(PORT4_VECTOR)
#define P4IFG_ADDR   (uint16_t)(&P4IFG)
#define P4IES_ADDR   (uint16_t)(&P4IES)
#define P4IE_ADDR    (uint16_t)(&P4IE )
#else
#define P4IFG_ADDR   (uint16_t)(0xFFFF)
#define P4IES_ADDR   (uint16_t)(0xFFFF)
#define P4IE_ADDR    (uint16_t)(0xFFFF)
#endif /*defined(PORT4_VECTOR)*/

#define P4SEL_ADDR   (uint16_t)(&P4SEL)
#define P4SEL2_ADDR  (uint16_t)(&P4SEL2)
#define P4REN_ADDR   (uint16_t)(&P4REN)

#endif /*__MSP430_HAS_PORT4_R__*/

#if defined(__MSP430_HAS_PORT5_R__)

#define P5IN_ADDR    (uint16_t)(&P5IN)
#define P5OUT_ADDR   (uint16_t)(&P5OUT)
#define P5DIR_ADDR   (uint16_t)(&P5DIR)

#if defined(PORT5_VECTOR)
#define P5IFG_ADDR   (uint16_t)(&P5IFG)
#define P5IES_ADDR   (uint16_t)(&P5IES)
#define P5IE_ADDR    (uint16_t)(&P5IE )
#else
#define P5IFG_ADDR   (uint16_t)(0xFFFF)
#define P5IES_ADDR   (uint16_t)(0xFFFF)
#define P5IE_ADDR    (uint16_t)(0xFFFF)
#endif /*defined(PORT5_VECTOR)*/

#define P5SEL_ADDR   (uint16_t)(&P5SEL)
#define P5SEL2_ADDR  (uint16_t)(&P5SEL2)
#define P5REN_ADDR   (uint16_t)(&P5REN)

#endif /*__MSP430_HAS_PORT5_R__*/

#if defined(__MSP430_HAS_PORT6_R__)

#define P6IN_ADDR    (uint16_t)(&P6IN)
#define P6OUT_ADDR   (uint16_t)(&P6OUT)
#define P6DIR_ADDR   (uint16_t)(&P6DIR)

#if defined(PORT6_VECTOR)
#define P6IFG_ADDR   (uint16_t)(&P6IFG)
#define P6IES_ADDR   (uint16_t)(&P6IES)
#define P6IE_ADDR    (uint16_t)(&P6IE )
#else
#define P6IFG_ADDR   (uint16_t)(0xFFFF)
#define P6IES_ADDR   (uint16_t)(0xFFFF)
#define P6IE_ADDR    (uint16_t)(0xFFFF)
#endif /*defined(PORT6_VECTOR)*/

#define P6SEL_ADDR   (uint16_t)(&P6SEL)
#define P6SEL2_ADDR  (uint16_t)(&P6SEL2)
#define P6REN_ADDR   (uint16_t)(&P6REN)

#endif /*__MSP430_HAS_PORT6_R__*/

#if defined(__MSP430_HAS_PORT7_R__)

#define P7IN_ADDR    (uint16_t)(&P7IN)
#define P7OUT_ADDR   (uint16_t)(&P7OUT)
#define P7DIR_ADDR   (uint16_t)(&P7DIR)

#if defined(PORT7_VECTOR)
#define P7IFG_ADDR   (uint16_t)(&P7IFG)
#define P7IES_ADDR   (uint16_t)(&P7IES)
#define P7IE_ADDR    (uint16_t)(&P7IE )
#else
#define P7IFG_ADDR   (uint16_t)(0xFFFF)
#define P7IES_ADDR   (uint16_t)(0xFFFF)
#define P7IE_ADDR    (uint16_t)(0xFFFF)
#endif /*defined(PORT7_VECTOR)*/

#define P7SEL_ADDR   (uint16_t)(&P7SEL)
#define P7SEL2_ADDR  (uint16_t)(&P7SEL2)
#define P7REN_ADDR   (uint16_t)(&P7REN)

#endif /*__MSP430_HAS_PORT7_R__*/

#if defined(__MSP430_HAS_PORT8_R__)

#define P8IN_ADDR    (uint16_t)(&P8IN)
#define P8OUT_ADDR   (uint16_t)(&P8OUT)
#define P8DIR_ADDR   (uint16_t)(&P8DIR)

#if defined(PORT8_VECTOR)
#define P8IFG_ADDR   (uint16_t)(&P8IFG)
#define P8IES_ADDR   (uint16_t)(&P8IES)
#define P8IE_ADDR    (uint16_t)(&P8IE )
#else
#define P8IFG_ADDR   (uint16_t)(0xFFFF)
#define P8IES_ADDR   (uint16_t)(0xFFFF)
#define P8IE_ADDR    (uint16_t)(0xFFFF)
#endif /*defined(PORT8_VECTOR)*/

#define P8SEL_ADDR   (uint16_t)(&P8SEL)
#define P8SEL2_ADDR  (uint16_t)(&P8SEL2)
#define P8REN_ADDR   (uint16_t)(&P8REN)

#endif /*__MSP430_HAS_PORT8_R__*/

#if defined(__MSP430_HAS_PORT9_R__)

#define P9IN_ADDR    (uint16_t)(&P9IN)
#define P9OUT_ADDR   (uint16_t)(&P9OUT)
#define P9DIR_ADDR   (uint16_t)(&P9DIR)

#if defined(PORT9_VECTOR)
#define P9IFG_ADDR   (uint16_t)(&P9IFG)
#define P9IES_ADDR   (uint16_t)(&P9IES)
#define P9IE_ADDR    (uint16_t)(&P9IE )
#else
#define P9IFG_ADDR   (uint16_t)(0xFFFF)
#define P9IES_ADDR   (uint16_t)(0xFFFF)
#define P9IE_ADDR    (uint16_t)(0xFFFF)
#endif /*defined(PORT9_VECTOR)*/

#define P9SEL_ADDR   (uint16_t)(&P9SEL)
#define P9SEL2_ADDR  (uint16_t)(&P9SEL2)
#define P9REN_ADDR   (uint16_t)(&P9REN)

#endif /*__MSP430_HAS_PORT9_R__*/



#if (!defined(__MSP430_BASEADDRESS_PORT1_R__))

#define __MSP430_BASEADDRESS_PORT1_R__ 0x0020
#define OFS_P1SEL2             0x0021

#endif
#if (!defined(__MSP430_BASEADDRESS_PORT2_R__))

#define __MSP430_BASEADDRESS_PORT2_R__ 0x0028
#define OFS_P2SEL2             0x001A

#endif
#if (!defined(__MSP430_BASEADDRESS_PORT3_R__))

#define __MSP430_BASEADDRESS_PORT3_R__ 0x0018
#define OFS_P3SEL2             0x002B

#endif
#if (!defined(__MSP430_BASEADDRESS_PORT4_R__))

#define __MSP430_BASEADDRESS_PORT4_R__ 0x001C
#define OFS_P4SEL2             0x0028

#endif

/***************************Public Type Definitions********************************/
typedef struct{
     uint16_t Base;
     uint16_t PxIN;
     uint16_t PxOUT;
     uint16_t PxDIR;
#ifdef __msp430
     uint16_t PxIFG;
     uint16_t PxIES;
     uint16_t PxIE;
     uint16_t PxSEL;
     uint16_t PxSEL2;
     uint16_t PxREN;
#endif
}GPIO_PortAddr;

/***************************Public Data Definitions********************************/



/***************************Public Function Definitions****************************/


#endif /* REG_ACCESS_H_ */
