/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "stdio.h"


// Blinking rate in milliseconds
#define BLINKING_RATE     2s
#define THERM_OUT         P10_1
#define THERM_VDD         P10_3
#define THERM_GND         P10_0


int main()
{
    // Initialise the digital pin LED1 as an output
    DigitalOut led(LED1);
    DigitalOut vdd(THERM_VDD);
    DigitalOut gnd(THERM_GND);
    AnalogIn tempVoltage(THERM_OUT);

    while (true) {
        led = !led;
        ThisThread::sleep_for(BLINKING_RATE);
        vdd = true;
        gnd = false;
        float tempTherm = tempVoltage.read();
        vdd = false;
        printf("The thermistor voltage is %2.3fVolts\n", tempTherm);
    }
}
