/*
 * io_cnf.c
 *
 *  Created on: 18 сент. 2017 г.
 *      Author: Dumitru
 */


/**************Imports***********************************/

#include "io.h"

/**************Private Macro Definitions*****************/



/**************Private Type Definitions******************/



/**************Private Variable Definitions**************/




/**************Public Variable Definitions***************/



/**************Private Function Definitions**************/


void GPIO_UartPinConfig(void){
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1, GPIO_PIN1, GPIO_TERNARY_MODULE_FUNCTION);
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1, GPIO_PIN2, GPIO_TERNARY_MODULE_FUNCTION);

}


void GPIO_SpiPinConfig(void){
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P3, GPIO_PIN5, GPIO_PRIMARY_MODULE_FUNCTION);
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P3, GPIO_PIN4|GPIO_PIN0, GPIO_PRIMARY_MODULE_FUNCTION);

}


/**************Public Function Definitions***************/


void GPIO_PrjConfig(void){

    GPIO_SpiPinConfig();

    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P2, GPIO_PIN6|GPIO_PIN7, GPIO_PRIMARY_MODULE_FUNCTION);
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN0, GPIO_TERNARY_MODULE_FUNCTION);
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P4, GPIO_PIN0, GPIO_SECONDARY_MODULE_FUNCTION);
}
