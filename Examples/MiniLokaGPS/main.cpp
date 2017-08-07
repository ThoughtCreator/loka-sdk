#include <rtos.h>
#include <timer.h>
#include <Loka.h>
#include <console.h>


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <drivers/SerialPort.h>
#include <SigfoxProtocol.h>

#include "TinyGPS.h"


SerialPort serial;
int32_t lastSend = 0;
TinyGPS gps;

char buf[32];

void setup()
{
	//Disable board watchdog
	Loka::disableWatchdog();
	Board::set24MHzBoosterOnMode();

	//Initialize Serial Port with baudrate 9600
	serial.init(0, 9600);
	serial.write("Ready to capture GPS data\r\n");

	Board::pinMode(LED, OUTPUT);
	Board::digitalWrite(LED, LOW);

	SigfoxProtocol::init(RCZ1);
}


void loop()
{

	bool newData = false;
	unsigned long chars;
	unsigned short sentences, failed;

	// For one second we parse GPS data and report some key values
	for (unsigned long start = millis(); millis() - start < 1000;)
	{
		while (serial.available())
		{
			char c = serial.read();
			// Serial.write(c); // uncomment this line if you want to see the GPS data flowing
			if (gps.encode(c)) // Did a new valid sentence come in?
				newData = true;
		}
	}

	unsigned long age;
	if (newData)
	{
		float flat, flon;
		gps.f_get_position(&flat, &flon, &age);

		if (flat != TinyGPS::GPS_INVALID_F_ANGLE && flon != TinyGPS::GPS_INVALID_F_ANGLE ) {
			serial.write("LAT=");
			//serial.write(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
			sprintf(buf, "%f", flat);
			serial.write(buf);




			serial.write(" LON=");
			sprintf(buf, "%f", flon);
			serial.write(buf);
			serial.write("\r\n");


			serial.write(" ALT = ");
			sprintf(buf, "%f", gps.f_altitude());
			serial.write(buf);
			serial.write("\r\n");

			if (getTime() - lastSend > (int32_t) 60) {
				SigfoxProtocol::sendGPSPosition(flat,flon,(int) (gps.f_altitude()/1000));
				lastSend = getTime();
				serial.write("Sent location by sigfox");
			}
		}


		/**
		serial.write(" SAT=");
		serial.write(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
		serial.write(" PREC=");
		serial.write(gps.hdop() == TinyGPS::GPS_INVALID_HDOP ? 0 : gps.hdop());
		//GPS mode
		serial.write(" Constellations=");
		serial.write(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0 : gps.constellations());
		 */
	}

	/**
	//satellites in view
	uint32_t* satz = gps.trackedSatellites();
	uint8_t sat_count = 0;
	for(int i=0;i<24;i++)
	{
		if(satz[i] != 0)    //exclude zero SNR sats
		{
			sat_count++;
			byte strength = (satz[i]&0xFF)>>1;
			byte prn = satz[i]>>8;
			sprintf(buf, "PRN %d: ", prn);
			serial.write(buf);
			serial.write(strength);
			serial.write("dB");
			serial.write("\r\n");
		}
	}
	 */

	//date time
	int year;
	uint8_t month, day, hour, minutes, second, hundredths;
	gps.crack_datetime(&year, &month, &day, &hour, &minutes, &second, &hundredths, &age);
	sprintf(buf,"GPS time: %d/%02d/%02d %02d:%02d:%02d", year, month, day, hour, minutes, second);
	serial.write(buf);
	serial.write("\r\n");


	gps.stats(&chars, &sentences, &failed);
	/**
	serial.write(" CHARS=");
	serial.write(chars);
	serial.write(" SENTENCES=");
	serial.write(sentences);
	serial.write(" CSUM ERR=");
	serial.write(failed);
	serial.write("\r\n");

	 */

	if (chars == 0)
		serial.write("** No characters received from GPS: check wiring **\r\n");


	if (getTime() - lastSend > (int32_t)  60) {

		double temp = Loka::getTemperature();
		SigfoxProtocol::sendAnalogValue(102,temp);
		serial.write("Sent temperature by sigfox");
		lastSend = getTime();
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
