#include <rtos.h>
#include <timer.h>
#include <Loka.h>
#include <console.h>

#include <stdlib.h>
#include <string.h>

#include <drivers/InputOutput.h>

/** Connect Relay to P1 */

void setup() {

	//Set Rellay to P1
	Board::pinMode(IO0, OUTPUT);
	console_close();
	//reset the serial port
	Board::set24MHzBoosterOnMode();
	console_init();
}

void loop(){

	Board::watchdogReset();


	//Turn On
	Board::digitalWrite(IO0, HIGH);
	console_debug("Relay On!!");
	sleep(3);

	//Turn Off
	Board::digitalWrite(IO0, LOW);
	console_debug("Relay Off!!");
	sleep(3);

}



int main(void) {

	//Board init with debug enabe
	tc_rtos_init(1);

	setup();

	for(;;)
		loop();


	//return 0;

}
