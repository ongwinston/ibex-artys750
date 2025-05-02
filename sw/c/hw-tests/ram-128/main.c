// Copyright lowRISC contributors.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#include <stdlib.h>
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

#define RAM_START 0x00100000

uint32_t test_mem_addr(uint32_t addr, int32_t value) {
    // Write to ADDR
    DEV_WRITE(addr, value);
    uint32_t read_val = DEV_READ(addr);
    if(value == read_val) {
        myprintf("MEM PASS, addr:0x%x\n", addr);
        return 0;
    } else {
        myprintf("MEM FAIL, addr:0x%x\n", addr);
        return 1;
    }
}

uint32_t test_mem_rand(uint32_t addr) {
    // Write to ADDR
    uint32_t rand_val = rand();
    myprintf("rand_val:0x%x\n", rand_val);
    DEV_WRITE(addr, rand_val);
    uint32_t read_val = DEV_READ(addr);
    if(rand_val == read_val) {
        myprintf("MEM PASS, addr:0x%x\n", addr);
        return 0;
    } else {
        myprintf("MEM FAIL, addr:0x%x\n", addr);
        return 1;
    }
}

void print_symbols(void) {
    // Test HEAP variables
    myprintf("_vectors_start:%x\n", (uintptr_t)&_vectors_start);
    myprintf("_stext:%x\n", (uintptr_t)&_stext);
    myprintf("_etext:%x\n", (uintptr_t)&_etext);
    myprintf("_sdata:%x\n", (uintptr_t)&_sdata);
    myprintf("_edata:%x\n", (uintptr_t)&_edata);
    myprintf("_stack:%x\n",(uintptr_t)&_stack);
    myprintf("_bss_start:%x\n", (uintptr_t)&_bss_start);
    myprintf("_bss_end:%x\n", (uintptr_t)&_bss_end);
}


int main(void) {
    puts("---\n");
    uint32_t status = 0;

    // Write to PWM to pinpoint point in simulation
    DEV_WRITE(0x80003000, 0xffffffff);

    status = test_mem_addr(0x00113000, 0x0badc0de);

    /* for(int i = 0; i < 1024; i ++) {  */
    /*     status = test_mem_rand(0x00113000 + (i * 1024)); */
    /*     if(status == 1) break; */
    /* } */
    DEV_WRITE(0x80003000, 0x00120000);
    status = test_mem_rand(0x00120000);
    DEV_WRITE(0x80003000, 0x00120010);
    status = test_mem_rand(0x00120010);
    DEV_WRITE(0x80003000, 0x00130000);
    status = test_mem_rand(0x00130000);
    DEV_WRITE(0x80003000, 0x60000000);
    status = test_mem_rand(0x60000000);

    print_symbols();

    while(1) {
        asm volatile("nop");
    }


    return status;
}
