/*
 * fls_hw.h
 *
 *  Created on: May 14, 2019
 *      Author: dumitru
 */

#ifndef FLS_HW_H_
#define FLS_HW_H_

#include "fls_types.h"

void Fls_HwInit(uint8_t clkDiv,FlsClkSourceEnum source);
void Fls_SetClkSource(FlsClkSourceEnum source);
FlsClkSourceEnum Fls_GetClkSource(void);
void Fls_SetClkDiv(uint8_t divider);
uint8_t Fls_GetClkDiv(void);
bool IsFlashControllerBusy(void);
void SetFlashWLock(void);
void ReleaseFlashWLock(void);
void EmergencyExit(void);
void EnableFlashWrite(void);
void DisableFlashWrite(void);
volatile void EnableFlashBlockWrite(void);
volatile void DisableFlashBlockWrite(void);
void Fls_EnableErase(void);
void Fls_DisableErase(void);
bool IsFlsWaiting(void);
bool isAccessViolated(void);

#endif /* FLS_HW_H_ */
