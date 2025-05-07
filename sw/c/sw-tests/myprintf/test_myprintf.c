#include <stddef.h>
#include "demo_system.h"
#include "gpio.h"
#include "myprintf.h"
#include "dev_access.h"

void test_myprintf(void) {

    // Test print zero
    int zero = 0;
    myprintf("zero %d\n", zero, NULL);

    int int_var = 123;
    int int_var2 = 9;
    myprintf("test %d\n", int_var, NULL);
    myprintf("test my print int:%d, int2:%d, done\n", int_var, int_var2, NULL);
    myprintf("%d \n", 9567982, NULL);
    myprintf("%d\n", 54321, NULL);
    myprintf("%d\n", 1000, NULL);
    myprintf("%d\n", 1024, NULL);
    myprintf("%d\n", 0, NULL);
    int int_var3 = 7843; // 0x1ea3
    int32_t int_var4 = -10241; // 0x2801
    myprintf("%d,and Negative number: %d\n", int_var3, int_var4, NULL);

    puts("\nEND\n");
}
