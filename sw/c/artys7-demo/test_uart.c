#include <stddef.h>
#include "demo_system.h"
#include "gpio.h"


void test_uart(void) {
    // puts("Hello Opal Test\n");

    myprintf("test my print\n");
    char string_var = "a";
    myprintf(string_var);
}