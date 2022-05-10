/*
 * File:   boom_task.c
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

volatile extern char rxval[20];
void boomTask( void *pvParameters )
{
    int  i = 0, j = 0, k = 0, sampleCount = 0;
    int boom = 0, boomPrev = 0;
    int m = 0;
    PHASE2 = 2303;
    while(1)
    {
        for(i = 0; i < 15; i++)
        {
            if(rxval[i] == 'b')
            {
                boom = charToInt(rxval[i+1], rxval[i+2], rxval[i+3]);
                //Motor Arithmitic Here
                //PHASE3 and PDC2 are for PWM3L, the bucket boom motor
                //PHASE is always 2303 to give a rising edge every 20ms
                //Max Duty Cycle is PDC = 253
                //Neutral Duty Cycle is 173
                //Min Duty Cycle is PDC = 92
                if(sampleCount == SAMPLE_RATE)     //We're only going to take the 100th sample
                {
                    if(boomPrev <= boom)        //Direction
                    {
                        //Increment Duty Cycle from the previous boom to boom
                        for(m = boomPrev; m <= boom; m++)   
                        {
                            PDC2 = (173 + m);
                            for(j = 0; j < LOOPS; j++);
                        }
                        boomPrev = boom;        //Save the previous value of boom
                        sampleCount = 0;
                    }
                    else if(boomPrev > boom)    //Reverse
                    {
                        //Increment Duty Cycle from the previous boom to boom
                        for(k = boomPrev; k > boom; k--)
                        {
                            PDC2 = (173 + k);
                            for(j = 0; j < LOOPS; j++);
                        }
                        boomPrev = boom;        //Save the previous value of boom
                        sampleCount = 0;
                    } 
                }
                sampleCount++;  
                break;
            }
        }
    }    
}

