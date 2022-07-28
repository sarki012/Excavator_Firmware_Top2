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
    int delayReceived = 0;
    PHASE2 = 36850;
    PDC2 = 2800;
    while(1)
    {
      for(i = 0; i < 45; i++)
        {
            if(rxval[i] == 'd')
            {
                delayPercentage = charToInt(rxval[i+1], rxval[i+2], rxval[i+3], rxval[i+4]);
                numDelayLoops = 50 + delayPercentage*5;
                delayReceived = 1;
            }
            else if(rxval[i] == 's')
            {
                stick = charToInt(rxval[i+1], rxval[i+2], rxval[i+3], rxval[i+4]);
                if(delayReceived)
                {
                    delayReceived = 0;
                    break;
                }
             }
        }
        //numDelayLoops = (abs(boom)*(31 - .0526*abs(boom))) + delayPercentage*50;
        //Motor Arithmitic Here
        //PHASE3 and PDC2 are for PWM3L, the bucket boom motor
        //PHASE is always 2303 to give a rising edge every 20ms
        //Max Duty Cycle is PDC = 253
        //Neutral Duty Cycle is 173
        //Min Duty Cycle is PDC = 92
        //With Max Resolution:
        //PHASEx = 36,850
        //Max Duty Cycle is PDC = 4,054
        //Neutral Duty Cycle is PDC = 3,685;
        //Min Duty Cycle is PDC = 1,474
        if(stick > 200)
        {
            PDC2--;
            delay(numDelayLoops);
            if(PDC2 < 1474)
            {
                PDC2 = 1474;
            }
        }
        else if(stick < -200)
        {
            PDC2++;
            delay(numDelayLoops);
            if(PDC2 > 4054)
            {
                PDC2 = 4054;
            }
        }   
    }
        /*
        for(i = 0; i < 45; i++)
        {
            if(rxval[i] == 'd')
            {
                delayPercentage = charToInt(rxval[i+1], rxval[i+2], rxval[i+3], rxval[i+4]);
                //numDelayLoops = 500 + delayPercentage*25;
            }
            if(rxval[i] == 's')
            {
                stick = charToInt(rxval[i+1], rxval[i+2], rxval[i+3], rxval[i+4]);
                numDelayLoops = (abs(stick)*(31 - .0526*abs(stick))) + delayPercentage*50;
                //Motor Arithmitic Here
                //PHASE3 and PDC2 are for PWM3L, the bucket boom motor
                //PHASE is always 2303 to give a rising edge every 20ms
                //Max Duty Cycle is PDC = 253
                //Neutral Duty Cycle is 173
                //Min Duty Cycle is PDC = 92
                if(sampleCount == SAMPLE_RATE)     //We're only going to take the SAMPLE_RATE sample
                {
                    if(stick > 100)
                    {
                    PDC2--;
                        delay(numDelayLoops);
                        if(PDC2 < 92)
                        {
                            PDC2 = 92;
                        }
                    }
                    else if(stick < -100)
                    {
                        PDC2++;
                        delay(numDelayLoops);
                        if(PDC2 > 253)
                        {
                            PDC2 = 253;
                        }
                    }
            }
        }
    }  */  

}