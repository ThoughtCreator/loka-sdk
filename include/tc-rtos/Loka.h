/*
 * Board.h
 *
 *  Created on: Oct 11, 2016
 *      Author: pedro
 */

#ifndef INCLUDE_TC_RTOS_LOKA_H_
#define INCLUDE_TC_RTOS_LOKA_H_

#include <drivers/InputOutput.h>

class Loka {

public:
	Loka();
	static void reset();
	static void resetCause(char* message);

	static void set1MHzBoosterOffMode();
	static void set1MHzBoosterOnMode();
	static void set24MHzBoosterOnMode();
	static unsigned long getCurrentFrequency();


	static void eraseConfig();
	static void getConfig(const char *parm_s, char *value);
	static void getConfig(const char *parm_s, char *value,int index);
	static void setConfig(const char *param_s, const char *value_s);


	static void digitalWrite(digio gpio, uint8_t value);
	static unsigned char digitalRead(digio gpio);
	static void pinMode(digio io, uint8_t mode);


	static char* uptime(char *c);
	static char* power(char *c);
	static char* temperature(char *c);
	static char* updateFirmware(char *c);


	static double getTemperature();
	static double getInputVoltage();

	static void disableWatchdog();
	static void watchdogReset();

	static void setLowPowerMode(int duration);


};

/**
 * Loka GPIO Structure
 */


typedef Loka Board;




#endif /* INCLUDE_TC_RTOS_LOKA_H_ */
