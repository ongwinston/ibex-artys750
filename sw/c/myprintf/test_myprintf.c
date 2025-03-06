#include <stddef.h>
#include "demo_system.h"
#include "gpio.h"
#include "myprintf.h"



void test_putchar(void) {
    // Print ASCII
    putchar(65); // A
    putchar(83); // S
    putchar(67); // C
    putchar(73); // I
    putchar(73); // I
    puts("\n");
    convert_to_ascii('0');
    convert_to_ascii('3');
    convert_to_ascii('6');
    convert_to_ascii('1');
    puts("\n");
    convert_to_ascii("125");
    puts("\n");
}

void test_puthex(void) {
    puthex(70); // P
    puthex(75); // U
    puthex(74); // T
    puthex(68); // H
    puthex(65); // E
    puthex(78); // X
}

void test_myprintf(void) {
    test_putchar();
    // test_puthex();
    puts("\n");
    myprintf("test my %d print\n");
    puts("\n");
    myprintf("%d");

    // char string_var = "a";
    // myprintf(string_var);
}