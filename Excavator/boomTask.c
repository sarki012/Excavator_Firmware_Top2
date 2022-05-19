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

volatile extern char rxval[40];
void boomTask( void *pvParameters )
{
    int  i = 0, j = 0, k = 0, sampleCount = 0;
    int boom = 0, boomPrev = 0;
    int m = 0;
    int p = 0, q = 0, breakTime = 0;
    int kPrev = 0, mPrev = 0;
    PHASE1 = 2303;
    while(1)
    {
        for(i = 0; i < 35; i++)
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
                            PDC1 = (173 - m);
                            for(j = 0; j < LOOPS; j++);
                            
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
                            PDC1 = (173 - k);
                            for(j = 0; j < LOOPS; j++);
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

/*
volatile extern char rxval[40];
void boomTask( void *pvParameters )
{
    int  i = 0, j = 0, k = 0, m = 0, sampleCount = 0;
    int boom = 0, boomPrev = 0;
    int breakTime = 0;
    PHASE1 = 2303;
    while(1)
    {
        for(i = 0; i < 35; i++)
        {
            if(rxval[i] == '*')
            {
                break;
            }
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
                            PDC1 = (173 - m);
                            m = 0;
                            for(j = 0; j < LOOPS; j++)
                            {
                                if(rxval[m] == '*')
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
                        boomPrev = boom;        //Save the previous value of boom
                        sampleCount = 0;
                    }
                    else if(boomPrev > boom)    //Reverse
                    {
                        //Increment Duty Cycle from the previous boom to boom
                        for(k = boomPrev; k > boom; k--)
                        {
                            PDC1 = (173 - k);
                            for(j = 0; j < LOOPS; j++)
                            {
                                if(rxval[m] == '*')
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
 * */

