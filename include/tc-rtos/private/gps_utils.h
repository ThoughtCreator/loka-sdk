/*
 * gps.h
 *
 *  Created on: 09/04/2015
 *      Author: Dev
 */

#ifndef LIBS_UTILS_INCLUDE_GPS_UTILS_H_
#define LIBS_UTILS_INCLUDE_GPS_UTILS_H_



#include <msp430.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <math.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct GPSPoint
{
	double latitude;
	double longitude;
	double speed;
	double timestamp;

} GPSPoint;

#define PI 3.14159265

double convert2Degrees(char* input);
long calculate_distance(double lat1, double lon1, double lat2, double lon2);
long int convertDate(char *date);

#ifdef __cplusplus
}
#endif



#endif /* LIBS_UTILS_INCLUDE_GPS_UTILS_H_ */
