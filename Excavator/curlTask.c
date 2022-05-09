#include <xc.h>
#include <p33ep512mc502.h>
#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOSConfig.h"
#include "main.h"

volatile extern char rxval[20];
void curlTask( void *pvParameters )
{
    int  i = 0, j = 0, k = 0, averageCount = 0, curlAvg = 0;
    int curl = 0, curlPrev = 0, curlDelta = 0;
    int curlAvgPrev = 0;
    int m = 0;
    PHASE3 = 2303;
    while(1)
    {
        //We're going to take the average of NUM_AVG values
        //We're only going to update the duty cycle every NUM_AVG loops
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
                if(averageCount == NUM_AVG)
                {
                    if(curlPrev <= curl)
                    {
                        for(m = curlPrev; m <= curl; m++)
                        {
                            PDC3 = (173 + m);
                            for(j = 0; j < 2500; j++);
                       //     vTaskDelay(10);
                        }
                        curlPrev = curl;
                        averageCount = 0;
                    }
                    else if(curlPrev > curl)
                    {
                        for(k = curlPrev; k > curl; k--)
                        {
                            PDC3 = (173 + k);
                            for(j = 0; j < 2500; j++);
                       //     vTaskDelay(10);
                        }
                        curlPrev = curl;
                        averageCount = 0;
                    } 
                }
                averageCount++;  
                break;
            }
        }

    } 
}
/*
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
                curlAvg += curl;
                if(averageCount == (NUM_AVG - 1))
                {
                    curlAvg /= NUM_AVG;
                    if(curlAvgPrev <= curlAvg)
                    {
                        for(j = curlAvgPrev; j <= curlAvg; j++)
                        {
                            PDC3 = (173 + j);
                            curlAvgPrev = curlAvg;
                            //for(j = 0; j < 1000; j++);
                            averageCount = 0;
                            curlAvg = 0;
                       //     vTaskDelay(10);
                        }
                    }
                    else if(curlAvgPrev > curlAvg)
                    {
                        for(k = curlAvgPrev; k > curlAvg; k--)
                        {
                            PDC3 = (173 + k);
                            curlAvgPrev = curlAvg;
                            //for(j = 0; j < 1000; j++);
                            averageCount = 0;
                            curlAvg = 0;
                        //    vTaskDelay(10);
                        }
                    }
                    
                }
                averageCount++;  
                break;
            }
        }
*/
                /*
                    curlDelta = curl - curlPrev;
                   // if(curlDelta < 10)
                  //  {
                    if(curlPrev <= curl)
                    {
                        // Spin motor from curl_prev to curl
                        for(i = curlPrev; i <= curl; i++)
                        {
                            PDC3 = (int)(173 + i);
                            for(j = 0; j < 100; j++);          //Delay
                        }
                    }
                    else if(curl < curlPrev)
                    {
                                  // Spin motor from curl_prev to curl
                        for(i = curlPrev; i > curl; i--)
                        {
                            PDC3 = (int)(173 + i);
                            for(j = 0; j < 100; j++);          //Delay
                        }
                    }
                 //   }
                    curlPrev = curl;
                    break;
                    */