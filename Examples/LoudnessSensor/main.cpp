#include <rtos.h>
#include <timer.h>
#include <Loka.h>
#include <console.h>


// connected sensor to the port 1 (A0)


const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;


void setup() {

	//Disable board watchdog
	Board::disableWatchdog();
	console_close();
	//serial port reset
	Board::set24MHzBoosterOnMode();
	console_init();

}



void loop(){

	unsigned long startMillis= millis();  // Start of sample window
	unsigned int peakToPeak = 0;   // peak-to-peak level

	unsigned int signalMax = 0;
	unsigned int signalMin = 1024;

	while (millis() - startMillis < sampleWindow)
	{
		sample = Loka::analogRead(A0);
		if (sample < 1024)  // toss out spurious readings
		{
			if (sample > signalMax)
			{
				signalMax = sample;  // save just the max levels
			}
			else if (sample < signalMin)
			{
				signalMin = sample;  // save just the min levels
			}
		}
	}

	peakToPeak = signalMax - signalMin;
	double volts = (peakToPeak * 2.5) / 1024;

	console_debug("Loudness Level: %f volts - PeakToPeak %d max %d min %d", volts, peakToPeak, signalMax, signalMin);

	//Sleep for 1 second
	delay(30);

}

int main(void) {

	//Board init with debug enabled
	tc_rtos_init(1);

	setup();

	for(;;)
		loop();

	//return 0;

}
