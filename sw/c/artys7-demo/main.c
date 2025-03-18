// Copyright lowRISC contributors.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0


#include "demo_system.h"
#include "timer.h"
#include "test_gpio.h"
#include "test_uart.h"
#include "test_pwm.h"
#include "test_wishbone.h"


int main(void) {
    puts("---\n");
    int status = 0;

    // // Create pointer to Memory location and write to it
    // volatile uint32_t* memptr = (volatile uint32_t*)0x44a00000;
    // *memptr = 0xdeadc0de;

    // status = drive_led();
    test_uart();

    // HW-test PWM
    // pwm_example();
 
    // HW-test Wishbone Bus
    // status = wishbone_master_test();

    while(1) {
        asm volatile("nop");
    }


    return status;
}
