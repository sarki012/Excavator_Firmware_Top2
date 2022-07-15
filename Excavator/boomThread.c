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

volatile extern char rxval[50];
void boomThread( void *pvParameters )
{
    int  i = 0, j = 0, k = 0, sampleCount = 0;
    int boom = 0, boomPrev = 0, boomDelta = 0, numDelayLoops = 0;
    int m = 0;
    int p = 0, q = 0, breakTime = 0;
    int kPrev = 0, mPrev = 0;
    PHASE1 = 2303;
    while(1)
    {
        for(i = 0; i < 45; i++)
        {
            if(rxval[i] == 'b')
            {
                boom = charToInt(rxval[i+1], rxval[i+2], rxval[i+3], rxval[i+4]);
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
                        boomDelta = boom - boomPrev;
                        //Increment Duty Cycle from the previous boom to boom
                        for(m = boomPrev; m <= boom; m++)   
                        {
                            for(p = 0; p < 35; p++)
                            {
                                if(rxval[p] == '*')
                                {
                                    breakTime = 1;
                                    break;
                                }
                            }
                            if(breakTime == 1)
                            {
                                boomPrev = m;
                                break;
                            }
                            //PDC1 = (173 - m);
                            PDC1 = (int)(173 - .14*m);
                            delay(LOOPS);
                        }
                        if(breakTime == 0)
                        {
                            boomPrev = boom;        //Save the previous value of boom
                        }
                        else if(breakTime == 1)
                        {
                            breakTime = 0;
                        }
                        sampleCount = 0;
                    }
                    else if(boomPrev > boom)    //Reverse
                    {
                        //Increment Duty Cycle from the previous boom to boom
                        for(k = boomPrev; k > boom; k--)
                        {
                            for(p = 0; p < 35; p++)
                            {
                                if(rxval[p] == '*')
                                {
                                    breakTime = 1;
                                    break;
                                }
                            }
                            if(breakTime == 1)
                            {
                                boomPrev = k;
                                break;
                            }
                          //  PDC1 = (173 - k);
                            PDC1 = (int)(173 - .14*k);
                            delay(LOOPS);
                        }
                        if(breakTime == 0)
                        {
                            boomPrev = boom;        //Save the previous value of boom
                        }
                        else if(breakTime == 1)
                        {
                            breakTime = 0;
                        }
                        sampleCount = 0;
                    } 
                }
                sampleCount++;  
                break;
            }
        }
    }    
}
