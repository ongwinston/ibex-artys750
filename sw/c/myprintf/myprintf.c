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
            ptr++;
            // Then check for the following specifier
            switch (*ptr) {
                case 'd': //Integer
                    /* code */
                    puts("silly");
                    // call Integer formatter with first variable
                    break;
                case 'u': // Unsigned Decimal Integer
                    break;
                case 'o': // Octal
                    break;
                case 'x': // Unsigned Hexadecimal
                    break;
                case 'X': // Unsigned Hexadecimal Uppercase
                    break;
                case 'f' : // Floating Point
                    break;
                case 'F': // Floating Point Uppercase
                    break;
                case 'e': // Scientific Notation
                    break;
                case 'E': // Scientific Notation Uppercase
                    break;
                case 'c': // Character
                    break;
                case 's': // String of Characters
                    break;
                case 'p': // Pointer Address
                    break;
                case 'n': //
                    break;
                case '%': // Print '%'
                    break;
                default:
                    break;
            }
        }
        ptr++;
    }
    puts(string);
    return 0;
}


void convert_to_ascii(char s) {
    switch(s) {
        case '!':
            putchar(33);
            break;
        case '"':
            putchar(34);
            break;
        case '#':
            putchar(35);
            break;
        case '$':
            putchar(36);
            break;
        case '%':
            putchar(37);
            break;
        case '&':
            putchar(38);
            break;
        case '\'':
            putchar(39);
            break;
        case '(':
            putchar(40);
            break;
        case ')':
            putchar(41);
            break;
        case '*':
            putchar(42);
            break;
        case '+':
            putchar(43);
            break;
        case ',':
            putchar(44);
            break;
        case '-':
            putchar(45);
            break;
        case '.':
            putchar(46);
            break;
        case '/':
            putchar(47);
            break;
        case '0':
            putchar(48);
            break;
        case '1':
            putchar(49);
            break;
        case '2':
            putchar(50);
            break;
        case '3':
            putchar(51);
            break;
        case '4':
            putchar(52);
            break;
        case '5':
            putchar(53);
            break;
        case '6':
            putchar(54);
            break;
        case '7':
            putchar(55);
            break;
        case '8':
            putchar(56);
            break;
        case '9':
            putchar(57);
            break;
        case ':':
            putchar(58);
            break;
        case ';':
            putchar(59);
            break;
        case '<':
            putchar(60);
            break;
        case '=':
            putchar(61);
            break;
        case '>':
            putchar(62);
            break;
        case '?':
            putchar(63);
            break;
        case '@':
            putchar(64);
            break;
        default:
            break;
    }
}
