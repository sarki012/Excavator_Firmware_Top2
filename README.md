# Excavator_Firmware_Top2
Controls the three servo motors.
UART2 is hooked to the Bluetooth module which takes the data sent from the Android tabled and puts it in rxval[], the receive array
boomThread controls PWM1, which looks for a 'b' in the receive array, calls charToInt to convert the characters into an integer, and increments or decrements
the duty cycle in an infinite loop.
stickThread controls PWM2, which looks for an 's' in the receive array, calls charToInt to convert the characters into an integer, and increments or decrements
the duty cycle in an infinite loop.
curlThread controls PWM3, which looks for a 'c' in the receive array, calls charToInt to convert the characters into an integer, and increments or decrements
the duty cycle in an infinite loop.
The radio thread relays the stepper motor information from the tablet to the radio to control the stepper motors on the bottom circuit board. 
