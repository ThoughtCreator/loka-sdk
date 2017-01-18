/*
 * I2c.cpp
 *
 *  Created on: 05/01/2017
 *      Author: rafael.pires
 */

#include "I2C.h"
#include <console.h>


digio _sda;
digio _scl;

// Init function. Needs to be called once in the beginning.
// Returns false if SDA or SCL are low, which probably means
// a I2C bus lockup or that the lines are not pulled up.
bool SoftwareI2C::init(digio sda, digio scl) {

	_sda = sda;
	_scl = scl;
	Board::pinMode(_sda, INPUT);
	Board::pinMode(_scl, INPUT);

	if (Board::digitalRead(_sda) == 0 || Board::digitalRead(_scl) == 0){
		return false;
	}

	Board::pinMode(_sda, OUTPUT);
	Board::digitalWrite(_sda, HIGH);
	Board::pinMode(_scl, OUTPUT);
	Board::digitalWrite(_scl, HIGH);

	return true;
}



// Start transfer function: <addr> is the 8-bit I2C address (including the R/W
// bit).
//
// LSB:	0- Read
// 		1- Write
//
// Return: true if the slave replies with an "acknowledge", false otherwise
bool SoftwareI2C::start(uint8_t addr) {

	  Board::digitalWrite(_sda, LOW);
	  _delay_cycles(DELAY);
	  Board::digitalWrite(_scl, LOW);

	  return write(addr);
}



// Repeated start function: After having claimed the bus with a start condition,
// you can address another or the same chip again without an intervening
// stop condition.
// Return: true if the slave replies with an "acknowledge", false otherwise
bool SoftwareI2C::repStart(uint8_t addr) {

	  Board::digitalWrite(_sda, HIGH);
	  Board::digitalWrite(_scl, HIGH);
	  _delay_cycles(DELAY);

	  return start(addr);
}



// Issue a stop condition, freeing the bus.
void SoftwareI2C::stop(void) {

	  Board::digitalWrite(_sda, LOW);
	  _delay_cycles(DELAY);
	  Board::digitalWrite(_scl, HIGH);
	  _delay_cycles(DELAY);
	  Board::digitalWrite(_sda, HIGH);
	  _delay_cycles(DELAY);

}



// Write one byte to the slave chip that had been addressed
// by the previous start call. <value> is the byte to be sent.
// Return: true if the slave replies with an "acknowledge", false otherwise
bool SoftwareI2C::write(uint8_t value) {
	  for (uint8_t m = 0x80; m != 0; m= m/2) {

		if(m & value){
			Board::digitalWrite(_sda, HIGH);	// Send bit
		}else{
			Board::digitalWrite(_sda, LOW);	// Send bit
		}

		//fake clock
		Board::digitalWrite(_scl, HIGH);
		_delay_cycles(DELAY);
		Board::digitalWrite(_scl, LOW);

	  }

	  // get Ack or Nak
	  Board::pinMode(_sda, INPUT);
	  Board::digitalWrite(_scl, HIGH);
	  uint8_t rtn = Board::digitalRead(_sda);
	  Board::digitalWrite(_scl, LOW);
	  Board::pinMode(_sda, OUTPUT);
	  Board::digitalWrite(_sda, LOW);


	  return rtn == 0;
}



// Read one byte. If <last> is true, we send a NAK after having received
// the byte in order to terminate the read sequence.
uint8_t SoftwareI2C::read(bool last) {

	  uint8_t b = 0;

	  Board::digitalWrite(_sda, HIGH);
	  Board::pinMode(_sda, INPUT);
	  for (uint8_t i = 0; i < 8; i++) {

		b <<= 1;

		//fake clock and read bit
		_delay_cycles(DELAY);
		Board::digitalWrite(_scl, HIGH);
		if (Board::digitalRead(_sda)==1)
			b |= 1;
		Board::digitalWrite(_scl, LOW);

	  }

	  // if last==1 sends NAK
	  Board::pinMode(_sda, OUTPUT);

	  if(last == true)
		  Board::digitalWrite(_sda, HIGH);
	  else
		  Board::digitalWrite(_sda, LOW);

	  Board::digitalWrite(_scl, HIGH);
	  _delay_cycles(DELAY);
	  Board::digitalWrite(_scl, LOW);
	  Board::digitalWrite(_sda, LOW);

	  return b;
}

uint8_t SoftwareI2C::read8(uint8_t addr, uint8_t device ) {

	uint8_t byte=0;

	if(start(device)==true){

		// access specific Register
		while (write(addr)!=true){
			console_debug("Retry to access Slave Register8!");
		}


		while (repStart(device | 0x01)!=true){
				console_debug("Retry read from device!");
		}

		//Read Value from specified register
		byte=read(true);

	}

	stop();

	//console_debug("Read8:0x%x",byte);

	return byte;
}

uint16_t SoftwareI2C::read16(uint8_t addr, uint8_t device ) {

	uint8_t byte =0;
	uint16_t bytes =0;

	if(start(device)==true){

		// access specific Register
		while (write(addr)!=true){
			console_debug("Retry to access Slave Register!");
		}


		while (repStart(device | 0x01)!=true){
					console_debug("Retry read from device!");
		}

		// read first part and says that didnt not finished
		byte=read(false);

		// read the last part
		bytes= ( ((uint16_t) byte)<<8) + read(true);

	}
	//console_debug("Read16:0x%x",bytes);

	stop();
	return bytes;
}

uint8_t *  SoftwareI2C::readBytes(uint8_t addr, uint8_t n, uint8_t device) {

	uint8_t * bytes;

	// allocate n bytes
	bytes= (uint8_t * ) malloc(sizeof(uint8_t)*(n));

	if(start(device)==true){

		// access specific Register
		while (write(addr)!=true){
			console_debug("Retry to access Slave Register!");
		}

		while (repStart(device | 0x01)!=true){
			console_debug("Retry read from device!");
		}

		// read first part and says that didnt not finished
		for(int i=0; i<n ; i++){
			bytes[i]=read(false);
			//console_debug("ReadBytes:0x%x",bytes[i]);

		}


	}

	stop();

	return bytes;
}


bool SoftwareI2C::write8(uint8_t addr , uint8_t device ,uint8_t byte) {

	bool result;

	// access specific Device
	while (start(device)!=true){
		console_debug("Retry to access Slave Device!");
	}

	// access specific Register
	while (write(addr)!=true){
		console_debug("Retry to access Slave Register!");
	}

	result= write(byte);

	stop();

	return  result;
}

bool SoftwareI2C::write16(uint8_t addr ,uint8_t device, uint8_t byte0, uint8_t byte1) {

	bool result;

	// access specific Device
	while (start(device)!=true){
		console_debug("Retry to access Slave Device!");
	}

	// access specific Register
	while (write(addr)!=true){
		console_debug("Retry to access Slave Register!");
	}

	result= write(byte0) & write (byte1);

	stop();

	return  result;
}
