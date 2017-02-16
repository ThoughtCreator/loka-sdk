#include <rtos.h>
#include <timer.h>
#include <Loka.h>
#include <console.h>
#include <interruptions.h>
#include <SigfoxProtocol.h>
#include <drivers/InputOutput.h>


#define MOVE_DIGITAL_PORT 101
int hall = 0;


static void deviceHallClose(void) {
	intClear(HALL);
	hall = 1;
}

static void deviceHallOpen(void) {
	intClear(HALL);
	hall = 0;
}



void setup() {

	//Disable board watchdog
	Loka::disableWatchdog();

	Board::pinMode(HALL, INPUT);
	intConnect(HALL, deviceHallClose);
	intSetEdge(HALL, RISING);
	intEnable(HALL);


	SigfoxProtocol::init(RCZ2);

}

void loop(){

	Board::setLowPowerMode(9999); //gambi for now


	if (hall == 1) {

		intDisable(HALL);

		SigfoxProtocol::sendGPIOValue(MOVE_DIGITAL_PORT,1);

		intConnect(HALL, deviceHallOpen);

		//Sets the edge that will trigger the interruption
		intSetEdge(HALL, FALLING);

		//enables the interruption
		intEnable(HALL);

	}



	if (hall == 0) {

		intDisable(HALL);

		SigfoxProtocol::sendGPIOValue(MOVE_DIGITAL_PORT,0);

		intConnect(HALL, deviceHallClose);

		//Sets the edge that will trigger the interruption
		intSetEdge(HALL, RISING);

		//enables the interruption
		intEnable(HALL);

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
