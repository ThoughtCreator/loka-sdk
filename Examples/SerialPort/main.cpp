#include <rtos.h>
#include <timer.h>
#include <Loka.h>
#include <console.h>

#include <stdlib.h>
#include <string.h>

#include <drivers/SerialPort.h>

//Buffer array for data receive over serial port
unsigned char buffer[64];
int count = 0;

//SerialPort instance
SerialPort serial;


void printBuffer(){

	if(count>0){
		serial.write("Echo: ");
		for(int i = 0; i< count; i++){
			serial.write(buffer[i]);
		}
		serial.write("\r\n");
	 }

}


void setup() {

	//Disable board watchdog
	Loka::disableWatchdog();

	//Initialize Serial Port with baudrate 115200
	serial.init(0, 115200);
	serial.write("Loka Serial Port Sample! Type something and press Enter!\r\n");

}

void loop(){

	if(serial.available()){
		while(serial.available()){				// reading data into char array

			buffer[count]=serial.read();			// writing data into array

			if(buffer[count] == '\n' || buffer[count] == '\r'){

				count++;
				buffer[count] = '\0';

				printBuffer();

				count = 0;
				break;
			}


			if(count == 63) {

				buffer[count] = '\0';

				printBuffer();

				count = 0;
				break;
			}

			count++;
		}

	}

}


int main(void) {

	//Board init with debug disabled
	tc_rtos_init(0);

	setup();

	for(;;)
		loop();


	//return 0;

}
