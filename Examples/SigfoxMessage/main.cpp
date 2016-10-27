#include <rtos.h>
#include <timer.h>
#include <Loka.h>
#include <console.h>

#include <SigfoxProtocol.h>


void setup() {

	//Disable board watchdog
	Loka::disableWatchdog();

	//Initialize Sigfox Protocol
	SigfoxProtocol sig;
	sig.init();

	//Send GPIO Sigfox Message
	sig.sendGPIOValue(90, 0);

	console_debug("Sent Sigfox message!");

}

void loop(){

    delay(1000);

}

int main(void) {

	//Board init with debug enabled
    tc_rtos_init(1);

    //Set board frequency to 24Mhz with Booster ON (Sigfox Radio dependency)
    Board::set24MHzBoosterOnMode();
    delay(2000);

    setup();

    for(;;)
        loop();

    //return 0;

}

