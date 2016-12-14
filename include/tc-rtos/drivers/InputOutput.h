/*
 * InputOutput.h
 *
 *  Created on: Oct 13, 2016
 *      Author: pedro
 */

#ifndef INCLUDE_TC_RTOS_DRIVERS_INPUTOUTPUT_H_
#define INCLUDE_TC_RTOS_DRIVERS_INPUTOUTPUT_H_

#include <stdint.h>


typedef struct { uint8_t port; uint8_t pin; } digio;


enum {
    FALLING,
    RISING
};


enum {
	INPUT,
	OUTPUT,
	INPUT_PULLUP
};

enum {
	HIGH,
	LOW
};


static digio IO0 = {5,0};
static digio IO1 = {5,1};
static digio IO2 = {1,6};
static digio IO3 = {1,7};
static digio IO4 = {3,2};
static digio IO5 = {3,4};
static digio IO6 = {3,3};
static digio IO7 = {2,7};
static digio BUTTON = {1,1};
static digio LED = {4,0};
static digio ACCELEROMETER = {1,3};
static digio A0 = {5,0};
static digio A1 = {5,1};



#endif /* INCLUDE_TC_RTOS_DRIVERS_INPUTOUTPUT_H_ */
