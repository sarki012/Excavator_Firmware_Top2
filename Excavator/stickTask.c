/*
 * File:   stickTask.c
 * Author: Erik
 *
 * Created on April 29, 2022, 4:43 PM
 */
#include <xc.h>
#include <p33ep512mc502.h>
#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOSConfig.h"
#include "main.h"

volatile extern char rxval[40];
void stickTask( void *pvParameters )
{
    int  i = 0, j = 0, k = 0, sampleCount = 0;
    int stick = 0, stickPrev = 0;
    int m = 0;
    PHASE2 = 2303;
    while(1)
    {
        for(i = 0; i < 35; i++)
        {
            if(rxval[i] == 's')
            {
                stick = charToInt(rxval[i+1], rxval[i+2], rxval[i+3]);
                //Motor Arithmitic Here
                //PHASE3 and PDC2 are for PWM3L, the bucket boom motor
                //PHASE is always 2303 to give a rising edge every 20ms
                //Max Duty Cycle is PDC = 253
                //Neutral Duty Cycle is 173
                //Min Duty Cycle is PDC = 92
                if(sampleCount == SAMPLE_RATE)     //We're only going to take the SAMPLE_RATE sample
                {
                    if(stickPrev <= stick)        //Direction
                    {
                        //Increment Duty Cycle from the previous stickPrev to stick
                        for(m = stickPrev; m <= stick; m++)   
                        {
                            PDC2 = (173 - m);
                            for(j = 0; j < LOOPS; j++);
                        }
                        stickPrev = stick;        //Save the previous value of stick
                        sampleCount = 0;
                    }
                    else if(stickPrev > stick)    //Reverse
                    {
                        //Increment Duty Cycle from the previous boom to boom
                        for(k = stickPrev; k > stick; k--)
                        {
                            PDC2 = (173 - k);
                            for(j = 0; j < LOOPS; j++);
                        }
                        stickPrev = stick;        //Save the previous value of boom
                        sampleCount = 0;
                    } 
                }
                sampleCount++;  
                break;
            }
        }
    }    
}
