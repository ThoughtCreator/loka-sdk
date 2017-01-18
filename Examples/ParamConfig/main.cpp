#include <stdlib.h>

#include <rtos.h>
#include <timer.h>
#include <Loka.h>
#include <console.h>


void setup() {

	 //Disable board watchdog
	 Loka::disableWatchdog();

	 //Read the previous stored value for the paramater "abc"
	 char* value = (char*) malloc(sizeof(char)*20);
	 Loka::getConfig("abc", value);
	 console_debug("Before set config, value: abc=%s", value);

	 //Set the parameter "abc" to "new_value"
	 Loka::setConfig("abc", "new_value");

	 //Read the stored value for the paramater "abc" after the setConfig
	 char* value_after = (char*) malloc(sizeof(char)*20);
	 Loka::getConfig("abc", value_after);
	 console_debug("After set config, value: abc=%s", value_after);


}

void loop(){


}



int main(void) {

	//Board init with debug enabled
	tc_rtos_init(1);

	setup();

	for(;;)
		loop();


    //return 0;

}
