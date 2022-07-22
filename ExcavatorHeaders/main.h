// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef MAIN_H
#define	MAIN_H

#include <xc.h> // include processor files - each processor file is guarded. 
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "croutine.h"
#include "FreeRTOSConfig.h"

#define SAMPLE_RATE 2      //Was 1000 Was 20
#define LOOPS 2000     //2000 is good. Was 500. Was 2500. Tried 2000. Too fast. Last try: 2500. Ok but still too fast. Last try 3000
#define LOOPS_CURL 200     //Want the curl to be faster
void init(void);
void curlThread(void *pvParameters);
void boomThread(void *pvParameters);
void stickThread(void *pvParameters);
void radioThread(void *pvParameters);
int charToInt(char digit3, char digit2, char digit1, char digit0);
void delay(int numLoops);
#endif	/* XC_HEADER_TEMPLATE_H */

