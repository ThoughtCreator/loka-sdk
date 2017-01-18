
#include <rtos.h>
#include <timer.h>
#include <Loka.h>
#include <console.h>

#include <stdlib.h>
#include <string.h>

#include <drivers/InputOutput.h>

#include <msp430.h>


//defines
#define DATA_TIMEOUT 		-1
#define SENSOR_NOT_PRESENT 	-2
#define OK					 0

#define ACK_WINDOW  1000
#define TIMEOUT_WINDOW 	11561 //duration to get 4 meters

//global Vars
digio pin;

int readRange(digio pin, double * range){

	unsigned long start=0;
	unsigned long pulseDuration=0;

	//Ultrasonic Ack pins
	Board::pinMode(pin,OUTPUT);
	Board::digitalWrite(pin,LOW);
	__delay_cycles(48); // 2 micro seconds

	//Send pulse
	Board::digitalWrite(pin,HIGH);
	__delay_cycles(120); // 5 micro seconds
	Board::digitalWrite(pin,LOW);
;


	Board::pinMode(pin,INPUT_PULLUP);

	start=millis();
	while(Board::digitalRead(pin)==0){ // wait for the pulse
		if(millis()-start>=ACK_WINDOW){
			return SENSOR_NOT_PRESENT;
		}

	}

	while(Board::digitalRead(pin)==1)	// read pulse
	{
		if(pulseDuration >= TIMEOUT_WINDOW)
			return DATA_TIMEOUT;

		pulseDuration++;
	}

	*range=(double(pulseDuration)/1000000)*554;  // tunned
	if(*range>4){
		*range=4;
	}

	return OK;
}

void setup() {

	console_close();
	// turn on Booster because of the consumption, higher the clock for time precision
	Board::set24MHzBoosterOnMode();
	console_init();


	// Sensor plugged on the port 8 (IO7), for this sensor could be any port.
	pin=IO7;


}

void loop(){

	double range;

	Board::watchdogReset();

	switch(readRange(pin, &range)){

	case OK:
		console_debug("Range: %.02f m \r\n",range);
		break;
	case SENSOR_NOT_PRESENT:
		console_debug("Sensor not detected!\r\n");
		break;
	case DATA_TIMEOUT:
		console_debug("Data Timeout!\r\n");
		break;
	}

	sleep(3);

}



int main(void) {

	//Board init with debug enabled
	tc_rtos_init(1);

	setup();

	for(;;)
		loop();


	//return 0;

}
