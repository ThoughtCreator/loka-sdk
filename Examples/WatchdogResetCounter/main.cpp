#include <rtos.h>
#include <timer.h>
#include <Loka.h>
#include <console.h>

int count = 0;

void setup() {

}


void loop(){

	//Print the message
	console_debug("Program is still Running... Count: %d", count);
	count++;

	//Reset the watchdog counter
	Loka::watchdogReset();

	//Sleep for 1 second
	delay(10000);

}

int main(void) {

    //Board init with debug enabled
    tc_rtos_init(1);

    setup();

    for(;;)
        loop();

    //return 0;

}

