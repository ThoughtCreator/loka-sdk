#include <rtos.h>
#include <timer.h>
#include <Loka.h>
#include <console.h>

/*
 * Please notice that the sensor should be powered for 2 minutes before you can get acurate mesurments.
 *
 * */


void setup() {

    //Disable board watchdog
    Board::disableWatchdog();

    console_close();
    // to supply the sensor with 3V
    Board::set24MHzBoosterOnMode();
    console_init();
}

void loop(){


	// connected to the port 1 (A0) could be conneted on port2 too.
    // Read and print de analog Value for Pin A0 (value between 0 and 1023, from 0V to 2.5V)

	unsigned int airQuality = Loka::analogRead(A0);
    console_debug("Air Quality Level: %d",airQuality);

    //these thresholds could be ajusted
	if(airQuality>700){
	    console_debug("High Pollution Level!\r\n");
	}else if(airQuality>300){
	    console_debug("Low Pollution Level!\r\n");
	}else{
	    console_debug("Fresh Air!\r\n");
	}


    //Sleep for 1 second
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
