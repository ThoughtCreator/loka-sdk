#include <rtos.h>
#include <timer.h>
#include <Loka.h>
#include <console.h>

#include <drivers/LIS3DE.h>

void setup() {

    //Disable board watchdog
    Loka::disableWatchdog();

    LIS3DE::init();

}

void loop(){

    //Read the board Temperature
    //Print the value and sleep for 1 second
    console_debug("Temp: %f", Loka::getTemperature());
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

