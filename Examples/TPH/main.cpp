#include <rtos.h>
#include <timer.h>
#include <Loka.h>
#include <console.h>
#include "TPHDriver/TPH.h"



void setup() {

    //Disable board watchdog
    Board::disableWatchdog();

    console_close();
    Board::set24MHzBoosterOnMode();
    console_init();

    // This sensor must be connected to the port P9, doesnt work on any other ports.

    TPH::begin(0); // mode== oversampling

}

void loop(){

	console_debug("TemperatureBMP: %.2f C",TPH::readTemperatureBMP());

	console_debug("TemperatureSHT: %.2f C",TPH::readTemperatureSHT());

	console_debug("Temperature: %.2f C",TPH::readTemperature());

	console_debug("Pressure: %.2f mBar",TPH::readPressure());

	console_debug("Humidity:  %.2f %",TPH::readHumidity());

    //Sleep for 1 second
    sleep(5);

}

int main(void) {

    //Board init with debug enabled
    tc_rtos_init(1);

    setup();

    for(;;)
        loop();

    //return 0;

}
