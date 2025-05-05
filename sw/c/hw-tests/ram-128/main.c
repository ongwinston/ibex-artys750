// Copyright lowRISC contributors.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0


#include "demo_system.h"
#include "dev_access.h"
#include "myprintf.h"

extern uint32_t _stack;
extern uint32_t _bss_start;
extern uint32_t _bss_end;
extern uint32_t _stext;
extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _vectors_start;

int main(void) {
    puts("---\n");
    uint32_t status = 0;

    // Write to PWM to pinpoint point in simulation
    DEV_WRITE(0x80003000, 0xffffffff);
    DEV_WRITE(0x00113000,0x0badc0de);

    /* for(int i = 0; i < 3; i++) { */
    /*     uint32_t test_read =  DEV_READ(0x00113000 + i); */
    /*     myprintf("Test read:0x%x\n", test_read); */
    /*     puthex(test_read); */
    /*     puts("\n"); */
    /* } */

    // Test HEAP variables
    myprintf("_vectors_start:%x\n", (uintptr_t)&_vectors_start);
    myprintf("_stext:%x\n", (uintptr_t)&_stext);
    myprintf("_etext:%x\n", (uintptr_t)&_etext);
    myprintf("_sdata:%x\n", (uintptr_t)&_sdata);
    myprintf("_edata:%x\n", (uintptr_t)&_edata);
    myprintf("_stack:%x\n",(uintptr_t)&_stack);
    myprintf("_bss_start:%x\n", (uintptr_t)&_bss_start);
    myprintf("_bss_end:%x\n", (uintptr_t)&_bss_end);


    while(1) {
        asm volatile("nop");
    }


    return status;
}
