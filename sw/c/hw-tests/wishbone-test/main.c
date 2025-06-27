

#include "demo_system.h"
#include "dev_access.h"
#include "myprintf.h"

#define WISHBONE_MASTER_BASE_ADDR 0x80005000
#define PWM_BASE_ADDR 0x80003000

#define DM_BASE_ADDR 0x1a110000
#define DM_ADDR 0x1a110000
// #define DM_ADDR 0x1a110380
#define DM_CONTROL_ADDR 0x1a110380 + 0x10
#define DM_STATUS_ADDR 0x1a110380 + 0x11



/**
 * Test the cores ability to halt itself via the Debug Module
 * Write to debug module to activate it
 * And send a halt request to the core (itself)
 * Where the core should then interrupt itself and move into debug address space
 * Which notifies the Debug module that it is halted
 * 
 */
void test_debug_module() {

    // Write to DEBUG MODULE
    DEV_WRITE(DM_ADDR,0xdeadbeef);
    uint32_t dmstatus = DEV_READ(DM_STATUS_ADDR);

    // myprintf("dmstatus:0x%x\n", dmstatus);
    DEV_WRITE(PWM_BASE_ADDR, dmstatus);

    // Configure the hart to select, as in this hart (hart 0)

    // Try to write to DMCONTROL and set dmactive
    DEV_WRITE(DM_CONTROL_ADDR,0x00000001);

}


/**
 * Test of wishbone device
 * Lets write to the address space of the wishbone device
 * and read it back to see if the data was saved
 */
void test_wishbone_peripheral() {

    // Write to wishbone master device and read it back
    DEV_WRITE(WISHBONE_MASTER_BASE_ADDR, 0xffffffff);
    uint32_t read_val = DEV_READ(WISHBONE_MASTER_BASE_ADDR);

    myprintf("read_val 0%x\n", read_val);

}

int main(void) {

    myprintf("---\n");

    // Start write to PWM
    DEV_WRITE(PWM_BASE_ADDR, 0xffffffff);

    test_debug_module();

    test_wishbone_peripheral();

    while(1) {
        asm volatile("nop");
    }

    return 0;
}