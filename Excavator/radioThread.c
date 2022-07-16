/*
 * File:   radioThread.c
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
void radioThread( void *pvParameters )
{
    int i = 0;
    while(1)
    {
        for(i = 0; i < 45; i++)
        {
            if(rxval[i] == 'l')
            {
                U1TXREG = 'l';              //Left Track
                while(!U1STAbits.TRMT);     
                i++;
                U1TXREG = rxval[i];         //+/-
                while(!U1STAbits.TRMT);
                i++;
                U1TXREG = rxval[i];         //Digit2
                while(!U1STAbits.TRMT); 
                i++;
                U1TXREG = rxval[i];         //Digit1
                while(!U1STAbits.TRMT); 
                i++;
                U1TXREG = rxval[i];         //Digit0
                while(!U1STAbits.TRMT); 
            }
            else if(rxval[i] == 'r')
            {
                U1TXREG = 'r';              //Right Track
                while(!U1STAbits.TRMT);
                i++;
                U1TXREG = rxval[i];         //+/-
                while(!U1STAbits.TRMT);
                i++;
                U1TXREG = rxval[i];         //Digit2
                while(!U1STAbits.TRMT); 
                i++;
                U1TXREG = rxval[i];         //Digit1
                while(!U1STAbits.TRMT); 
                i++;
                U1TXREG = rxval[i];         //Digit0
                while(!U1STAbits.TRMT); 
            }
            else if(rxval[i] == 'o')
            {
                U1TXREG = 'o';              //Orbit (Rotate)
                while(!U1STAbits.TRMT);
                i++;
                U1TXREG = rxval[i];         //+/-
                while(!U1STAbits.TRMT);
                i++;
                U1TXREG = rxval[i];         //Digit2
                while(!U1STAbits.TRMT); 
                i++;
                U1TXREG = rxval[i];         //Digit1
                while(!U1STAbits.TRMT);  
                i++;
                U1TXREG = rxval[i];         //Digit0
                while(!U1STAbits.TRMT);
            }
            else if(rxval[i] == '$')
            {
                U1TXREG = '$';              //Stop Sending
                while(!U1STAbits.TRMT);
            }
            else if(rxval[i] == '@')
            {
                U1TXREG = '@';              //Stop Sending
                while(!U1STAbits.TRMT);
            }
        }
    }    
}
