#include <rtos.h>
#include <timer.h>
#include <Loka.h>
#include <console.h>

void setup() {

    //Disable board watchdog
    Loka::disableWatchdog();

}

void loop(){

	console_close();
	Board::set1MHzBoosterOffMode();
	//reset the serial Port should be done every time that freq changes
	console_init();

	//Read the board current CPU frequency
    unsigned long freq =  Loka::getCurrentFrequency();

    //Print the value and sleep for 1 second
    console_debug("Current Frequency: %lu", freq);
    delay(1000);

	console_close();
	Board::set24MHzBoosterOnMode();
	//reset the serial Port should be done every time that freq changes
	console_init();

	//Read the board current CPU frequency
	freq =  Loka::getCurrentFrequency();
	//Print the value and sleep for 1 second
	console_debug("Current Frequency: %lu", freq);
	delay(1000);

}

int main(void) {

    //Board init with debug enabled
    tc_rtos_init(1);

    setup();

    for(;;)
        loop();

    //return 0;

}
