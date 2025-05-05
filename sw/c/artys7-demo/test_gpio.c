/*
    Arty S7 50 GPIO driver
*/

#include <stdint.h>

// #include "demo_system.h"
// #include <stdbool.h>


#define GPIO_BASE_ADDR 0x80000000;
#define GPIO_END_ADDR 0x80000000 + 4*1024;


int drive_led() {
    // Do something

    // Writes to GPIO
    volatile uint32_t* gpioptr = GPIO_BASE_ADDR;
    *gpioptr = 0xbad0beef;


    // Find the LED base addr
    // Write to Output enable register
    //  - There is no output enable register
    //  - The gpio module boundary is not bi-directional

    // Write to its data register
    // The first 16 bits of data written to GPIO get put on its output pins
    *gpioptr = 0xff;

    return 0;
}