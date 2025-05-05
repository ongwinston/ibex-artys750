

#include "demo_system.h"
#include "dev_access.h"
#include "myprintf.h"

#define WISHBONE_MASTER_BASE_ADDR 0x80005000
#define PWM_BASE_ADDR 0x80003000

int main(void) {
    myprintf("---\n");

    // Start write to PWM
    DEV_WRITE(PWM_BASE_ADDR, 0xffffffff);


    // Write to wishbone master device and read it back
    DEV_WRITE(WISHBONE_MASTER_BASE_ADDR, 0xffffffff);
    uint32_t read_val = DEV_READ(WISHBONE_MASTER_BASE_ADDR);

    myprintf("read_val 0%x\n", read_val);

    while(1) {
        asm volatile("nop");
    }

    return 0;
}