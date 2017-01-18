#include <rtos.h>
#include <timer.h>
#include <Loka.h>
#include <console.h>

#include <stdlib.h>
#include <string.h>

#include <drivers/ESP8266.h>

void setup() {

	char SSID [] = "T-Creator";
	char password [] = "#tcreator$wireless#";

	ESP8266::init();
	ESP8266::turnOn();
	console_close();
	console_init();
	console_debug("Wi-Fi ON!\r\n");

	ESP8266::connectAP(SSID, password);

	if(ESP8266::connect()==1){
		console_debug("Connected!\r\n");
	}

	//google. == "213.30.114.207"
	ESP8266::openSocket(0,"213.30.114.207",80,"TCP");

	Board::disableWatchdog();
}

void loop(){

	char * data;
	int size =0;


	ESP8266::sendData(0,(unsigned char*)"GET /search?q=thought+creator&start=0&num=1 HTTP/1.0\r\nUser-Agent: curl/7.37.0\r\nHost: 213.30.114.207\r\nAccept: */*\r\nConnection: keep-alive\r\n\r\n\\0",strlen("GET /search?q=thought+creator&start=0&num=1 HTTP/1.0\r\nUser-Agent: curl/7.37.0\r\nHost: 213.30.114.207\r\nAccept: */*\r\nConnection: keep-alive\r\n\r\n\\0"));

	sleep(1);

	console_debug("Response!!\r\n");

	do{
		size=ESP8266::pendingDataSize(0);
		if(size>0){
			data =  (char*) malloc(sizeof(char)*size);
			ESP8266::readData(0,data,size);
			console_debug(data);
			free(data);
		}
	}while(size!=0);


	sleep(10);

}



int main(void) {

	//Board init without debug enabled
	tc_rtos_init(1);

	setup();

	for(;;)
		loop();


	//return 0;

}

