/*
 * Copyright (c) 2018 Martin Jäger / Libre Solar
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef PCB_STUB_H
#define PCB_STUB_H

// PWM charge controller
#define CONFIG_PWM_TERMINAL_SOLAR DT_OUTPUTS_PWM_SWITCH_PRESENT

// MPPT buck/boost or nanogrid mode
#define CONFIG_HV_TERMINAL_SOLAR DT_COMPAT_DCDC
#define CONFIG_HV_TERMINAL_NANOGRID 0

// battery always assumed to be at low-voltage terminal (might need to be changed for boost mode)
#define CONFIG_LV_TERMINAL_BATTERY 1

// basic battery configuration
#define BATTERY_TYPE        BAT_TYPE_GEL    ///< GEL most suitable for general batteries (see battery.h for other types)
#define BATTERY_NUM_CELLS   6               ///< For lead-acid batteries: 6 for 12V system, 12 for 24V system
#define BATTERY_CAPACITY    40              ///< Cell capacity or sum of parallel cells capacity (Ah)

#define CONFIG_DEVICE_ID 12345678

#define DT_CHARGE_CONTROLLER_PCB_TYPE "PCB-STUB"
#define DT_CHARGE_CONTROLLER_PCB_VERSION_STR "v0.1"

#define CONFIG_THINGSET_EXPERT_PASSWORD "expert123"
#define CONFIG_THINGSET_MAKER_PASSWORD "maker456"

// specify features of charge controller
#define DT_COMPAT_DCDC  1
#define DT_INST_0_DCDC_PWM_FREQUENCY 70000 // Hz
#define DT_INST_0_DCDC_PWM_DEADTIME  300   // ns
#define DT_INST_0_DCDC_CURRENT_MAX   20    // A

#define DT_OUTPUTS_PWM_SWITCH_PRESENT 1
#define DT_OUTPUTS_PWM_SWITCH_PWMS_PERIOD   (20*1000*1000)
#define DT_OUTPUTS_PWM_SWITCH_CURRENT_MAX    20 // A

#define DT_OUTPUTS_LOAD_PRESENT     1
#define DT_OUTPUTS_LOAD_CURRENT_MAX 20  // PCB maximum load switch current

#define DT_OUTPUTS_USB_PWR_PRESENT  1

// Values that are otherwise defined by Kconfig
#define CONFIG_CONTROL_FREQUENCY   10   // Hz
#define DT_CHARGE_CONTROLLER_PCB_MOSFETS_TJ_MAX     120
#define DT_CHARGE_CONTROLLER_PCB_INTERNAL_TREF_MAX  50
#define DT_CHARGE_CONTROLLER_PCB_MOSFETS_TAU_JA     5

#define DT_CHARGE_CONTROLLER_PCB_LS_VOLTAGE_MAX    32  // Maximum voltage at battery port (V)
#define DT_CHARGE_CONTROLLER_PCB_HS_VOLTAGE_MAX   55  // Maximum voltage at PV input port (V)

#define PIN_UEXT_TX   0
#define PIN_UEXT_RX   0
#define PIN_UEXT_SCL  0
#define PIN_UEXT_SDA  0
#define PIN_UEXT_MISO 0
#define PIN_UEXT_MOSI 0
#define PIN_UEXT_SCK  0
#define PIN_UEXT_SSEL 0

#define PIN_SWD_TX    0
#define PIN_SWD_RX    0

//#define PIN_LOAD_DIS    0
//#define PIN_USB_PWR_DIS 0

enum pin_state_t { PIN_HIGH, PIN_LOW, PIN_FLOAT };

// assignment LED numbers on PCB to their meaning
#define NUM_LEDS 5

#define LED_SOC_1 0     // LED1
#define LED_SOC_2 1     // LED2
#define LED_SOC_3 2     // LED3
#define LED_LOAD  3     // LED4
#define LED_RXTX  4     // LED5, used to indicate when sending data

// LED pins and pin state configuration to switch above LEDs on
#define NUM_LED_PINS 3
static const int led_pins[NUM_LED_PINS] = {
    //  A         B         C
       0,    0,    0
};
static const enum pin_state_t led_pin_setup[NUM_LEDS][NUM_LED_PINS] = {
    { PIN_HIGH,  PIN_LOW,   PIN_FLOAT }, // LED1
    { PIN_LOW,   PIN_HIGH,  PIN_FLOAT }, // LED2
    { PIN_HIGH,  PIN_FLOAT, PIN_LOW   }, // LED3
    { PIN_FLOAT, PIN_HIGH,  PIN_LOW   }, // LED4
    { PIN_FLOAT, PIN_LOW,   PIN_HIGH  }  // LED5
};

// pin definition only needed in adc_dma.cpp to detect if they are present on the PCB
#define PIN_ADC_TEMP_BAT

// typical value for Semitec 103AT-5 thermistor: 3435
#define NTC_BETA_VALUE 3435
#define NTC_SERIES_RESISTOR 8200.0

#define DT_ADC_INPUTS_V_HIGH_MULTIPLIER 105600
#define DT_ADC_INPUTS_V_HIGH_DIVIDER 5600
#define DT_ADC_INPUTS_V_LOW_MULTIPLIER 105600
#define DT_ADC_INPUTS_V_LOW_DIVIDER 5600
#define DT_ADC_INPUTS_V_PWM_MULTIPLIER 25224   // see pwm_2420_lus.dtx
#define DT_ADC_INPUTS_V_PWM_DIVIDER 984
#define DT_ADC_INPUTS_V_PWM_OFFSET 2338

// amp gain: 50, resistor: 4 mOhm
#define DT_ADC_INPUTS_I_LOAD_MULTIPLIER 1000
#define DT_ADC_INPUTS_I_LOAD_DIVIDER (4 * 50)
#define DT_ADC_INPUTS_I_DCDC_MULTIPLIER 1000
#define DT_ADC_INPUTS_I_DCDC_DIVIDER (4 * 50)
#define DT_ADC_INPUTS_I_PWM_MULTIPLIER 1000
#define DT_ADC_INPUTS_I_PWM_DIVIDER (4 * 50)


#endif
