#include <rtos.h>
#include <timer.h>
#include <Loka.h>
#include <console.h>

void setup() {

    //Disable board watchdog
    Loka::disableWatchdog();

}

void loop(){

    console_debug("Setting Low Power Mode for 10 Secs!!\r\n");

    Loka::setLowPowerMode(10);

    console_debug("Wakeup from Low Power Mode !!\r\n");


    //Sleep for 1 second
    delay(1000);

}

int main(void) {

    //Board init with debug enabled
    tc_rtos_init(1);

    setup();

    for(;;)
        loop();

}
