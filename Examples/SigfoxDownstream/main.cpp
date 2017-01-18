#include <rtos.h>
#include <timer.h>
#include <Loka.h>
#include <console.h>

#include <stdlib.h>
#include <string.h>

#include <SigfoxProtocol.h>


unsigned char message = {0x0E};
unsigned char rcvMessage[8];

//Callback function for downstream message
void * sfxCallBack(unsigned char * receivedMessage)	{
	console_debug("This callback can be used for some messages");
	return NULL;

}


void setup() {

	//Init Sigfox in RCZ2 mode
	SigfoxProtocol::init(RCZ2);

	//Register a callback for a downstream with the header (first byte) equal to 0x0E
	//The 0x0E is the time request to the TC Core
	SigfoxProtocol::registerCommand(0x60, sfxCallBack);

	console_debug("Starting Downstream sample");

}

void loop() {

	Board::disableWatchdog();

	console_debug("Try to get some downstream from sigfox");

	int bytesReceived = SigfoxProtocol::sendRawDownlinkMessage((unsigned char *) &message, 1, (unsigned char *) &rcvMessage);
	console_debug("Received %d bytes from sigfox!!", bytesReceived);
	for (int i=0; i < bytesReceived; i++) {
		console_debug("Byte %d=%x",i, rcvMessage[i]);
	}

	sleep(600);




}



int main(void) {

	//Board init with debug enabled
	tc_rtos_init(1);

	setup();

	for(;;)
		loop();


	//return 0;

}
