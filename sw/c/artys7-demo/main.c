// Copyright lowRISC contributors.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0


#include "demo_system.h"
#include "timer.h"
#include "test_gpio.h"
#include "test_uart.h"
#include "test_pwm.h"
#include "test_wishbone.h"


int romanToInt(char* s) {
    puts("\n-\n");

    int converted_int = 0;
    int current_int;
    int current_char, previous_int = 0;

    // Declare new char pointer to iterate with
    char* ptr = s;

    // Loop over the given String s till the end
    while(*ptr != '\0') {
        current_char = *ptr;
        switch(current_char) {
            case 'I':
                current_int = 1;
                break;
            case 'V':
                current_int = 5;
                break;
            case 'X':
                current_int = 10;
                break;
            case 'L':
                current_int = 50;
                break;
            case 'C':
                current_int = 100;
                break;
            case 'D':
                current_int = 500;
                break;
            case 'M':
                current_int = 1000;
                break;
            default:
                puts("END\n");
                break;
        }
        if(current_int >= previous_int) {
            converted_int += current_int;
        } else {
            converted_int -= current_int;
        }
        previous_int = current_int;
        ptr++;
        puts("val:");
        puthex(converted_int);
        puts("\n");
    }

    return converted_int;
}

int testRomanToInt(void) {
    puts("START TEST\n");
    int status = 0;
    int ret_integer;

    ret_integer = romanToInt("I"); // One
    if(ret_integer != 1){
        puts("Failed I saw:");
        putchar(ret_integer);
        status = 1;
    }
    ret_integer = romanToInt("V"); // Five
    if(ret_integer != 5){
        puts("Failed V\n");
        status = 1;
    }
    ret_integer = romanToInt("X"); // Ten
    if(ret_integer != 10){
        puts("Failed X\n");
        status = 1;
    }
    ret_integer = romanToInt("L"); // Fifty
    if(ret_integer != 50){
        puts("Failed L\n");
        status = 1;
    }
    ret_integer = romanToInt("C"); // Hundred
    if(ret_integer != 100){
        puts("Failed C\n");
        status = 1;
    }
    ret_integer = romanToInt("D"); // Five Hundred
    if(ret_integer != 500){
        puts("Failed D\n");
        status = 1;
    }
    ret_integer = romanToInt("M"); // Thousand
    if(ret_integer != 1000){
        puts("Failed M\n");
        status = 1;
    }
    ret_integer = romanToInt("IVX"); // 6 (1-5-10)
    if(ret_integer != 6){
        puts("Failed IVX\n");
        status = 1;
    }
    ret_integer = romanToInt("CLI"); // (151) = 100 + 50 + 1
    if(ret_integer != 151){
        puts("Failed CLI\n");
        status = 1;
    }
    ret_integer = romanToInt("III"); //  1 + 1 + 1
    if(ret_integer != 3){
        puts("Failed III\n");
        status = 1;
    }
    ret_integer = romanToInt("LVIII"); // 50 + 5 + 3
    if(ret_integer != 58){
        puts("Failed LVIII\n");
        status = 1;
    }
    ret_integer = romanToInt("MCMXCIV"); // 1000(M) + 900(CM) + 90(XC) + 4(IV)
    if(ret_integer != 1994){
        puts("Failed MCMXCIV\n");
        status = 1;
    }

    puts("\nEND\n");
    return status;
}


int main(void) {
    puts("---\n");
    int status = 0;

    // // Create pointer to Memory location and write to it
    // volatile uint32_t* memptr = (volatile uint32_t*)0x44a00000;
    // *memptr = 0xdeadc0de;

    // status = drive_led();
    // test_uart();

    if(testRomanToInt()) puts("FAILED\n");

    // HW-test Wishbone Bus
    // status = wishbone_master_test();

    // HW-test PWM
    // pwm_example(); // Loops indefinitely
 

    puts("PROGRAM EXIT CODE:");
    putchar(status);
    return status;
}
