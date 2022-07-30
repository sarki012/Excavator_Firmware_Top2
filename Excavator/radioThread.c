/*
 * File:   radioThread.c
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
void radioThread( void *pvParameters )
{
    int i = 0;
    while(1)
    {
        for(i = 0; i < 45; i++)
        {
            //This loop reads the receive array and hands the characters to the radio
            //Uart 1 is hooked to the radio
            if(rxval[i] == 'l')
            {
                U1TXREG = 'l';              //Send 'l' for left Track
                while(!U1STAbits.TRMT);     
                i++;
                U1TXREG = rxval[i];         //Send +/-
                while(!U1STAbits.TRMT);
                i++;
                U1TXREG = rxval[i];         //Send digit2
                while(!U1STAbits.TRMT); 
                i++;
                U1TXREG = rxval[i];         //Send digit1
                while(!U1STAbits.TRMT); 
                i++;
                U1TXREG = rxval[i];         //Send digit0
                while(!U1STAbits.TRMT); 
            }
            else if(rxval[i] == 'r')
            {
                U1TXREG = 'r';              //Send 'r' for right Track
                while(!U1STAbits.TRMT);
                i++;
                U1TXREG = rxval[i];         //Send +/-
                while(!U1STAbits.TRMT);
                i++;
                U1TXREG = rxval[i];         //Send digit2
                while(!U1STAbits.TRMT); 
                i++;
                U1TXREG = rxval[i];         //Send digit1
                while(!U1STAbits.TRMT); 
                i++;
                U1TXREG = rxval[i];         //Send digit0
                while(!U1STAbits.TRMT); 
            }
            else if(rxval[i] == 'o')
            {
                U1TXREG = 'o';              //Sned 'o' for Orbit (Rotate)
                while(!U1STAbits.TRMT);
                i++;
                U1TXREG = rxval[i];         //Send +/-
                while(!U1STAbits.TRMT);
                i++;
                U1TXREG = rxval[i];         //Send digit2
                while(!U1STAbits.TRMT); 
                i++;
                U1TXREG = rxval[i];         //Send digit1
                while(!U1STAbits.TRMT);  
                i++;
                U1TXREG = rxval[i];         //Send digit0
                while(!U1STAbits.TRMT);
            }
            else if(rxval[i] == '$')
            {
                U1TXREG = '$';              //Send stop sending left track
                while(!U1STAbits.TRMT);
            }
            else if(rxval[i] == '@')
            {
                U1TXREG = '@';              //Send stop sending right track
                while(!U1STAbits.TRMT);
            }
            else if(rxval[i] == '#')
            {
                U1TXREG = '#';              //Send stop sending left joystick
                while(!U1STAbits.TRMT);
            }
        }
    }    
}
