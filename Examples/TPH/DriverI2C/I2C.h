/*
 * I2c.h
 *
 *  Created on: 05/01/2017
 *      Author: rafael.pires
 */

#ifndef DRIVERI2C_I2C_H_
#define DRIVERI2C_I2C_H_

#include <inttypes.h>
#include <drivers/InputOutput.h>
#include <Loka.h>
#include <stdlib.h>
#include <msp430.h>
#include <timer.h>



#define I2C_READ 1
#define I2C_WRITE 0
#define DELAY 5*24 // delay in microseconds
#define BUFFER_LENGTH 32

class SoftwareI2C {



 public:

  static bool write(uint8_t value);
  static uint8_t read(bool last);
  static bool start(uint8_t addr);
  static bool repStart(uint8_t addr);
  static bool init(digio sda, digio scl);
  static uint8_t read8(uint8_t addr, uint8_t device);
  static uint16_t read16(uint8_t addr, uint8_t device);
  static uint8_t * readBytes(uint8_t addr, uint8_t n, uint8_t device);
  static bool write8( uint8_t addr, uint8_t device ,uint8_t byte);
  static bool write16(uint8_t addr , uint8_t device,uint8_t byte0, uint8_t byte1);
  static void stop(void);


  bool error;

};




#endif /* DRIVERI2C_I2C_H_ */
