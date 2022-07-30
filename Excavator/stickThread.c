/*
 * File:   stickThread.c
 * Author: Erik Sarkinen
 *
 * Created on April 29, 2022, 4:43 PM
 */
#include <xc.h>
#include <p33ep512mc502.h>
#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOSConfig.h"
#include "main.h"

volatile extern char rxval[50];     //The UART receive array which holds the data sent 
                                    //via Bluetooth from the tablet
void stickThread( void *pvParameters )
{
    int  i = 0;
    int stick = 0;
    int delayPercentage = 0;        //Value received via Bluetooth from the app
    int numDelayLoops = 0;          
    int delayReceived = 0;
    PHASE2 = 36850;     //PHASEx is always 36,850 for a 50Hz pulse
    PDC2 = 2800;        //Duty cycle register. Starting duty cycle is 2800.
    while(1)
    {
      for(i = 0; i < 45; i++)
        {
            if(rxval[i] == 'd')
            {
                //This means the next character is a +/- followed by three characters
                //which are passed to charToInt which returns an integer value
                //delayPercentage is a number between 0-100 that will speed up or slow down the stick
                delayPercentage = charToInt(rxval[i+1], rxval[i+2], rxval[i+3], rxval[i+4]);
                numDelayLoops = 50 + delayPercentage*2;        //Number of delay loops passed to delay() function after each motor update
                delayReceived = 1;
            }
            else if(rxval[i] == 's')
            {
                //This means the next character is a +/- followed by three characters
                //which are passed to charToInt which returns an integer value
                //stick is the pixels in the y-direction of the bottom left joystick sent from the tablet
                stick = charToInt(rxval[i+1], rxval[i+2], rxval[i+3], rxval[i+4]);
                if(delayReceived)
                {
                    //We've received stick data and delay data. Break from loop
                    delayReceived = 0;
                    break;
                }
             }
        }
        //Motor Arithmitic Here
        //PHASE2 and PDC2 are for PWM2L, the stick motor
        //With Max Resolution:
        //PHASEx = 36,850
        //Max Duty Cycle is PDC = 4,054
        //Neutral Duty Cycle is PDC = 3,685;
        //Min Duty Cycle is PDC = 1,474
        if(stick > 200)     //We don't touch the motors if the thumb press is in the circle
        {
            PDC2--;         //Decrementing the duty cycle moves the boom down
            delay(numDelayLoops);
            if(PDC2 < 1474)
            {
                PDC2 = 1474;    //We don't let PDC2 get less than 1,474
            }
        }
        else if(stick < -200)
        {
            PDC2++;         //Incrementing the duty cycle moves the boom up
            delay(numDelayLoops);
            if(PDC2 > 4054)
            {
                PDC2 = 4054;    //We don't let PDC2 get greater than 4054
            }
        }   
    }
}