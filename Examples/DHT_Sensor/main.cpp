#include <rtos.h>
#include <timer.h>
#include <Loka.h>
#include <console.h>

#include <drivers/SerialPort.h>

void setup() {

	//Disable board watchdog
	Loka::disableWatchdog();


}

void loop(){

    delay(1000);

}

int main(void) {

    //Board init with debug disabled
    tc_rtos_init(0);

    setup();

    for(;;)
        loop();

    //return 0;

}

