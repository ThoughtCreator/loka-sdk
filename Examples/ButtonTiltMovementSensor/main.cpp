#include <rtos.h>
#include <timer.h>
#include <Loka.h>
#include <console.h>
#include <interruptions.h>

int flag = 0;

//Please connet the Sensor in the GTOOVE DIGITAL P3

static void callback(void){

	//Clear the intrruption flags
	intClear(IO2);

	//Sets the flag as true
	flag = 1;

}

void setup() {

	//Disable board watchdog
	Loka::disableWatchdog();

	//Set GPIO pin mode as INPUT_PULLUP
	Loka::pinMode(IO2, INPUT_PULLUP);

	//Matched the callback function with the GPIO interruption pin
	intConnect(IO2, callback);

	//Sets the edge that will trigger the interruption
	intSetEdge(IO2, RISING);

	//enables the interruption
	intEnable(IO2);



}

void loop(){

	console_debug("Sleeping in low power mode!!");

	//Enter in low power mode for unlimited time
	Loka::setLowPowerMode(0);

	sleep(1);

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

