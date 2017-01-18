#include <rtos.h>
#include <timer.h>
#include <Loka.h>
#include <console.h>

void setup() {

    //Disable board watchdog
    Board::disableWatchdog();
    console_close();
    //must reset the serial port every time that freq changes
    Board::set24MHzBoosterOnMode();
    console_init();
}

void loop(){


	// connected to the port 1 (A0)
    // Read and print de analog Value for Pin A0 (value between 0 and 1023, from 0V to 2.5V)
    console_debug("Light Level: %u", Loka::analogRead(A0));

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
