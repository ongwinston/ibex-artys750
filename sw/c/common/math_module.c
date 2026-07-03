#include "math_module.h"
#include "demo_system.h"
#include "dev_access.h"


void write_reg(uint32_t reg, int32_t data) {
    // volatile uint32_t* module_ptr;
    // if(reg == DATA_A_ADDR) {
    //     module_ptr = (volatile uint32_t*) DATA_A_ADDR;

    // } else if (reg == DATA_B_ADDR) {
    //     module_ptr = (volatile uint32_t*) DATA_B_ADDR;
    // }
    // *module_ptr = data;
    DEV_WRITE(reg, data);
}

int32_t read_result(void) {
    return DEV_READ(MATH_OP_ADDR);
}

// Mult
void configure_mult(void) {
    math_op_t op = mult;
    DEV_WRITE(MATH_OP_ADDR, op);
}

// Sqrt
void configure_sqrt(void) {
    math_op_t op = sqrt;
    DEV_WRITE(MATH_OP_ADDR, op);
}