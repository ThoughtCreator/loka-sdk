/*
	BMP180.cpp
	Bosch BMP180 pressure sensor library for the Arduino microcontroller
	Mike Grusin, SparkFun Electronics

	Uses floating-point equations from the Weather Station Data Logger project
	http://wmrx00.sourceforge.net/
	http://wmrx00.sourceforge.net/Arduino/BMP085-Calcs.pdf

	Forked from BMP085 library by M.Grusin

	version 1.0 2013/09/20 initial version
	Verison 1.1.2 - Updated for Arduino 1.6.4 5/2015

	Our example code uses the "beerware" license. You can do anything
	you like with this code. No really, anything. If you find it useful,
	buy me a (root) beer someday.
*/

#include "BMP180.h"
#include <console.h>

int16_t AC1,AC2,AC3,VB1,VB2,MB,MC,MD;
uint16_t AC4,AC5,AC6;
double c5,c6,mc,md,x0,x1,x2,y0,y1,y2,p0,p1,p2;
char Oversampling=0;

char BMP180::begin(char mode)
// Initialize library for subsequent pressure measurements
{
	double c3,c4,b1;

	Oversampling=mode;

	//start I2C lib
	if (SoftwareI2C::init(IO4,IO3)==true){

		// The BMP180 includes factory calibration data stored on the device.
		// Each device has different numbers, these must be retrieved and
		// used in the calculations when taking pressure measurements.

		// Retrieve calibration data from device:

		if (SoftwareI2C::read8(0xD0,BMP180_ADDR) != 0x55){
			console_debug("Chip not Detected!!");
			return(0);				// Error reading calibration data; bad component or connection?
		}else{

			AC1=SoftwareI2C::read16(0xAA,BMP180_ADDR);
			AC2=SoftwareI2C::read16(0xAC,BMP180_ADDR);
			AC3=SoftwareI2C::read16(0xAE,BMP180_ADDR);
			AC4=SoftwareI2C::read16(0xB0,BMP180_ADDR);
			AC5=SoftwareI2C::read16(0xB2,BMP180_ADDR);
			AC6=SoftwareI2C::read16(0xB4,BMP180_ADDR);
			VB1=SoftwareI2C::read16(0xB6,BMP180_ADDR);
			VB2=SoftwareI2C::read16(0xB8,BMP180_ADDR);
			MB= SoftwareI2C::read16(0xBA,BMP180_ADDR);
			MC= SoftwareI2C::read16(0xBC,BMP180_ADDR);
			MD= SoftwareI2C::read16(0xBE,BMP180_ADDR);


			// Compute floating-point polynominals:

			c3 = 160.0 * pow(2,-15) * AC3;
			c4 = pow(10,-3) * pow(2,-15) * AC4;
			b1 = pow(160,2) * pow(2,-30) * VB1;
			c5 = (pow(2,-15) / 160) * AC5;
			c6 = AC6;
			mc = (pow(2,11) / pow(160,2)) * MC;
			md = MD / 160.0;
			x0 = AC1;
			x1 = 160.0 * pow(2,-13) * AC2;
			x2 = pow(160,2) * pow(2,-25) * VB2;
			y0 = c4 * pow(2,15);
			y1 = c4 * c3;
			y2 = c4 * b1;
			p0 = (3791.0 - 8.0) / 1600.0;
			p1 = 1.0 - 7357.0 * pow(2,-20);
			p2 = 3038.0 * 100.0 * pow(2,-36);

			// Success!
			return(1);
		}
	}else{
		console_debug("Unable to I2C start!!");
		return (0);
	}
}




bool BMP180::startTemperature(void)
// Begin a temperature reading.
{
	bool result;


	result=SoftwareI2C::write8(BMP180_REG_CONTROL,BMP180_ADDR,BMP180_COMMAND_TEMPERATURE);

	//Oversampling time... see datasheet
	delay(5);


	return result;

}


// Retrieve a previously-started temperature reading.
// Requires begin() to be called once prior to retrieve calibration parameters.
// Requires startTemperature() to have been called prior and sufficient time elapsed.
// T: external variable to hold result.
// Returns 1 if successful, 0 if I2C error.

double BMP180::getTemperature(){

	double tu, a;

	if (startTemperature()==true){

		tu=SoftwareI2C::read16(BMP180_REG_RESULT,BMP180_ADDR);


		//example from Bosch datasheet
		//tu = 27898;

		//example from http://wmrx00.sourceforge.net/Arduino/BMP085-Calcs.pdf
		//tu = 0x69EC;

		a = c5 * (tu - c6);

		return (a + (mc / (a + md)));

	}else{

		return -273.15;
	}
}

// Begin a pressure reading.
// Oversampling: 0 to 3, higher numbers are slower, higher-res outputs.
// Will return delay in ms to wait, or 0 if I2C error.
bool BMP180::startPressure(){

	bool result;


	switch (Oversampling)
	{
		case 1:
			result = SoftwareI2C::write8(BMP180_REG_CONTROL,BMP180_ADDR,BMP180_COMMAND_PRESSURE1);
			delay(8); //Oversampling time see datasheet
		break;
		case 2:

			result = SoftwareI2C::write8(BMP180_REG_CONTROL,BMP180_ADDR,BMP180_COMMAND_PRESSURE2);
			delay(14);  //Oversampling time see datasheet
		break;
		case 3:
			result = SoftwareI2C::write8(BMP180_REG_CONTROL,BMP180_ADDR,BMP180_COMMAND_PRESSURE3);
			delay(26);  //Oversampling time see datasheet
		break;
		default:
			result = SoftwareI2C::write8(BMP180_REG_CONTROL,BMP180_ADDR,BMP180_COMMAND_PRESSURE0);
			delay(5);  //Oversampling time see datasheet
		break;
	}


	return result;

}


double BMP180::getPressure(double T)
// Retrieve a previously started pressure reading, calculate abolute pressure in mbars.
// Requires begin() to be called once prior to retrieve calibration parameters.
// Requires startPressure() to have been called prior and sufficient time elapsed.
// Requires recent temperature reading to accurately calculate pressure.

// P: external variable to hold pressure.
// T: previously-calculated temperature.
// Returns 1 for success, 0 for I2C error.

// Note that calculated pressure value is absolute mbars, to compensate for altitude call sealevel().
{
	uint8_t * data;

	double pu,s,x,y,z;

	if(BMP180::startPressure()==true){

		data = SoftwareI2C::readBytes(BMP180_REG_RESULT, 3, BMP180_ADDR);


		pu = (double (data[0]) * 256.0) + double(data[1]) + (double(data[2])/256.0);

		//example from Bosch datasheet
		//pu = 23843;

		//console_debug("PU data: %f",pu);

		//example from http://wmrx00.sourceforge.net/Arduino/BMP085-Calcs.pdf, pu = 0x982FC0;
		//pu = (0x98 * 256.0) + 0x2F + (0xC0/256.0);

		s = T - 25.0;
		x = (x2 * pow(s,2)) + (x1 * s) + x0;
		y = (y2 * pow(s,2)) + (y1 * s) + y0;
		z = (pu - x) / y;

		free(data);

		return((p2 * pow(z,2)) + (p1 * z) + p0);

	}else{
		return -1;
	}
}


double BMP180::sealevel(double P, double A)
// Given a pressure P (mb) taken at a specific altitude (meters),
// return the equivalent pressure (mb) at sea level.
// This produces pressure readings that can be used for weather measurements.
{
	return(P/pow(1-(A/44330.0),5.255));
}


double BMP180::altitude(double P, double P0)
// Given a pressure measurement P (mb) and the pressure at a baseline P0 (mb),
// return altitude (meters) above baseline.
{
	return(44330.0*(1-pow(P/P0,1/5.255)));
}


