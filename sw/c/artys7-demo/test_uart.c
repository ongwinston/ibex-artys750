#include <stddef.h>
#include "demo_system.h"
#include "gpio.h"


int myprintf(char* string) {

    if(string == NULL) {
        return 1; //ERROR
    }

    // New pointer value
    char* ptr = string;

    while(*ptr != '\0') {
        puts(ptr);
        ptr++;
    }
    return 0;
}


void test_uart(void) {
    // puts("Hello Opal Test\n");

    myprintf("test my print\n");
    char string_var = "a";
    myprintf(string_var);
}