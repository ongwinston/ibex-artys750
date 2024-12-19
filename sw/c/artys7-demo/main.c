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

void pwm_example() {

    // PWM variables
    uint32_t counter    = UINT8_MAX;
    uint32_t brightness = 0;
    bool ascending      = true;
    // The three least significant bits correspond to RGB, where B is the leas significant.
    uint8_t color = 7;

    while(1){
        // Going from bright to dim on PWM
        for (int i = 0; i < NUM_PWM_MODULES; i++) {
          set_pwm(PWM_FROM_ADDR_AND_INDEX(PWM_BASE, i), ((1 << (i % 3)) & color) ? counter : 0,
                  brightness ? 1 << (brightness - 1) : 0);
        }
        if (ascending) {
          brightness++;
          if (brightness >= 5) {
            ascending = false;
          }
        } else {
          brightness--;
          // When LEDs are off cycle through the colors
          if (brightness == 0) {
            ascending = true;
            color++;
            if (color >= 8) {
              color = 1;
            }
          }
        }
    }

}

int wishbone_master_test() {
    volatile uint32_t* wishboneBasePtr = (volatile uint32_t*)0x80005000;
    
    // Write to wishbone
    *wishboneBasePtr = 0x12345678;


    // Read from wishbone
    volatile uint32_t value = *wishboneBasePtr;
    puts("Value:");
    puthex(value);

    return 0;
}

int main(void) {

    // Create pointer to Memory location and write to it
    // volatile uint32_t* memptr = (volatile uint32_t*)0x44a00000; // Writing to an invalid mem address will break the wbxbar
    // *memptr = 0xdeadc0de;

    // Writes to GPIO
    volatile uint32_t* gpioptr = (volatile uint32_t*)GPIO_BASE_ADDR;
    *gpioptr = 0xbad0beef; 

    // // Exit
    puts("Hello Opal Test");

    // pwm_example();
    int status = wishbone_master_test();

    // Delay to allow UART to finish transmitting
    for(int i=0; i < 1000; i++) {
        asm volatile("nop");
    }

    return status;
}