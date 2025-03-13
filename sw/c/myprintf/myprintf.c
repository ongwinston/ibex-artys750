#include <stddef.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "demo_system.h"
#include "gpio.h"
#include "dev_access.h"


int powerof(int32_t multiplicand, int32_t multiplier) {
    // puts("multiplicand:0x");
    // puthex(multiplicand);
    // puts("\n multiplier:0x");

    // puthex(multiplier);
    // puts("\n");
    int result = multiplicand;
    for(int i = 1; i < multiplier; i++) {
        result *= multiplicand;
    }
    // puts("Result is:0x");
    // puthex(result);
    // puts("\n");

    return result;
}

// Must be an int value
char convert_int_to_char(int value) {
    char ascii_of_value = '0';
    switch(value) {
        case 0:
            putchar(48);
            puts("\n");
            ascii_of_value = '0';
            // puthex(msb_digit);
            // return '0';
            // DEV_WRITE(0x80003000,0xffff);
            break;
        case 1:
            putchar(49);
            puts("\n");
            ascii_of_value = '1';
            // puthex(msb_digit);
            // return '1';
            // DEV_WRITE(0x80003000,0xaaa);
            break;
        case 2:
            putchar(50);
            puts("\n");
            ascii_of_value = '2';
            // puthex(msb_digit);
            // return '2';
            // DEV_WRITE(0x80003000,0xbbbb);
            break;
        case 3:
            putchar(51);
            puts("\n");
            ascii_of_value = '3';
            // puthex(msb_digit);
            // return '3';
            // DEV_WRITE(0x80003000,0xcccc);
            break;
        case 4:
            putchar(52);
            puts("\n");
            ascii_of_value = '4';
            // puthex(msb_digit);
            // return '4';
            // DEV_WRITE(0x80003000,0xdddd);
            break;
        case 5:
            putchar(53);
            puts("\n");
            ascii_of_value = '5';
            // puthex(msb_digit);
            // return '5';
            // DEV_WRITE(0x80003000,0xeeee);
            break;
        case 6:
            putchar(54);
            puts("\n");
            ascii_of_value = '6';
            // puthex(msb_digit);
            // return '6';
            // DEV_WRITE(0x80003000,0x1212);
            break;
        case 7:
            putchar(55);
            puts("\n");
            ascii_of_value = '7';
            // puthex(msb_digit);
            // return '7';
            // DEV_WRITE(0x80003000,0x3434);
            break;
        case 8:
            putchar(56);
            puts("\n");
            ascii_of_value = '8';
            // puthex(msb_digit);
            // return '8';
            // DEV_WRITE(0x80003000,0x5656);
            break;
        case 9:
            putchar(57);
            puts("\n");
            ascii_of_value = '9';
            // puthex(msb_digit);
            // return '9';
            // DEV_WRITE(0x80003000,0x6767);
            break;
        default:
            break;
    }
    return  ascii_of_value;
}

void print_int(int32_t val) {
    uint32_t cnt = 0;
    int32_t tmp = val;
    int32_t int_to_loop = val;
    float msb_digit;
    int32_t divisor = 0;
    DEV_WRITE(0x80003000,val);
    // puts("print_int:0x");
    // puthex(val);
    // puts("\n");

    // Count the number of digits
    while(abs(tmp) > 0) {
        tmp /= 10;
        cnt++;
        DEV_WRITE(0x80003000,cnt); // track counter
    }
    // puts("counter:");
    // puthex(cnt);
    // puts("\n");
    while (cnt != 0) {
        if(cnt != 1) {
            divisor = (powerof(10,(cnt-1)));
            msb_digit = int_to_loop / divisor;
        } else {
            // Final digit case just print this
            msb_digit = int_to_loop;
        }

        // puts("divisor:0x");
        // puthex(divisor);
        // puts("\n");
        // puts("val:0x");
        // puthex(val);
        // puts("\n");
        // puts("msb_digit:0x");
        // puthex(msb_digit);
        // puts("\n");
        convert_int_to_char(msb_digit);
        int_to_loop = int_to_loop - (msb_digit*divisor);
        // puts("New value val:0x");
        // puthex(int_to_loop);
        // puts("\n");
        // puts("Counter val:");
        // puthex(cnt);
        // puts("\n");
        cnt--;
    }
    // convert_int_to_char(msb_digit); // Print final
}

int myprintf(char* string, ...) {

    int32_t int_list_arg;
    // int sizeofstring = sizeof(string)/sizeof(string[0]);

    if(string == NULL) {
        return 1; //ERROR
    }

    va_list args;
    va_start(args, string);
    
    // Increment one arg as we dont want to grab the string value
    // char test = va_arg(args, string_len);

    // Iterate through String checking for format specifiers throughout
    while(*string) {

        // Check for format specifier '%'
        if(*string == '%') {
            string++;
            // Then check for the following specifierp
            switch (*string) {
                case 'd': // Integer
                    int_list_arg = va_arg(args, int32_t);
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
                    puts("UNSUPPORTED\n");
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
        }
        string++;
    }
    // puts(string);
    va_end(args);
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
