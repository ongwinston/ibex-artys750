// Copyright lowRISC contributors.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#include <stdbool.h>

#include "demo_system.h"
#include "gpio.h"
#include "pwm.h"
#include "timer.h"


#define GPIO_BASE_ADDR 0x80000000;
#define GPIO_END_ADDR 0x80000000 + 4*1024;

int main(void) {

    // Create pointer to Memory location and write to it
    volatile uint32_t* memptr = 0x44a00000;
    *memptr = 0xdeadc0de;

    // Writes to GPIO
    volatile uint32_t* gpioptr = GPIO_BASE_ADDR;
    *gpioptr = 0xbad0beef; 

    // Exit
    puts("Hello Opal Test");

    // Delay to allow UART to finish transmitting
    for(int i=0; i < 10000; i++) {
        asm volatile("nop");
    }

    return 0;
}