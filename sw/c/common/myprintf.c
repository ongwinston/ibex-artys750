#include <stddef.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "demo_system.h"
#include "gpio.h"
#include "dev_access.h"


int powerof(int32_t multiplicand, int32_t multiplier) {
    int result = multiplicand;
    for(int i = 1; i < multiplier; i++) {
    result *= multiplicand;
    }
    return result;
}

// Must be an int value of 0-9
char convert_int_to_char(int value) {
    char ascii_of_value = '0';
    switch(value) {
    case 0:
        return '0';
    case 1:
        return '1';
    case 2:
        return '2';
    case 3:
        return '3';
    case 4:
        return '4';
    case 5:
        return '5';
    case 6:
        return '6';
    case 7:
        return '7';
    case 8:
        return '8';
    case 9:
        return '9';
    default:
        break;
    }
    return  ascii_of_value; // ERROR
}

char print_int(int32_t val/* , char* buf_ptr */) {
    uint32_t cnt = 0;
    int32_t tmp = val;
    float msb_digit;
    int32_t divisor = 0;

    if(val < 0) {
        // Convert to positive
        val = ~val + 1;
    }

    // Count the number of digits
    while(abs(tmp) > 0) {
        tmp /= 10;
        cnt++;
    }
    // puts("counter:");
    // puthex(cnt);
    // puts("\n");

    // Now loop over each Digit and print it out
    while (cnt != 0) {
        if(cnt != 1) {
            divisor = (powerof(10,(cnt-1)));
            msb_digit = val / divisor;
        } else {
            // This is the final digit so just print
            msb_digit = val;
        }

        /* puts("divisor:0x"); */
        /* puthex(divisor); */
        /* puts("\n"); */
        /* puts("val:0x"); */
        /* puthex(val); */
        /* puts("\n"); */
        /* puts("msb_digit:0x"); */
        /* puthex(msb_digit); */
        /* puts("\n"); */

        putchar(convert_int_to_char(msb_digit)); // Return ASCII Char from int

        val = val - (msb_digit*divisor);
        /* puts("New value val:0x"); */
        /* puthex(val); */
        /* puts("\n"); */
        /* puts("Counter val:"); */
        /* puthex(cnt); */
        /* puts("\n"); */
        cnt--;
    }
    return (char)'0'; // TODO: Fix
}


// Return Success or failure
// Takes character string and variable list of arguments,
// Creates a character buffer which then prints
int myprintf(char* string, ...) {

    int32_t int_list_arg;
    // int sizeofstring = sizeof(string)/sizeof(string[0]);

    if(string == NULL) {
    return 1; //ERROR
    }

    va_list args;
    va_start(args, string);

    /* int buf_elements = 4; */
    // Create a String array buffer to store the completed print
    /* char* print_buf_ptr = (char*) malloc(buf_elements * sizeof(char)); */
    /* if(print_buf_ptr == NULL) { */
    /*   return NULL; */
    /* } */

    // Iterate through String checking for format specifiers throughout
    while(*string) {

    // Check for format specifier '%'
    if(*string == '%') {
        string++;
        // Then check for the following specifierp
        switch (*string) {
        case 'd': // Integer
            int_list_arg = va_arg(args, int32_t);
            if(int_list_arg < 0) {
                putchar(45); // Print - sign
            }
            print_int(int_list_arg);
            // puts("List Argument:0x");
            // puthex(int_list_arg);
            // puts("\n");
            // putchar(int_list_arg);
            // puts("*");
            break;
        case 'u': // Unsigned Decimal Integer
            puts("UNSUPPORTED\n");
            break;
        case 'o': // Octal
            puts("UNSUPPORTED\n");
            break;
        case 'x': // Unsigned Hexadecimal
            int_list_arg = va_arg(args, int32_t);
            puthex(int_list_arg);
            break;
        case 'X': // Unsigned Hexadecimal Uppercase
            puts("UNSUPPORTED\n");
            break;
        case 'f' : // Floating Point
            puts("UNSUPPORTED\n");
            break;
        case 'F': // Floating Point Uppercase
            puts("UNSUPPORTED\n");
            break;
        case 'e': // Scientific Notation
            puts("UNSUPPORTED\n");
            break;
        case 'E': // Scientific Notation Uppercase
            puts("UNSUPPORTED\n");
            break;
        case 'c': // Character
            puts("UNSUPPORTED\n");
            break;
        case 's': // String of Characters
            puts("UNSUPPORTED\n");
            break;
        case 'p': // Pointer Address
            puts("UNSUPPORTED\n");
            break;
        case 'n': //
            puts("UNSUPPORTED\n");
            break;
        case '%': // Print '%'
            // print_ascii('%');
            puts("UNSUPPORTED\n");
            break;
        default:
            break;
        }
    } else {
        // Else just output the next char of the string
        putchar(*string);
        /* print_buf_ptr = *string; */
        /* print_buf_ptr++; */
    }
    string++;
    }
    // puts(string);
    va_end(args);
    /* free(print_buf_ptr); */
    return 0;
}


// void print_ascii(char s) {
//     switch(s) {
//         case '!':
//             putchar(33);
//             break;
//         case '"':
//             putchar(34);
//             break;
//         case '#':
//             putchar(35);
//             break;
//         case '$':
//             putchar(36);
//             break;
//         case '%':
//             putchar(37);
//             break;
//         case '&':
//             putchar(38);
//             break;
//         case '\'':
//             putchar(39);
//             break;
//         case '(':
//             putchar(40);
//             break;
//         case ')':
//             putchar(41);
//             break;
//         case '*':
//             putchar(42);
//             break;
//         case '+':
//             putchar(43);
//             break;
//         case ',':
//             putchar(44);
//             break;
//         case '-':
//             putchar(45);
//             break;
//         case '.':
//             putchar(46);
//             break;
//         case '/':
//             putchar(47);
//             break;
//         case '0':
//             putchar(48);
//             break;
//         case '1':
//             putchar(49);
//             break;
//         case '2':
//             putchar(50);
//             break;
//         case '3':
//             putchar(51);
//             break;
//         case '4':
//             putchar(52);
//             break;
//         case '5':
//             putchar(53);
//             break;
//         case '6':
//             putchar(54);
//             break;
//         case '7':
//             putchar(55);
//             break;
//         case '8':
//             putchar(56);
//             break;
//         case '9':
//             putchar(57);
//             break;
//         case ':':
//             putchar(58);
//             break;
//         case ';':
//             putchar(59);
//             break;
//         case '<':
//             putchar(60);
//             break;
//         case '=':
//             putchar(61);
//             break;
//         case '>':
//             putchar(62);
//             break;
//         case '?':
//             putchar(63);
//             break;
//         case '@':
//             putchar(64);
//             break;
//         default:
//             break;
//     }
// }
