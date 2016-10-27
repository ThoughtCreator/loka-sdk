/*
 * SerialPort.h
 *
 *  Created on: 14 de Set de 2013
 *      Author: Pedro Moscoso
 */

#ifndef SERIALPORT_H_
#define SERIALPORT_H_


class SerialPort {
	public:
		int init(int id);
		int init(int id, long baudRate);
		int init(int id, long baudRate, unsigned long txBuffer, unsigned long rxBuffer);

		SerialPort();
		virtual ~SerialPort();
		int write(unsigned char *buffer,int size);
		int write(char *buffer,int size);
		int write(uint8_t c);
		int write(char *buffer);
		unsigned char read();
		unsigned int available(void);

		int close();

};

#endif
