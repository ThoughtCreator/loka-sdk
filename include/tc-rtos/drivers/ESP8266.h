/*
 * esp8266.h
 *
 *  Created on: 08/02/2016
 *      Author: Dev
 */

#ifndef DRIVERS_NETWORK_ESP8266_INCLUDE_ESP8266_H_
#define DRIVERS_NETWORK_ESP8266_INCLUDE_ESP8266_H_


#include <stdio.h>
#include <singleton.h>

typedef struct accessPoint {
	int rssi;
	int channel;
	unsigned char mac[6];
} accessPoint;

typedef struct accessPoints {
	int size;
	accessPoint **aps;
} accessPoints;


class ESP8266
{
    public:
		static void init();
		static void turnOn();
		static void turnOff();
		static int8_t sendATcommand(char* data, char* expected_answer1,  char* expected_answer2, unsigned int timeout);
		static int8_t sendSerialcommand(char* data,int size, char* expected_answer1,  char* expected_answer2, unsigned int timeout);

		static int scan(accessPoints *aps);

		static int connect();
		static int connectAP(char *SSID, char *password);

		static int openSocket(int id, char *server, int port, char *proto);
		static int closeSocket(int id);
		static int sendData(int id, unsigned char *buffer, int size);
		static int readData(int id,char *c,int size);
		static int pendingDataSize(int id);

};



#endif /* DRIVERS_NETWORK_ESP8266_INCLUDE_ESP8266_H_ */
