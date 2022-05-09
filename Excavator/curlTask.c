#include <xc.h>
#include <p33ep512mc502.h>
#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOSConfig.h"
#include "main.h"

volatile extern char rxval[20];
void curlTask( void *pvParameters )
{
    int  i = 0, j = 0, k = 0, sampleCount = 0, curlAvg = 0;
    int curl = 0, curlPrev = 0, curlDelta = 0;
    int curlAvgPrev = 0;
    int m = 0;
    PHASE3 = 2303;
    while(1)
    {
        for(i = 0; i < 15; i++)
        {
            if(rxval[i] == 'c')
            {
                curl = charToInt(rxval[i+1], rxval[i+2], rxval[i+3]);
                //Motor Arithmitic Here
                //PHASE3 and PDC3 are for PWM3L, the bucket curl motor
                //PHASE is always 2303 to give a rising edge every 20ms
                //Max Duty Cycle is PDC = 253
                //Neutral Duty Cycle is 173
                //Min Duty Cycle is PDC = 92
                if(sampleCount == SAMPLE_RATE)     //We're only going to take the 100th sample
                {
                    if(curlPrev <= curl)        //Direction
                    {
                        //Increment Duty Cycle from the previous curl to curl
                        for(m = curlPrev; m <= curl; m++)   
                        {
                            PDC3 = (173 + m);
                            for(j = 0; j < 5000; j++);
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
                            for(j = 0; j < 5000; j++);
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