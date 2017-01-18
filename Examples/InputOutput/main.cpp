#include <rtos.h>
#include <timer.h>
#include <Loka.h>
#include <console.h>

#include <drivers/InputOutput.h>

void setup() {

	//Disable board watchdog
	Loka::disableWatchdog();

	Board::pinMode(LED, OUTPUT);


	console_close();
	// Led Consumption needs the booster On
	Board::set24MHzBoosterOnMode();
	console_init();
}

void loop(){

	Board::digitalWrite(LED, HIGH);
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
