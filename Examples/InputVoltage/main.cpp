#include <rtos.h>
#include <timer.h>
#include <Loka.h>
#include <console.h>

void setup() {

    //Disable board watchdog
    Loka::disableWatchdog();

}

void loop(){

	//Read the board input voltage,
	float voltage = Loka::getInputVoltage();

    //Print the value
    console_debug("Input Voltage: %f", voltage);

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
