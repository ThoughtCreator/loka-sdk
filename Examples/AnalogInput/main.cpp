#include <rtos.h>
#include <timer.h>
#include <Loka.h>
#include <console.h>

void setup() {

    //Disable board watchdog
    Loka::disableWatchdog();

}

void loop(){

    // Read and print de analog Value for Pin A0 (value between 0 and 1023, from 0V to 2.5V)
    console_debug("Analog Reading A0: %u", Loka::analogRead(A0));

    // Read and print de analog Value for Pin A1 (value between 0 and 1023, from 0V to 2,5V)
    console_debug("Analog Reading A1: %u", Loka::analogRead(A1));

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
