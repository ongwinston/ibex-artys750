
#include "demo_system.h"
#include "dev_access.h"
#include "myprintf.h"
#include "math_module.h"


// Test 01
void test_mult_01(int32_t data_a, int32_t data_b) {

    // Config to Multiply
    configure_mult();
    
    // Write to wishbone
    write_reg(DATA_A_ADDR, data_a);
    write_reg(DATA_B_ADDR, data_b);

    // Read from mathModule
    int32_t value = read_result();

    myprintf("Mult value %d\n", value);

    // Software Multiply
    software_multiply(data_a, data_b);
}

void test_sqrt_01(int32_t data_a) {
    configure_sqrt();
    write_reg(DATA_A_ADDR, data_a);
    int32_t value = read_result();
    myprintf("Sqrt value: %d\n", value);
    // software_sqrt();
}

void software_multiply(int32_t data_a, int32_t data_b){
    write_reg(DATA_A_ADDR, 0xffff0f0f);
    int32_t result = data_a * data_b;
    // write_data_a
    write_reg(DATA_A_ADDR, 0x0badc0de);
}

int main(void) {

    // Init math module

    test_mult_01(4, 3);
    test_sqrt_01(4);

    while(1) {

    }

    return 0;
}