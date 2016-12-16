#include <rtos.h>
#include <timer.h>
#include <Loka.h>
#include <console.h>

#include <drivers/LIS3DE.h>

/** Setup sample with INTERRUPTION */
void setup() {

	console_debug("Setup accelerometer demo");

	// init accelerometer
	LIS3DE::init(1);

	/*
	 * Set click event for the accelerometer
	 * params:	 mode 0- dissable
	 * 				  1- turn on all axes & singletap
	 * 				  2- turn on all axes & doubletap
	 *
	 *  		 threshold = from 0x00 to 0x7F
	 */
	LIS3DE::setClick(2,0x28);		//on ACC side click have interruptions configured by default


	/*
	* Set wakeUp event  for the accelerometer
	* params:	interruption pin enable , thresh, timelimit
	*/
	LIS3DE::setWakeUp(0x01,0x02,0x01); 	//on ACC side wakeup interruption are enable now...


	//NOTE: to generate interruptions, is necessary to configure the interruption on the main MCU side for the ACCELEROMETER pin... See interruptions documentation

	Loka::disableWatchdog();


}

void loop(){


	if(LIS3DE::getWakeUp()){
		console_debug("ACC WakeUp Movement!");
	}

	if(LIS3DE::getClick()){
		console_debug("ACC Click Movement!");
	}


}



int main(void) {

	//Board init with debug enabled
	tc_rtos_init(1);

	setup();

	for(;;)
		loop();


	//return 0;

}
