#include <rtos.h>
#include <timer.h>
#include <Loka.h>
#include <console.h>

#include <drivers/LIS3DE.h>

/** Setup sample with INTERRUPTION */
void setup() {

	console_debug("Setup accelerometer demo");

	// init accelerometer
	LIS3DE::init();

	/*
	 * On this mode the acc stores the samples in a buffer,
	 * users can set the watermark lvl for this buffer,
	 * when the number of samples pass this watermark level
	 * interruptions can be generated, or this
	 * level can be used for reference only
	 *
	 * 	params: level  from 0 to 1F;
	 * 			enable interrupt pin 0 or 1
	 */
	LIS3DE::setWatermark(0x1F,1);

	/*
	 * Sets the range for the Acc Mesurments in G's
	 * 				LIS3DE_RANGE_16_G
					LIS3DE_RANGE_8_G
					LIS3DE_RANGE_4_G
					LIS3DE_RANGE_2_G
	 *
	 */
	LIS3DE::setRange(LIS3DE_RANGE_8_G);

	/*
		 * Sets the data rate for the Acc Mesurments in G's
 				LIS3DE_DATARATE_400_HZ
				LIS3DE_DATARATE_200_HZ
				LIS3DE_DATARATE_100_HZ
				LIS3DE_DATARATE_50_HZ
				LIS3DE_DATARATE_25_HZ
				LIS3DE_DATARATE_10_HZ
				LIS3DE_DATARATE_1_HZ
				LIS3DE_DATARATE_POWERDOWN
				LIS3DE_DATARATE_LOWPOWER_1K6HZ
				LIS3DE_DATARATE_LOWPOWER_5KHZ
		 *
	*/
	LIS3DE::setDataRate(LIS3DE_DATARATE_10_HZ);


	Loka::disableWatchdog();


}

void loop(){


	LIS3DE_Aceleration * Acc;


	//Read ACC Raw info
	Acc=LIS3DE::readAxis();
	// print ACC Raw info
	console_debug("Acceletation: x:%f , y:%f , z:%f",Acc->x,Acc->y,Acc->z);

	free(Acc);

}



int main(void) {

	//Board init with debug enabled
	tc_rtos_init(1);

	setup();

	for(;;)
		loop();


	//return 0;

}
