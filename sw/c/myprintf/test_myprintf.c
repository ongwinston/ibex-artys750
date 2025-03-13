#include <stddef.h>
#include "demo_system.h"
#include "gpio.h"
#include "myprintf.h"
#include "dev_access.h"

// void test_putchar(void) {
//     // Print ASCII
//     putchar(65); // A
//     putchar(83); // S
//     putchar(67); // C
//     putchar(73); // I
//     putchar(73); // I
//     puts("\n");
//     print_ascii('0');
//     print_ascii('3');
//     print_ascii('6');
//     print_ascii('1');
//     puts("\n");
//     print_ascii("125");
//     puts("\n");
// }

// void test_puthex(void) {
//     puthex(70); // P
//     puthex(75); // U
//     puthex(74); // T
//     puthex(68); // H
//     puthex(65); // E
//     puthex(78); // X
// }

void test_myprintf(void) {
    // volatile uint32_t* memptr = (volatile uint32_t*)0x44a00000;
    // *memptr = 0xdeadc0de;
    // DEV_WRITE(0x80003000,0x0bad);

    // int int_var = 123;
    // int int_var2 = 9;
    // myprintf("%d\n", int_var, NULL);
    // puts("\n");
    // myprintf("test my print int:%d, int2:%d \n", int_var, int_var2, NULL);
    myprintf("%d", 9567982, NULL);
    myprintf("%d", 54321, NULL);
    myprintf("%d", 1000, NULL);
    myprintf("%d", 1024, NULL);

    puts("\nEND\n");
}