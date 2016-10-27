/*
 * interruptions.h
 *
 *  Created on: Oct 11, 2016
 *      Author: pedro
 */

#ifndef INCLUDE_TC_RTOS_INTERRUPTIONS_H_
#define INCLUDE_TC_RTOS_INTERRUPTIONS_H_

#include <msp430.h>
#include <stdint.h>
#include <drivers/InputOutput.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*ISR_FUNC_PTR)(void);





#define HAL_DIGIO_OK       0
#define HAL_DIGIO_ERROR  (~0)



/***********************************************************************************
* GLOBAL FUNCTIONS
*/

uint8_t intConnect(digio io, ISR_FUNC_PTR func);
uint8_t intEnable (digio io);
uint8_t intDisable(digio io);
uint8_t intClear  (digio io);
uint8_t intSetEdge(digio io, uint8_t edge);

#ifdef __cplusplus
}
#endif





#endif /* INCLUDE_TC_RTOS_INTERRUPTIONS_H_ */
