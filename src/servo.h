//used to control a servo motor to provide steering to a rc car and takes in values from rc receiver
#ifndef servo_h
#define servo_h

//intializes the servo and inputPin and sets the PWM frequency of 1MHZ 
void servoInit();

//receives the input from the RC receiver and sends the value to the PWM controlling the servo
void runServo();

#endif