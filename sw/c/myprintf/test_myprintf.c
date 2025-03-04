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
            switch (*ptr + 1) {
            case 'd':
                /* code */
                puts("silly");
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
        puts(ptr[0]);
        // putchar(ptr);
        ptr++;
    }
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


void test_putchar(void) {
    // Print ASCII
    putchar(65); // A
    putchar(83); // S
    putchar(67); // C
    putchar(73); // I
    putchar(73); // I
    puts("\n");
    convert_to_ascii('0');
    convert_to_ascii('3');
    convert_to_ascii('6');
    convert_to_ascii('1');
    puts("\n");
    convert_to_ascii("125");
    puts("\n");
}

void test_puthex(void) {
    puthex(70); // P
    puthex(75); // U
    puthex(74); // T
    puthex(68); // H
    puthex(65); // E
    puthex(78); // X
}

void test_myprintf(void) {
    test_putchar();
    // test_puthex();
    puts("\n");
    myprintf("test my %d print\n");
    // char string_var = "a";
    // myprintf(string_var);
}