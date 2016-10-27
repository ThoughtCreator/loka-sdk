/*
 * time.h
 *
 *  Created on: Oct 6, 2016
 *      Author: pedro
 */

#ifndef INCLUDE_TIMER_H_
#define INCLUDE_TIMER_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


void sleep(unsigned long seconds);
void usleep(unsigned long milliseconds);
void delay(unsigned long milliseconds);

unsigned long millis();

void setTime(int32_t ts);
int32_t getTime();
int32_t getUptime();


#ifdef __cplusplus
}
#endif






#endif /* INCLUDE_TIMER_H_ */
