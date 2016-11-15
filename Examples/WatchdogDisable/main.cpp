#include <rtos.h>
#include <timer.h>
#include <Loka.h>
#include <console.h>


void setup() {

    //Disable board watchdog
    Loka::disableWatchdog();

    console_debug("Board Will not reset...");

}


void loop(){

    delay(10000);

}

int main(void) {

    //Board init with debug enabled
    tc_rtos_init(1);

    setup();

    for(;;)
        loop();

    //return 0;

}

