#include <rtos.h>
#include <timer.h>
#include <Loka.h>
#include <console.h>

#include <drivers/LIS3DE.h>

void setup() {

    //Disable board watchdog
    Loka::disableWatchdog();

    //Initialize LIS3DE module
    LIS3DE::init(1);

}

void loop(){

    //Read the board Temperature
    double temp = Loka::getTemperature();

    //Print the value and sleep for 1 second
    console_debug("Temp: %lf", temp);

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

