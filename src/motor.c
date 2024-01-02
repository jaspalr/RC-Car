//used to control a motor to provide power to a rc car and takes in values from rc receiver
#include "FreeRTOS.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"
#include "motor.h"
//pins for the motor
#define en 12
#define in1 11
#define in2 10
//pin that rc receiver is connected to
#define inputPin 13

#define outMin 60
#define outMax 100
#define map(x, inMin, inMax)((x - inMin) * (outMax - outMin) / (inMax - inMin) + outMin)


static uint motorSlice = 0;
static int wrap = outMax;

//sets the motor into a forward positon 
#define forward(){\
    gpio_put(in1,1);\
    gpio_put(in2,0);\
}

//sets the motor into a backward positon 
#define backward(){\
    gpio_put(in1,0);\
    gpio_put(in2,1);\
}

//stops the motor
#define stop(){\
    gpio_put(in1,0);\
    gpio_put(in2,0);\
}



//initializes the motor pins, reciever pin and the PWM pin controlling the motor, sets PWM pin to a frequency to 1MHz
void motorInit(){
    //pins controlling the motor direction
    gpio_init(in1);
    gpio_init(in2);
    gpio_set_dir(in1, GPIO_OUT);
    gpio_set_dir(in2, GPIO_OUT);
    stop();
    //PWM pin for the motor
    gpio_set_function(en, GPIO_FUNC_PWM);
    motorSlice = pwm_gpio_to_slice_num(en);
    pwm_set_clkdiv(motorSlice, 125); //clock_div/125 = 1MHz (clock_div = 125)
    pwm_set_wrap(motorSlice, wrap);
    pwm_set_enabled(motorSlice, true);
    //pin that polls the revceiver 
    gpio_set_input_enabled(inputPin,true);
}

//receives the input from the RC revceiver and sets the direction of the motor the speed
void runMotor(){
    uint startTimer;
    uint stopTimer;
    int pwmValue;
    while (true) {
        //sample the value from the receiver
        startTimer = time_us_32();
        while(gpio_get(13) == 0 &&  time_us_32() - startTimer < 20000);
        startTimer = time_us_32();
        while(gpio_get(13) == 1 &&  time_us_32() - startTimer< 20000);
        stopTimer= time_us_32();
        pwmValue = stopTimer - startTimer;

        //if value is less than 1450 set the motor direction to going in reverse
        if(pwmValue < 1450){
            backward();
            pwm_set_chan_level(motorSlice, PWM_CHAN_A, map(1450-pwmValue,0,450));
        }
        //if value is less than 1550 set the motor direction to going in foward
        else if(pwmValue > 1550){
            forward();
            pwm_set_chan_level(motorSlice, PWM_CHAN_A, map(pwmValue,1550,2000));
        }
        //if between 1450 and 1550 stop the motor
        else{
            stop();
        }
    }    
}



