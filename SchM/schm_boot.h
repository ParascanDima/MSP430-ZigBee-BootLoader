/*
 * schm_boot.h
 *
 *  Created on: May 15, 2019
 *      Author: dumitru
 */

#ifndef SCHM_BOOT_H_
#define SCHM_BOOT_H_

#include "schm_types.h"

void SchM_InitPlatform(void);
BOOT_STATE GetBootState(void);
void SetBootRequest(BootRequestType type, uint16_t addr, uint8_t* data, FlashDataType dataType, uint16_t dataSize);
void SchM_MainFunction(void);

#endif /* SCHM_BOOT_H_ */
