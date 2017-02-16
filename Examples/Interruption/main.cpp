#include <rtos.h>
#include <timer.h>
#include <Loka.h>
#include <console.h>
#include <interruptions.h>

int flag = 0;

static void callback1(void){

	//Clear the intrruption flags
	intClear(BUTTON);

	//Sets the flag as true
	flag = 1;

}

static void callback2(void){

	//Clear the intrruption flags
	intClear(BUTTON);

	//Sets the flag as true
	flag = 0;

}

void setup() {

	//Disable board watchdog
	Loka::disableWatchdog();

	//Set GPIO pin mode as INPUT
	Loka::pinMode(BUTTON, INPUT);

	//Matched the callback function with the GPIO interruption pin
	intConnect(BUTTON, callback1);

	//Sets the edge that will trigger the interruption
	intSetEdge(BUTTON, RISING);

	//enables the interruption
	intEnable(BUTTON);



}

void loop(){

	console_debug("Sleeping in low power mode!!");

	//Enter in low power mode for unlimited time
	Loka::setLowPowerMode(3600);

	if(flag == 1) {

		//Print the message after the interruption being triggered
		console_debug("PRESS!!");

		intDisable(BUTTON);


		intConnect(BUTTON, callback2);

			//Sets the edge that will trigger the interruption
			intSetEdge(BUTTON, FALLING);

			//enables the interruption
			intEnable(BUTTON);

	}

	if(flag == 0) {

			//Print the message after the interruption being triggered
			console_debug("UNPRESS!!");


			intDisable(BUTTON);


			intConnect(BUTTON, callback1);

				//Sets the edge that will trigger the interruption
				intSetEdge(BUTTON, RISING);

				//enables the interruption
				intEnable(BUTTON);


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

