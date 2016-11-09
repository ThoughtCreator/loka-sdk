/*
 * Protocol.h
 *
 *  Created on: Oct 11, 2016
 *      Author: pedro
 */

#ifndef INCLUDE_TC_RTOS_SIGFOXPROTOCOL_H_
#define INCLUDE_TC_RTOS_SIGFOXPROTOCOL_H_

#include <stdint.h>
#include <Singleton.h>

typedef enum
{
    RCZ1 = 0,
	RCZ2 = 1,
	RCZ3 = 2,
	RCZ4 = 3
} SigfoxMode;

class SigfoxProtocol {

public:

	static void init(SigfoxMode sigfoxMode);

	static int doRegister();

	static int sendGPIOValue(int gpio, char value);
	static int sendAnalogValue(int port, double value);
	static int sendGPSPosition(double latitude, double longitude, double speed, double timestamp);

	static int sendLog(char log);
	static int sendDataLogger(int gpio, int32_t counter, int32_t time);

	static int sendWifiSimple(char *mac, int chan, int rssi, int temp, int move, double vcc);
	static int sendWifiDouble(char *mac, int chan, int rssi, int chan2, int rssi2, int move, char *mac2);
	static int sendWifiTriple(char *mac, char* mac2, char* mac3, int rssi, int rssi2, int rssi3, int move, double temperature);

	static int32_t  getLastMessageTimestamp();

	static int sendRawMessage(unsigned char *message, int size);
	static int sendRawDownlinkMessage(unsigned char *message, int size, unsigned char *response);

	static void registerCommand(char *cmd, char * f (char *));


private:

};

typedef SigfoxProtocol Protocol;



#endif /* INCLUDE_TC_RTOS_SIGFOXPROTOCOL_H_ */
