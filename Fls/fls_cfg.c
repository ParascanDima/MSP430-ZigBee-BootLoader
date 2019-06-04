/*
 * fls_cfg.c
 *
 *  Created on: Apr 12, 2019
 *      Author: dumitru
 */


#include "fls_main.h"
#include "fls_hw.h"
#include "main.h"

FlashConfigType globalFlashCfg =
{
 .ClkDiv = 1,
 .source = enMCLK,
 .isLocked = true,
 .EnterCriticalSection = GlobalInterruptsEnable,
 .ExitCriticalSection = GlobalInterruptsDisnable
};
