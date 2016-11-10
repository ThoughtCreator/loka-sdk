/*
 * LIS4DE.h
 *
 *  Created on: Oct 12, 2016
 *      Author: pedro
 */

#include <stdlib.h>
#include <stdint.h>


#ifndef INCLUDE_TC_RTOS_LIS4DE_H_
#define INCLUDE_TC_RTOS_LIS4DE_H_



typedef enum
{
	LIS3DE_RANGE_16_G         = 0b11,   // +/- 16g
	LIS3DE_RANGE_8_G           = 0b10,   // +/- 8g
	LIS3DE_RANGE_4_G           = 0b01,   // +/- 4g
	LIS3DE_RANGE_2_G           = 0b00    // +/- 2g (default value)
} LIS3DE_range_t;

typedef enum
{
	LIS3DE_AXIS_X         = 0x0,
	LIS3DE_AXIS_Y         = 0x1,
	LIS3DE_AXIS_Z         = 0x2
} LIS3DE_axis_t;


/* Used with register 0x2A (LIS3DE_REG_CTRL_REG1) to set bandwidth */
typedef enum
{
	LIS3DE_DATARATE_400_HZ     = 0b0111, //  400Hz
	LIS3DE_DATARATE_200_HZ     = 0b0110, //  200Hz
	LIS3DE_DATARATE_100_HZ     = 0b0101, //  100Hz
	LIS3DE_DATARATE_50_HZ      = 0b0100, //   50Hz
	LIS3DE_DATARATE_25_HZ      = 0b0011, //   25Hz
	LIS3DE_DATARATE_10_HZ      = 0b0010, // 10 Hz
	LIS3DE_DATARATE_1_HZ       = 0b0001, // 1 Hz
	LIS3DE_DATARATE_POWERDOWN  = 0,
	LIS3DE_DATARATE_LOWPOWER_1K6HZ  = 0b1000,
	LIS3DE_DATARATE_LOWPOWER_5KHZ  =  0b1001,

} LIS3DE_dataRate_t;

class LIS3DE {
public:


	static int init();

	static  void setRange(LIS3DE_range_t range);
	static  int getRange(void);

	static void setDataRate(LIS3DE_dataRate_t dataRate);
	static LIS3DE_dataRate_t getDataRate(void);

	static int getTemperature();


	static void setWakeUp(uint8_t itr, uint8_t thresh, uint8_t timelimit = 1);
	static char getWakeUp();

	static  void setClick(uint8_t c, uint8_t clickthresh, uint8_t duration = 20, uint8_t timelatency = 30, uint8_t timewindow = 20);
	static  uint8_t getClick(void);


	static int8_t x, y, z;
	static  float x_g, y_g, z_g;

};

typedef LIS3DE Accelerometer;




#endif /* INCLUDE_TC_RTOS_LIS4DE_H_ */
