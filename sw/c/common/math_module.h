#include <stdint.h>

#define MATH_OP_ADDR 0x80005000
#define DATA_A_ADDR 0x80005004
#define DATA_B_ADDR 0x80005008

typedef enum {
    mult = 0,
    sqrt = 1
} math_op_t;


void write_reg(uint32_t reg, int32_t data);
int32_t read_result(void);
void configure_mult(void);
void configure_sqrt(void);