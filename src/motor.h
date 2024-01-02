//used to control a motor to provide power to a rc car and takes in values from rc receiver
#ifndef motor_h
#define motor_h

//initializes the motor pins, reciever pin and the PWM pin controlling the motor, sets PWM pin to a frequency to 1MHz
void motorInit();

//receives the input from the RC revceiver and sets the direction of the motor the speed
void runMotor();

#endif