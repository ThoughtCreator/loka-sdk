#include <rtos.h>
#include <timer.h>
#include <Loka.h>
#include <console.h>

#include <stdlib.h>
#include <string.h>

#include <drivers/InputOutput.h>

void setup() {

	Board::pinMode(LED, OUTPUT);
	console_close();
	//reset the serial Port should be done every time that freq changes
	Board::set24MHzBoosterOnMode();
	console_init();

}

void loop(){

	Board::watchdogReset();
	Board::digitalWrite(LED, HIGH);
	console_debug("Hello Loka!!");
	sleep(1);
	Board::digitalWrite(LED, LOW);
	sleep(1);

}



int main(void) {

	//Board init with debug enabled
	tc_rtos_init(1);

	setup();

	for(;;)
		loop();


	//return 0;

}
