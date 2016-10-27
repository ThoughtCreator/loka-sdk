#include <rtos.h>
#include <timer.h>
#include <Loka.h>
#include <console.h>

#include <stdio.h>
#include <stdlib.h>

#include <interruptions.h>


digio int_pin = IO1;
int flag = 0;

ISR_FUNC_PTR callback(){

	//Sets the flag as true
	flag = 1;

	//Clear the intrruption flags
	intClear(int_pin);
	return 0;

}


void setup()
{
	//Set GPIO pin mode as INPUT
	Loka::pinMode(int_pin, INPUT);

	//Matched the callback function with the GPIO interruption pin
	intConnect(int_pin, callback());

	//Sets the edge that will trigger the interruption
	intSetEdge(int_pin, RISING);

	//enables the interruption
	intEnable(int_pin);

}


void loop()
{
	//Enter in low power mode for unlimited time
	Loka::setLowPowerMode(0);

	if(flag){

		//Print the message after the interruption being triggered
		console_debug("Switched / Button Pressed / Movement Detected!");
		flag = 0;

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
