#include <rtos.h>
#include <timer.h>
#include <Loka.h>
#include <console.h>

#include <drivers/LIS3DE.h>

/** Setup sample with INTERRUPTION */
void setup() {

	console_debug("Setup accelerometer demo");
	LIS3DE::init();

	LIS3DE::setClick(2,0x28);
	LIS3DE::setWakeUp(0x0,0x02,0x01);

}

void loop(){


	if



}



int main(void) {

	//Board init with debug enabled
	tc_rtos_init(1);

	setup();

	for(;;)
		loop();


	//return 0;

}
