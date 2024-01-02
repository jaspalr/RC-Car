//used to control a servo motor to provide steering to a rc car and takes in values from rc receiver
#include "FreeRTOS.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"
#include "servo.h"

//pin that servo is connected to
#define servoPin 0
#define wrap 2500
//pin that rc receiver is connected to
#define inputPin 1

static int servoSlice = 0;

//intializes the servo and inputPin and sets the PWM frequency of 1MHZ
void servoInit(){
    gpio_set_function(0, GPIO_FUNC_PWM);
    servoSlice = pwm_gpio_to_slice_num(servoPin);
    pwm_set_clkdiv(servoSlice, 125); //clock_div/125 = 1MHz (clock_div = 125)
    pwm_set_wrap(servoSlice, wrap);
    pwm_set_enabled(servoSlice, true);
    gpio_set_input_enabled(inputPin,true); //pin that polls the revceiver 
}

//receives the input from the RC receiver and sends the value to the PWM controlling the servo
void runServo(){
    uint startTimer;
    uint stopTimer;
    while (true) {
        //sample the value
        startTimer = time_us_32();
        while(gpio_get(1) == 0 &&  time_us_32() - startTimer < 20000);
        startTimer = time_us_32();
        while(gpio_get(1) == 1 &&  time_us_32() - startTimer< 20000);
        stopTimer = time_us_32();
        //set the PWM pin the value
        pwm_set_chan_level(servoSlice, PWM_CHAN_A, stopTimer - startTimer);
       
    }

}
