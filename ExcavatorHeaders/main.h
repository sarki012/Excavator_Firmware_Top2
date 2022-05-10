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

#define SAMPLE_RATE 100
#define LOOPS 2000
void init(void);
void curlTask(void *pvParameters);
void boomTask(void *pvParameters);
int charToInt(char digit2, char digit1, char digit0);

#endif	/* XC_HEADER_TEMPLATE_H */

