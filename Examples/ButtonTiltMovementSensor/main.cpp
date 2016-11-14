#include <rtos.h>
#include <timer.h>
#include <Loka.h>
#include <console.h>
#include <interruptions.h>

int flag = 0;

static void callback(void){

	//Clear the intrruption flags
	intClear(IO1);

	//Sets the flag as true
	flag = 1;

}

void setup() {

	//Disable board watchdog
	Loka::disableWatchdog();

	//Set GPIO pin mode as INPUT
	Loka::pinMode(IO1, INPUT);

	//Matched the callback function with the GPIO interruption pin
	intConnect(IO1, callback);

	//Sets the edge that will trigger the interruption
	intSetEdge(IO1, RISING);

	//enables the interruption
	intEnable(IO1);



}

void loop(){

	console_debug("Sleeping in low power mode!!");

	//Enter in low power mode for unlimited time
	Loka::setLowPowerMode(0);

	if(flag == 1) {

		//Print the message after the interruption being triggered
		console_debug("Switched / Button Pressed / Movement Detected!");
		flag = 0;

		//Sleep 2 seconds
		sleep(2);
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

