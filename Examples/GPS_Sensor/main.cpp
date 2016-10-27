#include <rtos.h>
#include <timer.h>
#include <Loka.h>
#include <console.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <drivers/SerialPort.h>



unsigned char buffer[64];  // buffer array for data receive over serial port
int count=0;
SerialPort* serial = new SerialPort();

bool readCoordinates();
bool ExtractValues();
float ExtractValue(unsigned char& start);
void clearBufferArray();
float ConvertDegrees(float input);
unsigned char Skip(unsigned char start);


float longitude;
float latitude;
float altitude;
float time;
char  log[1024];



void setup()
{
	//Disable board watchdog
	Loka::disableWatchdog();

	//Initialize Serial Port with baudrate 9600
	serial->init(0, 9600);
	serial->write("Ready to capture GPS data\r\n");

}


void loop()
{

	if(readCoordinates() == true){
		serial->write("Coordinates: ");

		sprintf(&log[0], "%f", latitude);
		serial->write(log);

		serial->write(",");

		sprintf(&log[0], "%f", longitude);
		serial->write(log);

		serial->write("\r\n");
		serial->write("Altitude: ");

		sprintf(&log[0], "%f", altitude);
		serial->write(log);

		serial->write("\r\n");

		serial->write("Timestamp: ");

		sprintf(&log[0], "%f", time);
		serial->write(log);

		serial->write("\r\n");
	}
	delay(3000);
}

bool readCoordinates()
{
    bool foundGPGGA = false;						// sensor can return multiple types of data, need to capture lines that start with $GPGGA
    if (serial->available()){						// if date is coming from software serial port
        
        while(serial->available()){					// reading data into char array

            buffer[count++]=serial->read();			// writing data into array
            if(count == 64)break;

        }

        //Serial.println(count);
        //Serial.println((char*)buffer);
        foundGPGGA = count > 60 && ExtractValues();	// if we have less then 60 characters, then we have bogus input, so don't try to parse it or process the values
        clearBufferArray();							// call clearBufferArray function to clear the stored data from the array
        count = 0;									// set counter of while loop to zero
    }
    return foundGPGGA;
}

bool ExtractValues()
{
    
    unsigned char start = count;
    while(buffer[start] != '$'){					// find the start of the GPS data -> multiple $GPGGA can appear in 1 line, if so, need to take the last one.
    
        if(start == 0) break;						// it's unsigned char, so we can't check on <= 0
          start--;

    }

    start++;										// remove the '$', don't need to compare with that.

    if(start + 4 < 64 && buffer[start] == 'G' && buffer[start+1] == 'P' && buffer[start+2] == 'G' && buffer[start+3] == 'G' && buffer[start+4] == 'A'){

    	//we found the correct line, so extract the values.
    	start+=6;

    	time = ExtractValue(start);
        latitude = ConvertDegrees(ExtractValue(start) / 100);
        start = Skip(start);
        longitude = ConvertDegrees(ExtractValue(start)  / 100);
        start = Skip(start);
        start = Skip(start);
        start = Skip(start);
        start = Skip(start);
        altitude = ExtractValue(start);
        return true;

    }
    else
        return false;
}

float ExtractValue(unsigned char& start)
{
    
    unsigned char end = start + 1;
    while(end < count && buffer[end] != ',')	// find the start of the GPS data -> multiple $GPGGA can appear in 1 line, if so, need to take the last one.
        end++;
    buffer[end] = 0;							// end the string, so we can create a string object from the sub string -> easy to convert to float.
    float result = 0.0;
    if(end != start + 1)						// if we only found a ',', then there is no value.
        result = atoll((const char*)(buffer + start));
    start = end + 1;
    return result;

}

float ConvertDegrees(float input)
{
    
    float fractional = input - (int)input;
    return (int)input + (fractional / 60.0) * 100.0;

    
}


unsigned char Skip(unsigned char start)
{
    
    unsigned char end = start + 1;
    while(end < count && buffer[end] != ',')	// find the start of the GPS data -> multiple $GPGGA can appear in 1 line, if so, need to take the last one.
        end++;
    return end+1;

}

void clearBufferArray()							// function to clear buffer array
{
    
    for (int i=0; i<count;i++){
    	buffer[i]=NULL;							// clear all index of array with command NULL
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
