/*
 * File:   boom_task.c
 * Author: Erik
 *
 * Created on April 29, 2022, 4:43 PM
 */
//    numDelayLoops = (abs(boom)*(31 - .0526*abs(boom))) + delayPercentage*10;
#include <xc.h>
#include <p33ep512mc502.h>
#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOSConfig.h"
#include "main.h"
#include <stdio.h>
#include <stdlib.h>

volatile extern char rxval[50];
void boomThread( void *pvParameters )
{
    int  i = 0, k = 0, sampleCount = 0;
    int boom = 0, curl = 0;
    int m = 0;
    int p = 0, q = 0, breakTime = 0;
    int delayPercentage = 0, numDelayLoops = 0;
    int delayReceived = 0;
    int reverse = 0;
    PHASE1 = 36850;
   // PDC1 = 3100;
    PDC1 = 2500;
    while(1)
    {
      for(i = 0; i < 45; i++)
        {
            if(rxval[i] == 'd')
            {
                delayPercentage = charToInt(rxval[i+1], rxval[i+2], rxval[i+3], rxval[i+4]);
                numDelayLoops = 1 +delayPercentage*5;
                delayReceived = 1;
            }
            else if(rxval[i] == 'b')
            {
                boom = charToInt(rxval[i+1], rxval[i+2], rxval[i+3], rxval[i+4]);
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
        if(boom > 200)
        {
            PDC1--;
            delay(numDelayLoops);
            if(PDC1 < 1474)
            {
                PDC1 = 1474;
            }
        }
        else if(boom < -200)
        {
            PDC1++;
            delay(numDelayLoops);
            if(PDC1 > 4054)
            {
                PDC1 = 4054;
            }
        }   
    }
}    
    /*
     *                 numDelayLoops = (abs(boom)*(31 - .0526*abs(boom))) + delayPercentage*50;
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
                if(sampleCount == SAMPLE_RATE)     //We're only going to take the 100th sample
                {
                    if(boom > 100)
                    {
                        PDC1--;
                        delay(1000);
                        if(PDC1 < 1474)
                        {
                            PDC1 = 1474;
                        }
                    }
                    else if(boom < -100)
                    {
                        PDC1++;
                        delay(1000);
                        if(PDC1 > 4054)
                        {
                            PDC1 = 4054;
                        }
                    }
     * */