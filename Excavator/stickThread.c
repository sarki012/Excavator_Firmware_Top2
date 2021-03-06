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

volatile extern char rxval[50];
void stickThread( void *pvParameters )
{
    int  i = 0, j = 0, k = 0, sampleCount = 0;
    int stick = 0, stickPrev = 0;
    int m = 0, p = 0, breakTime = 0;
    int delayPercentage = 0, numDelayLoops = 0;
    PHASE2 = 2303;
    PDC2 = 173;
    while(1)
    {
        for(i = 0; i < 45; i++)
        {
            if(rxval[i] == 'd')
            {
                delayPercentage = charToInt(rxval[i+1], rxval[i+2], rxval[i+3], rxval[i+4]);
                numDelayLoops = 500 + delayPercentage*25;
            }
            if(rxval[i] == 's')
            {
                stick = charToInt(rxval[i+1], rxval[i+2], rxval[i+3], rxval[i+4]);
                //Motor Arithmitic Here
                //PHASE3 and PDC2 are for PWM3L, the bucket boom motor
                //PHASE is always 2303 to give a rising edge every 20ms
                //Max Duty Cycle is PDC = 253
                //Neutral Duty Cycle is 173
                //Min Duty Cycle is PDC = 92
                if(sampleCount == SAMPLE_RATE)     //We're only going to take the SAMPLE_RATE sample
                {
                    if(stick > 0)
                    {
                    PDC2--;
                        delay(numDelayLoops);
                        if(PDC2 < 92)
                        {
                            PDC2 = 92;
                        }
                    }
                    else if(stick < 0)
                    {
                        PDC2++;
                        delay(numDelayLoops);
                        if(PDC2 > 253)
                        {
                            PDC2 = 253;
                        }
                    }
                    sampleCount = 0;
                    /*
                    if(stickPrev <= stick)        //Direction
                    {
                        //Increment Duty Cycle from the previous stickPrev to stick
                        for(m = stickPrev; m <= stick; m += 5)   
                        {
                            for(p = 0; p < 35; p++)
                            {
                                if(rxval[p] == '#')
                                {
                                    breakTime = 1;
                                    break;
                                }
                            }
                            if(breakTime == 1)
                            {
                                stickPrev = m;
                                break;
                            }
                          //  PDC2 = (173 - m);
                            PDC2 = (int)(173 - .14*m);
                            delay(numDelayLoops);
                        }
                        if(breakTime == 0)
                        {
                            stickPrev = stick;        //Save the previous value of stick
                        }
                        else if(breakTime == 1)
                        {
                            breakTime = 0;
                        }
                        sampleCount = 0;
                    }
                    else if(stickPrev > stick)    //Reverse
                    {
                        //Increment Duty Cycle from the previous boom to boom
                        for(k = stickPrev; k > stick; k -= 5)
                        {
                            for(p = 0; p < 35; p++)
                            {
                                if(rxval[p] == '#')
                                {
                                    breakTime = 1;
                                    break;
                                }
                            }
                            if(breakTime == 1)
                            {
                                stickPrev = k;
                                break;
                            }
                           // PDC2 = (173 - k);
                            PDC2 = (int)(173 - .14*k);
                            delay(numDelayLoops);
                        }
                        if(breakTime == 0)
                        {
                            stickPrev = stick;        //Save the previous value of stick
                        }
                        else if(breakTime == 1)
                        {
                            breakTime = 0;
                        }
                        sampleCount = 0;
                    } 
                    */
                }
                sampleCount++;  
                break;
            }
        }
    }    
}
/*
volatile extern char rxval[40];
void stickTask( void *pvParameters )
{
    int  i = 0, j = 0, k = 0, sampleCount = 0;
    int stick = 0, stickPrev = 0;
    int m = 0;
    int breakTime = 0;
    PHASE2 = 2303;
    while(1)
    {
        for(i = 0; i < 35; i++)
        {
            if(rxval[i] == '#')
            {
                break;
            }
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
                            for(j = 0; j < LOOPS; j++)
                            {
                                if(rxval[m] == '#')
                                {
                                    breakTime = 1;
                                }
                                m++;
                                if(m == 35)
                                {
                                    m = 0;
                                }
                            }
                            if(breakTime)
                            {
                                breakTime = 0;
                                break;
                            }
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
                            for(j = 0; j < LOOPS; j++)
                            {
                                if(rxval[m] == '#')
                                {
                                    breakTime = 1;
                                }
                                m++;
                                if(m == 35)
                                {
                                    m = 0;
                                }
                            }
                            if(breakTime)
                            {
                                breakTime = 0;
                                break;
                            }
                        }
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

*/