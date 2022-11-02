/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "stdio.h"

/* Reference resistor in series with the thermistor is of 10kohm */
#define R_REFERENCE                         (float)(10000)

/* A constant of NCP18XH103F03RB thermistor is */
#define A_COEFF                          (float)(0.0009032679f)
/* B constant of NCP18XH103F03RB thermistor is */
#define B_COEFF                          (float)(0.000248772f)
/* C constant of NCP18XH103F03RB thermistor is */
#define C_COEFF                          (float)(0.0000002041094f)

/* Zero Kelvin in degree C */
#define ABSOLUTE_ZERO                       (float)(-273.15)
// Blinking rate in milliseconds
#define BLINKING_RATE     2s
#define THERM_OUT         P10_1
#define THERM_VDD         P10_3
#define THERM_GND         P10_0
    DigitalOut led(LED1);
    DigitalOut vdd(THERM_VDD);
    DigitalOut gnd(THERM_GND);
    AnalogIn tempVoltage(THERM_OUT);

float readTemp();
int main()
{
    // Initialise the digital pin LED1 as an output

    while (true) {
        led = !led;
        ThisThread::sleep_for(BLINKING_RATE);
        vdd = true;
        gnd = false;
        float tempTherm = readTemp();
        printf("The thermistor voltage is %2.3fC\n", tempTherm);
    }
}
    float readTemp() {
        // Power up the thermister
        vdd= true;
        gnd= false;
        // onvert to celcius
    
 
    float refVoltage = tempVoltage.read() * 2.4; // Range of ADC 0->2*Vref
        vdd = false;
    float refCurrent = refVoltage  / 10000.0; // 10k Reference Resistor
    float thermVoltage = 3.3 - refVoltage;    // Assume supply voltage is 3.3v
    float thermResistance = thermVoltage / refCurrent; 
    float logrT = (float32_t)log((float64_t)thermResistance);
    /* Calculate temperature from the resistance of thermistor using Steinhart-Hart Equation */
    float stEqn = (float32_t)((A_COEFF) + ((B_COEFF) * logrT) + 
                             ((C_COEFF) * pow((float64)logrT, (float32)3)));
    float temperatureC = (float32_t)(((1.0 / stEqn) + ABSOLUTE_ZERO)  + 0.05);
    return temperatureC;
}