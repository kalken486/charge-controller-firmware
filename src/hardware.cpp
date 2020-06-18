/*
 * Copyright (c) 2016 Martin Jäger / Libre Solar
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "hardware.h"

#include "mcu.h"
#include "board.h"
#include "load.h"
#include "half_bridge.h"
#include "leds.h"
#include "setup.h"

#if defined(CONFIG_SOC_SERIES_STM32F0X)
#define SYS_MEM_START       0x1FFFC800
#define SRAM_END            0x20003FFF  // 16k
#elif defined(CONFIG_SOC_SERIES_STM32L0X)
#define SYS_MEM_START       0x1FF00000
#define SRAM_END            0X20004FFF  // 20k
#define FLASH_LAST_PAGE     0x0802FF80  // start address of last page (192 kbyte cat 5 devices)
#endif

#define MAGIC_CODE_ADDR     (SRAM_END - 0xF)    // where the magic code is stored

#ifndef UNIT_TEST

#include <power/reboot.h>
#include <drivers/gpio.h>
#include <drivers/watchdog.h>

static struct device *wdt;
struct k_timer sw_wtchdg_timer;

int wdt_channel;
int64_t check_in_time_led;
int64_t check_in_time_control;
int64_t check_in_time_ext_mgr;


void watchdog_init()
{
    wdt = device_get_binding(DT_INST_0_ST_STM32_WATCHDOG_LABEL);
    if (!wdt) {
        printk("Cannot get WDT device\n");
        return;
    }
    
}

int watchdog_register(uint32_t timeout_ms)
{
    struct wdt_timeout_cfg wdt_config;

    wdt_config.flags = WDT_FLAG_RESET_SOC;
    wdt_config.window.min = 0U;
    wdt_config.window.max = timeout_ms;
    wdt_config.callback = NULL;             // STM32 does not support callbacks

    return wdt_install_timeout(wdt, &wdt_config);
}

void watchdog_start()
{
    wdt_setup(wdt, 0);
}

void watchdog_feed(int channel_id)
{
    wdt_feed(wdt, channel_id);
}

void check_in_led()
{
    check_in_time_led = k_uptime_get();
}

void check_in_control()
{
    check_in_time_control = k_uptime_get();
}

void check_in_ext_mgr()
{
    check_in_time_ext_mgr = k_uptime_get();
    
}

void sw_watchdog(struct k_timer *timer_id)
{
        watchdog_feed(wdt_channel);

        int64_t current_time = k_uptime_get();

        if((current_time - check_in_time_led) > 1000)
            reset_device();

        if((current_time - check_in_time_control) > 200)
            reset_device();

        if((current_time - check_in_time_ext_mgr) > 3000)
            reset_device();
        
}

void start_sw_watchdog()
{
    k_timer_init(&sw_wtchdg_timer, sw_watchdog, NULL);
    k_timer_start(&sw_wtchdg_timer, K_MSEC(10), K_MSEC(10)); 
    wdt_channel = watchdog_register(100);
}

void start_stm32_bootloader()
{
#ifdef DT_OUTPUTS_BOOT0_PRESENT
    // pin is connected to BOOT0 via resistor and capacitor
    struct device *dev = device_get_binding(DT_OUTPUTS_BOOT0_GPIOS_CONTROLLER);
    gpio_pin_configure(dev, DT_OUTPUTS_BOOT0_GPIOS_PIN,
        DT_OUTPUTS_BOOT0_GPIOS_FLAGS | GPIO_OUTPUT_ACTIVE);

    k_sleep(K_MSEC(100));   // wait for capacitor at BOOT0 pin to charge up
    reset_device();
#elif defined (CONFIG_SOC_SERIES_STM32F0X)
    // place magic code at end of RAM and initiate reset
    *((uint32_t *)(MAGIC_CODE_ADDR)) = 0xDEADBEEF;
    reset_device();
#endif
}

void reset_device()
{
    sys_reboot(SYS_REBOOT_COLD);
}

#else

// dummy functions for unit tests
void start_stm32_bootloader() {}
void reset_device() {}

#endif /* UNIT_TEST */
