/*
 * fls_hw.c
 *
 *  Created on: May 14, 2019
 *      Author: dumitru
 */
#include <msp430.h>
#include "fls_hw.h"

extern FlashConfigType globalFlashCfg;

void Fls_HwInit(uint8_t clkDiv,FlsClkSourceEnum source)
{
    FCTL2 = FWKEY | (clkDiv) | (source<<6);
}

void Fls_SetClkSource(FlsClkSourceEnum source)
{
    uint16_t regVal = FCTL2 & 0x003F;
    regVal |= FWKEY|(uint8_t)(source<<6);
    FCTL2 = regVal;
}

FlsClkSourceEnum Fls_GetClkSource(void)
{
    return globalFlashCfg.source;
}


void Fls_SetClkDiv(uint8_t divider)
{
    uint16_t regVal = FCTL2 & 0x00C0;
    if (divider <= (uint8_t)0x40)
    {
        regVal |= FWKEY|(divider-1);
        FCTL2 = regVal;
        globalFlashCfg.ClkDiv = divider;
    }
}


uint8_t Fls_GetClkDiv(void)
{
    return globalFlashCfg.ClkDiv;
}

#pragma CODE_SECTION(IsFlashControllerBusy, ".TI.ramfunc")
bool IsFlashControllerBusy(void)
{
    return (bool)(FCTL3 & BUSY);
}

#pragma CODE_SECTION(SetFlashWLock, ".TI.ramfunc")
void SetFlashWLock(void)
{
    uint16_t regVal = FCTL3 & 0x00EF;
    regVal |= FWKEY|LOCK;
    FCTL3 = regVal;
}

#pragma CODE_SECTION(ReleaseFlashWLock, ".TI.ramfunc")
void ReleaseFlashWLock(void)
{
    uint16_t regVal = FCTL3 & 0x00EF;
    regVal |= FWKEY;
    FCTL3 = regVal;
}

#pragma CODE_SECTION(EmergencyExit, ".TI.ramfunc")
void EmergencyExit(void)
{
    uint16_t regVal = FCTL3 & 0x00DF;
    regVal |= FWKEY|EMEX;
    FCTL3 = regVal;
}

#pragma CODE_SECTION(EnableFlashWrite, ".TI.ramfunc")
void EnableFlashWrite(void)
{
    uint16_t regVal = FCTL1 & 0x00BF;
    regVal |= FWKEY|WRT;
    FCTL1 = regVal;
}

#pragma CODE_SECTION(DisableFlashWrite, ".TI.ramfunc")
void DisableFlashWrite(void)
{
    uint16_t regVal = FCTL1 & 0x00BF;
    regVal |= FWKEY;
    FCTL1 = regVal;
}

#pragma CODE_SECTION(EnableFlashBlockWrite, ".TI.ramfunc")
volatile void EnableFlashBlockWrite(void)
{
    uint16_t regVal = FCTL1 & 0x007F;
    regVal |= FWKEY|BLKWRT;
    FCTL1 = regVal;
}

#pragma CODE_SECTION(DisableFlashBlockWrite, ".TI.ramfunc")
volatile void DisableFlashBlockWrite(void)
{
    uint16_t regVal = FCTL1 & 0x007F;
    regVal |= FWKEY;
    FCTL1 = regVal;
}

#pragma CODE_SECTION(Fls_EnableErase, ".TI.ramfunc")
void Fls_EnableErase(void)
{
    uint16_t regVal = FCTL1 & 0x00FD;
    regVal |= FWKEY|ERASE;
    FCTL1 = regVal;
}

#pragma CODE_SECTION(Fls_DisableErase, ".TI.ramfunc")
void Fls_DisableErase(void)
{
    uint16_t regVal = FCTL1 & 0x00FD;
    regVal |= FWKEY;
    FCTL1 = regVal;
}

#pragma CODE_SECTION(IsFlsWaiting, ".TI.ramfunc")
bool IsFlsWaiting(void)
{
    return (FCTL3 & (1<<3)) ? true : false;
}

#pragma CODE_SECTION(isAccessViolated, ".TI.ramfunc")
bool isAccessViolated(void)
{
    return (FCTL3 & ACCVIFG) ? true : false;
}

