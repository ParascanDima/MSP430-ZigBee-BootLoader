/*
 * global_memmap.h
 *
 *  Created on: 27 окт. 2019 г.
 *      Author: Owner
 */

#ifndef GLOBAL_MEMMAP_H_
#define GLOBAL_MEMMAP_H_

/*--------------------Definition of Boot Loader adresses--------------------*/
#define BOOT_START               (0x2100)
#define BOOT_SIZE                (0x3000)
#define BOOT_END                 ((BOOT_START + BOOT_SIZE) - 1)

/* uC specific address */
#define BSLSIGNATURE_START       (0xFFDE)

/*--------------------Definition of application addresses--------------------*/

#define APPLICATION_KEY_START    (BOOT_END + 1)
#define APPLICATION_KEY_SIZE     (0x02)
#define APPLICATION_KEY_END      ((APPLICATION_KEY_START + APPLICATION_KEY_SIZE) - 1)

#define APPLICATION_CRC_START    (APPLICATION_KEY_END + 1)
#define APPLICATION_CRC_SIZE     (0x02)
#define APPLICATION_CRC_END      ((APPLICATION_CRC_START + APPLICATION_CRC_SIZE) - 1)

#define APPLICATION_CODE_START   (APPLICATION_CRC_END + 1)
#define APPLICATION_CODE_END     (BSLSIGNATURE_START)
#define APPLICATION_CODE_SIZE    ((APPLICATION_CODE_END - APPLICATION_CODE_START) - 1)

#endif /* GLOBAL_MEMMAP_H_ */
