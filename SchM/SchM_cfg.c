/*
 * SchM_cfg.c
 *
 *  Created on: May 15, 2019
 *      Author: dumitru
 */

#include "schm_types.h"
#include "main.h"

const SchMConfigType SchM_BootCfg =
{
 .InitHook = MainPlatformInit,
 .ShutdownHook = NULL_PTR,
 .ErrorHook = NULL_PTR
};
