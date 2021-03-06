/*
 * Copyright (c) 2017 Martin Jäger / Libre Solar
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef MPPT_2420_LC_H
#define MPPT_2420_LC_H

#define CONFIG_CAN 1

enum pin_state_t { PIN_HIGH, PIN_LOW, PIN_FLOAT };

// assignment LED numbers on PCB to their meaning
#define NUM_LEDS 2

#define LED_PWR  0     // LED1
#define LED_LOAD 1     // LED2

// LED pins and pin state configuration to switch above LEDs on
#define NUM_LED_PINS 2

// defined in board definition pinmux.c
extern const char *led_ports[NUM_LED_PINS];
extern const int led_pins[NUM_LED_PINS];

static const enum pin_state_t led_pin_setup[NUM_LEDS][NUM_LED_PINS] = {
    { PIN_HIGH, PIN_LOW  }, // LED1
    { PIN_LOW,  PIN_HIGH }  // LED2
};

// pin definition only needed in adc_dma.cpp to detect if they are present on the PCB
#define PIN_ADC_TEMP_BAT    PA_0
#define PIN_ADC_TEMP_FETS   PA_1

// typical value for Semitec 103AT-5 thermistor: 3435
#define NTC_BETA_VALUE 3435
#define NTC_SERIES_RESISTOR 10000.0

// position in the array written by the DMA controller
enum {
    ADC_POS_TEMP_BAT,   // ADC 0 (PA_0)
    ADC_POS_TEMP_FETS,  // ADC 1 (PA_1)
    ADC_POS_V_REF,      // ADC 5 (PA_5)
    ADC_POS_V_LOW,      // ADC 6 (PA_6)
    ADC_POS_V_HIGH,     // ADC 7 (PA_7)
    ADC_POS_I_LOAD,     // ADC 8 (PB_0)
    ADC_POS_I_DCDC,     // ADC 9 (PB_1)
    ADC_POS_TEMP_MCU,   // ADC 16
    ADC_POS_VREF_MCU,   // ADC 17
    NUM_ADC_CH          // trick to get the number of enums
};

#define NUM_ADC_1_CH NUM_ADC_CH

// selected ADC channels (has to match with above enum)
#define ADC_CHSEL ( \
    ADC_CHSELR_CHSEL0 | \
    ADC_CHSELR_CHSEL1 | \
    ADC_CHSELR_CHSEL5 | \
    ADC_CHSELR_CHSEL6 | \
    ADC_CHSELR_CHSEL7 | \
    ADC_CHSELR_CHSEL8 | \
    ADC_CHSELR_CHSEL9 | \
    ADC_CHSELR_CHSEL16 | \
    ADC_CHSELR_CHSEL17 \
)

#endif
