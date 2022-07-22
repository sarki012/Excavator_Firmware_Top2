#include <xc.h>
#include <p33ep512mc502.h>
#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOSConfig.h"
#include "main.h"

volatile extern char rxval[50];
void curlThread( void *pvParameters )
{
    int  i = 0, j = 0, k = 0, sampleCount = 0, curlAvg = 0;
    int curl = 0, curlPrev = 0, curlDelta = 0;
    int curlAvgPrev = 0;
    int m = 0;
    int delayPercentage = 0, numDelayLoops = 0;
    PHASE3 = 2303;
    PDC3 = 173;
    while(1)
    {
        for(i = 0; i < 45; i++)
        {
            if(rxval[i] == 'd')
            {
                delayPercentage = charToInt(rxval[i+1], rxval[i+2], rxval[i+3], rxval[i+4]);
                numDelayLoops = 50 + delayPercentage*3;
            }
            if(rxval[i] == 'c')
            {
                curl = charToInt(rxval[i+1], rxval[i+2], rxval[i+3], rxval[i+4]);
                //Motor Arithmitic Here
                //PHASE3 and PDC3 are for PWM3L, the bucket curl motor
                //PHASE is always 2303 to give a rising edge every 20ms
                //Max Duty Cycle is PDC = 253
                //Neutral Duty Cycle is 173
                //Min Duty Cycle is PDC = 92
                if(sampleCount == SAMPLE_RATE)     //We're only going to take the 100th sample
                {
                    if(curl > 0)
                    {
                        PDC3++;
                        delay(numDelayLoops);
                        if(PDC3 > 253)
                        {
                            PDC3 = 253;
                        }
                    }
                    else if(curl < 0)
                    {
                        PDC3--;
                        delay(numDelayLoops);
                        if(PDC3 < 92)
                        {
                            PDC3 = 92;
                        }
                    }
                    sampleCount = 0;
                    /*
                    if(curlPrev <= curl)        //Direction
                    {
                        //Increment Duty Cycle from the previous curl to curl
                        for(m = curlPrev; m <= curl; m++)   
                        {
                          //  PDC3 = (173 + m);
                            PDC3 = (int)(173 + .14*m);
                            delay(numDelayLoops);
                        }
                        curlPrev = curl;        //Save the previous value of curl
                        sampleCount = 0;
                    }
                    else if(curlPrev > curl)    //Reverse
                    {
                        //Increment Duty Cycle from the previous curl to curl
                        for(k = curlPrev; k > curl; k--)
                        {
                           // PDC3 = (173 + k);
                            PDC3 = (int)(173 + .14*k);
                            delay(numDelayLoops);
                        }
                        curlPrev = curl;        //Save the previous value of curl
                        sampleCount = 0;
                    } */
                }
                sampleCount++;  
                break;
            }
        }

    } 
}
/*
volatile extern char rxval[40];
void curlTask( void *pvParameters )
{
    int  i = 0, j = 0, k = 0, sampleCount = 0, curlAvg = 0;
    int curl = 0, curlPrev = 0, curlDelta = 0;
    int curlAvgPrev = 0;
    int m = 0;
    int breakTime = 0;
    PHASE3 = 2303;
    while(1)
    {
        for(i = 0; i < 35; i++)
        {
            if(rxval[i] == '*')
            {
                break;
            }
            if(rxval[i] == 'c')
            {
                curl = charToInt(rxval[i+1], rxval[i+2], rxval[i+3]);
                //Motor Arithmitic Here
                //PHASE3 and PDC3 are for PWM3L, the bucket curl motor
                //PHASE is always 2303 to give a rising edge every 20ms
                //Max Duty Cycle is PDC = 253
                //Neutral Duty Cycle is 173
                //Min Duty Cycle is PDC = 92
                if(sampleCount == SAMPLE_RATE)     //We're only going to take the SAMPLE_RATE sample
                {
                    if(curlPrev <= curl)        //Direction
                    {
                        //Increment Duty Cycle from the previous curl to curl
                        for(m = curlPrev; m <= curl; m++)   
                        {
                            PDC3 = (173 + m);
                            for(j = 0; j < LOOPS_CURL; j++)
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
                        curlPrev = curl;        //Save the previous value of curl
                        sampleCount = 0;
                    }
                    else if(curlPrev > curl)    //Reverse
                    {
                        //Increment Duty Cycle from the previous curl to curl
                        for(k = curlPrev; k > curl; k--)
                        {
                            PDC3 = (173 + k);
                            for(j = 0; j < LOOPS_CURL; j++)
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
                        curlPrev = curl;        //Save the previous value of curl
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