/*
 * Copyright (c) 2016 Martin Jäger / Libre Solar
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef HARDWARE_H
#define HARDWARE_H

/** @file
 *
 * @brief
 * Hardware-specific functions like timers, watchdog, bootloader
 */

#include <stdint.h>


/**
 * Initialization of IWDG
 */
void watchdog_init();

/**
 * Register watchdog for this thread
 *
 * @param timeout_ms Timeout in milliseconds
 */
int watchdog_register(uint32_t timeout_ms);

/**
 * Must be called after all channels have been registered
 */
void watchdog_start();

/**
 * Feed/kick the watchdog for given channel
 */
void watchdog_feed(int channel_id);

/** Timer for system control (main DC/DC or PWM control loop) is started
 *
 * @param freq_Hz Frequency in Hz (10 Hz suggested)
 */
void control_timer_start(int freq_Hz);

/** DC/DC or PWM control loop (implemented in main.cpp)
 */
void system_control();

/** Reset device and start STM32 internal bootloader
 */
void start_stm32_bootloader();

/**
 * Reset device
 */
void reset_device();

/**
 * Threads (LED, Control, ext_mgr) check in for sw_watchdog
 */
void check_in_led();

void check_in_control();

void check_in_ext_mgr();

/**
 * Implements watchdog for multiple threads in software
 */
void sw_watchdog(struct k_timer *timer_id);

/**
 * Configure timer for software watchdog and
 * configure actual watchdog
 */
void start_sw_watchdog();

#endif /* HARDWARE_H */