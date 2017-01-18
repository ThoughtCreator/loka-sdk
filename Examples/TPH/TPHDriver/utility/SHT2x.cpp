/*
  SHT2x - A Humidity Library for Arduino.

  Supported Sensor modules:
    SHT21-Breakout Module - http://www.moderndevice.com/products/sht21-humidity-sensor
    SHT2x-Breakout Module - http://www.misenso.com/products/001

  Created by Christopher Ladden at Modern Device on December 2009.
  Modified by Paul Badger March 2010
  
  Modified by www.misenso.com on October 2011:
    - code optimisation
    - compatibility with Arduino 1.0

 * This file is part of Sodaq_SHT2x.
 *
 * Sodaq_SHT2x is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of
 * the License, or(at your option) any later version.
 *
 * Sodaq_SHT2x is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with Sodaq_SHT2x.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#include "SHT2x.h"

#include <stdint.h>


typedef enum {
    eSHT2xAddress = 0x80,
} HUM_SENSOR_T;

typedef enum {
    eTempHoldCmd        = 0xE3,
    eRHumidityHoldCmd   = 0xE5,
    eTempNoHoldCmd      = 0xF3,
    eRHumidityNoHoldCmd = 0xF5,
} HUM_MEASUREMENT_CMD_T;


/******************************************************************************
 * Global Functions
 ******************************************************************************/

/**********************************************************
 * GetHumidity
 *  Gets the current humidity from the sensor.
 *
 * @return float - The relative humidity in %RH
 **********************************************************/
float SHT2x::getHumidity(void)
{
    float value = readSensor(eRHumidityHoldCmd);
    if (value == 0) {
        return 0;                       // Some unrealistic value
    }
    return -6.0 + 125.0 / 65536.0 * value;
}

/**********************************************************
 * GetTemperature
 *  Gets the current temperature from the sensor.
 *
 * @return float - The temperature in Deg C
 **********************************************************/
float SHT2x::getTemperature(void)
{
    float value = readSensor(eTempHoldCmd);
    if (value == 0) {
        return -273;                    // Roughly Zero Kelvin indicates an error
    }
    return -46.85 + 175.72 / 65536.0 * value;
}


/******************************************************************************
 * Private Functions
 ******************************************************************************/

uint16_t SHT2x::readSensor(uint8_t command)
{
    uint16_t result;

    //request comand:
    SoftwareI2C::start(eSHT2xAddress);
    SoftwareI2C::write(command);

   SoftwareI2C::repStart(eSHT2xAddress | 0x01);

    // wait for the device compute the response
    delay(150);


    //Store the result
    result = (SoftwareI2C::read(false) << 8) | SoftwareI2C::read(true);
    result &= ~0x0003;   // clear two low bits (status bits)
    SoftwareI2C::stop();

    return result;
}


