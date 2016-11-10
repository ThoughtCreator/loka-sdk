#include <rtos.h>
#include <timer.h>
#include <Loka.h>
#include <console.h>

#include <SigfoxProtocol.h>


void setup() {

	//Disable board watchdog
	Loka::disableWatchdog();

	//Initialize Sigfox Protocol

	//RCZ1 - Europe, RCZ2 - Usa/Canada, RCZ4 - Brazil, NZ, AU, ETC
	SigfoxProtocol::init(RCZ1);

	//Send GPIO Sigfox Message
	SigfoxProtocol::sendGPIOValue(90, 0);



	console_debug("Sent Sigfox message!");

}

void loop(){

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

