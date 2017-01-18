
#include <rtos.h>
#include <timer.h>
#include <Loka.h>
#include <console.h>

#include <stdlib.h>
#include <string.h>

#include <drivers/InputOutput.h>

#include <msp430.h>


//defines
#define DHT_ERROR_NOT_PRESENT -2
#define DHT_ERROR_ACK_TOO_LONG -3
#define DHT_ERROR_CHECKSUM -4
#define DHT_ERROR_DATA_TIMEOUT -5
#define DHT_ERROR_SYNC_TIMEOUT -6

#define DHT_OK 0
#define DHT22_DATA_BIT_COUNT 41


// global Vars
float Humidity;
float Temperature;
digio pin;

int dthRead(digio pin){

	  uint8_t retryCount;
	  uint8_t bitTimes[DHT22_DATA_BIT_COUNT];
	  uint8_t checkSum, csPart1, csPart2, csPart3, csPart4;
	  int i;

	  int currentHumidity = 0;
	  int currentTemperature = 0;
	  checkSum = 0;

	  // Send the activate pulse
	  Board::digitalWrite(pin, LOW);
	  _delay_cycles(26400); // 1.1 ms
	  Board::digitalWrite(pin, HIGH);

	  Board::pinMode(pin, INPUT);

	  // Find the start of the ACK Pulse
	  retryCount = 0;
	  do
	  {
	    if (retryCount > 25) //(Spec is 20 to 40 us, 25*2 == 50 us)
	    {
	      return DHT_ERROR_NOT_PRESENT;
	    }
	    retryCount++;
	    _delay_cycles(48);
	  } while(!Board::digitalRead(pin));


	  // Find the end of the ACK Pulse
	  retryCount = 0;
	  do
	  {
	    if (retryCount > 50) //(Spec is 80 us, 50*2 == 100 us)
	    {
	      return DHT_ERROR_ACK_TOO_LONG;
	    }
	    retryCount++;
	    _delay_cycles(48);
	  } while(Board::digitalRead(pin));


	  // Read the 40 bit data stream
	  for(i = 0; i < DHT22_DATA_BIT_COUNT; i++)
	  {
	    // Find the start of the sync pulse
	    retryCount = 0;
	    do
	    {
	      if (retryCount > 35) //(Spec is 50 us, 35*2 == 70 us)
	      {
	        return DHT_ERROR_SYNC_TIMEOUT;
	      }
	      retryCount++;
	      _delay_cycles(48);
	    } while(!Board::digitalRead(pin));

			// Measure the width of the data pulse
			retryCount = 0;
			do
			{
			  if (retryCount > 50) //(Spec is 80 us, 50*2 == 100 us)
			  {
				return DHT_ERROR_DATA_TIMEOUT;
			  }
			  retryCount++;
			  _delay_cycles(48);
			} while(Board::digitalRead(pin));

			bitTimes[i] = retryCount;
	  }

	  // Now bitTimes have the number of retries (us *2)
	  // that were needed to find the end of each data bit
	  // Spec: 0 is 26 to 28 us
	  // Spec: 1 is 70 us
	  // bitTimes[x] <= 11 is a 0
	  // bitTimes[x] >  11 is a 1
	  // Note: the bits are offset by one from the data sheet, not sure why
	  for(i = 0; i < 16; i++)
	  {
	    if(bitTimes[i + 1] > 11)
	    {
	      currentHumidity |= (1 << (15 - i));
	    }
	  }
	  for(i = 0; i < 16; i++)
	  {
	    if(bitTimes[i + 17] > 11)
	    {
	      currentTemperature |= (1 << (15 - i));
	    }
	  }
	  for(i = 0; i < 8; i++)
	  {
	    if(bitTimes[i + 33] > 11)
	    {
	      checkSum |= (1 << (7 - i));
	    }
	  }


	  csPart1 = currentHumidity >> 8;
	  csPart2 = currentHumidity & 0xFF;
	  csPart3 = currentTemperature >> 8;
	  csPart4 = currentTemperature & 0xFF;

	  if(checkSum == ((csPart1 + csPart2 + csPart3 + csPart4) & 0xFF))
	  {
		  Humidity = (currentHumidity & 0x7FFF) * 0.1;
		  if(currentTemperature & 0x8000)
		  {
			// Below zero, non standard way of encoding negative numbers!
			// Convert to native negative format.
			  currentTemperature = -currentTemperature & 0x7FFF;

		  }
		  Temperature = currentTemperature * 0.1;

	    return DHT_OK;
	  }
	  return DHT_ERROR_CHECKSUM;
}

void setup() {

	console_close();
	// tunr on Booster because of the consumption
	Board::set24MHzBoosterOnMode();
	console_init();

	// Pin needs to start HIGH
	Board::pinMode(pin, OUTPUT);
	Board::digitalWrite(pin, HIGH);

	// Sensor plugged on the port 8 (IO7), for this sensor could be any port.
	pin=IO7;


}

void loop(){

	Board::watchdogReset();

	switch(dthRead(pin)){

	case DHT_OK:
		console_debug("Temperature: %.02f Humidity: %.02f \r\n",Temperature,Humidity);
		break;
	case DHT_ERROR_NOT_PRESENT:
		console_debug("DTH not detected!\r\n");
		break;
	case DHT_ERROR_ACK_TOO_LONG:
		console_debug("DTH Ack took too much!\r\n");
		break;
	case DHT_ERROR_CHECKSUM:
		console_debug("DTH Error on recieved Bytes!\r\n");
		break;
	case DHT_ERROR_SYNC_TIMEOUT:
		console_debug("DTH data Timeout!\r\n");
		break;
	case DHT_ERROR_DATA_TIMEOUT:
		console_debug("DTH sync Timeout!\r\n");
		break;
	}

	//ready for next sample
	Board::pinMode(pin, OUTPUT);
	Board::digitalWrite(pin, HIGH);
	sleep(3);

}



int main(void) {

	//Board init with debug enabled
	tc_rtos_init(1);

	setup();

	for(;;)
		loop();


	//return 0;

}
