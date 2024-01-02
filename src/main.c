//this application controls a motor and servo reciving inputs from rc receiver used to power a rc car
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"
#include "motor.h"
#include "servo.h"

//thread that controls servo
void servoTask(){     
    motorInit();
    runMotor();
}

   

//thread that control the motor
void motorTask(){
   servoInit();
   runServo();
}

int main()
{
    stdio_init_all();

    xTaskCreate(servoTask, "SERVO_TASK", 256, NULL, 1, NULL);
    xTaskCreate(motorTask, "MOTOR_TASK", 256, NULL, 1, NULL);
    vTaskStartScheduler();

    while(1){};
}