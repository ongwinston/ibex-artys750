
#include <stdint.h>
#include "demo_system.h"


int wishbone_master_test() {
    volatile uint32_t* wishboneBasePtr = (volatile uint32_t*)0x80005000;
    
    // Write to wishbone
    *wishboneBasePtr = 0x12345678;


    // Read from wishbone
    volatile uint32_t value = *wishboneBasePtr;

    return 0;
}
