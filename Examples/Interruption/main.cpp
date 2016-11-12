#include <rtos.h>
#include <timer.h>
#include <Loka.h>
#include <console.h>
#include <interruptions.h>

int flag = 0;

static void callback(void){

	//Clear the intrruption flags
	intClear(BUTTON);

	//Sets the flag as true
	flag = 1;

}

void setup() {

	//Set GPIO pin mode as INPUT
	Loka::pinMode(BUTTON, INPUT);

	//Matched the callback function with the GPIO interruption pin
	intConnect(BUTTON, callback);

	//Sets the edge that will trigger the interruption
	intSetEdge(BUTTON, RISING);

	//enables the interruption
	intEnable(BUTTON);



}

void loop(){

	console_debug("Sleeping in low power mode!!");

	//Enter in low power mode for unlimited time
	Loka::setLowPowerMode(0);

	if(flag == 1) {

		//Print the message after the interruption being triggered
		console_debug("Interruption!!");
		flag = 0;

		//Sleep 2 seconds
		sleep(2);
	}

}

int main(void) {

    //Board init with debug enabled
    tc_rtos_init(1);

    setup();
    Loka::disableWatchdog();

    for(;;)
        loop();

    //return 0;

}

