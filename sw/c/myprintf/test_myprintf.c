#include <stddef.h>
#include "demo_system.h"
#include "gpio.h"


// Formatted print

// Input to a printf
// Long String array
// Format Specifier
// %d -> integer
// %u -> unsigned decimal integer
// %o -> octal
// %x -> unsigned hexadecimal
// %X -> unsigned hexadecimal Uppercase
// %f -> floating point 
// %F -> floating point uppercase
// %e -> Scientific notation 
// %E -> Scientific notation uppercase
// %c -> character
// %s -> String of characters
// %p -> Pointer address
// %n
// %% - Writes a single % to stdout stream

int myprintf(char* string) {

    if(string == NULL) {
        return 1; //ERROR
    }

    // New pointer value
    char* ptr = string;

    while(*ptr != '\0') {

        // Check for format specifier '%'
        if(*ptr == '%') {
            // Then check for the following specifier
            switch (*ptr + (char)1) {
            case 'd':
                /* code */
                break;
            case 'u':
                break;
            case 'o':
                break;
            case 'x':
                break;
            case 'X':
                break;
            case 'f' :
                break;
            case 'F':
                break;
            case 'e':
                break;
            case 'E':
                break;
            case 'c':
                break;
            case 's':
                break;
            case 'p':
                break;
            case 'n':
                break;
            case '%':
                break;
            default:
                break;
            }
        }

        // Otherwise put the character on the uart tx
        puts(ptr);
        ptr++;
    }
    return 0;
}


void test_myprintf(void) {
    myprintf("test my print\n");
    char string_var = "a";
    myprintf(string_var);
}