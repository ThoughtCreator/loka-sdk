#include <rtos.h>
#include <timer.h>
#include <Loka.h>
#include <console.h>

void setup() {

    //Disable board watchdog
    Loka::disableWatchdog();

}

void loop(){

    //Read the board input voltage
    double voltage = Loka::getInputVoltage();

    //Print the value and sleep for 1 second
    console_debug("Input Voltage: %d", voltage);
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
