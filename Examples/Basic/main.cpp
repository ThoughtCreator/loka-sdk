#include <rtos.h>
#include <timer.h>
#include <Loka.h>
#include <console.h>

#include <drivers/InputOutput.h>

void setup() {

    //Print Hello World
    console_debug("Hello World!");
    Board::pinMode(LED, OUTPUT);

}

void loop(){

	Board::digitalWrite(LED, HIGH);
	sleep(1);
	Board::digitalWrite(LED, LOW);
	sleep(1);

}



int main(void) {

	//Board init with debug enabled
	tc_rtos_init(1);

    setup();

    for(;;)
        loop();


    //return 0;

}
