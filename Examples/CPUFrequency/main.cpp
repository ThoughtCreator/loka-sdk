#include <rtos.h>
#include <timer.h>
#include <Loka.h>
#include <console.h>

void setup() {

    //Disable board watchdog
    Loka::disableWatchdog();

}

void loop(){

    //Read the board current CPU frequency
    unsigned long freq =  Loka::getCurrentFrequency();

    //Print the value and sleep for 1 second
    console_debug("Current Frequency: %lu", freq);
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
