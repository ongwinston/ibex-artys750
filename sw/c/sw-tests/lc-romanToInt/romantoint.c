#include <stddef.h>
#include "demo_system.h"
#include "myprintf.h"

int chartoInt(char* s) {
    switch(*s) {
        case 'I':
            return 1;
            break;
        case 'V':
            return 5;
        case 'X':
            return 10;
            break;
        case 'L':
            return 50;
        case 'C':
            return 100;
        case 'D':
            return 500;
        case 'M':
            return 1000;
        default:
            myprintf("ERROR: Not supported String\n");
            return 0;
    }

}

    // Rules of Roman Numerals
    //  1) Repeating Numerals result in their sum
    //  2) No more than 3 repeating numerals
    //  3) The Letters V, L and D are not repeated
    //  4) Only I, X, and C can be used for subtraction
    //  5) When a Numeral is placed after another numeral of greater value,
    //      The result is their sum
    //  6) When a numeral is placed before a numeral of greater value,
    //      The result is their difference
    //  7) When a Numeral is placed between two greater numeral values,
    //      The numeral is the difference with the numeral after it on its right
    //  8) To multiply a numeral by 1000, a bar is placed over it
    //  9) Roman numerals do not follow place value system
    //  10) There is no numeral for zero

int romanToInt(char* s) {
    int converted_int = 0;
    int current_int;
    int previous_int = 0;

    if(s == NULL) {
        // ERROR
        return 1;
    }

    // Declare new char pointer to iterate with
    char* ptr = s;

    // Grab the first char value
    converted_int = chartoInt(ptr);
    previous_int = converted_int;
    ptr++;

    while(*ptr != '\0') {
        current_int = chartoInt(ptr);

        if(current_int > previous_int) {
            converted_int = (converted_int - previous_int) + (current_int - previous_int);
        } else {
            converted_int = converted_int + current_int;
        }

        previous_int = current_int;
        ptr++;
        // myprintf("val:0x%x\n", converted_int);
        // puthex(converted_int);
        // myprintf("\n");
    }

    return converted_int;
}

int testRomanToInt(void) {
    myprintf("START TEST\n");
    int status = 0;
    int ret_integer;

    ret_integer = romanToInt("CLI"); // (151) = 100 + 50 + 1
    if(ret_integer != 151){
        myprintf("Failed CLI (151)\n");
        puthex(ret_integer);
        status = 1;
    } else {
        myprintf("Passed 'CLI', val:%d\n", ret_integer);
    }
    ret_integer = romanToInt("III"); //  1 + 1 + 1
    if(ret_integer != 3){
        myprintf("Failed III (3)\n");
        puthex(ret_integer);
        status = 1;
    } else {
        myprintf("Passed 'III', val:%d\n",ret_integer);
    }
    ret_integer = romanToInt("LVIII"); // 50 + 5 + 3
    if(ret_integer != 58){
        myprintf("Failed LVIII (58) \n");
        puthex(ret_integer);
        status = 1;
    } else {
        myprintf("Passed 'LVIII', val:%d\n", ret_integer);
    }
    ret_integer = romanToInt("MCMXCIV"); // 1000(M) + 900(CM) + 90(XC) + 4(IV)
    if(ret_integer != 1994){
        myprintf("Failed MCMXCIV (1994)\n");
        puthex(ret_integer);
        status = 1;
    } else {
        myprintf("Passed 'MCMXCIV', val:%d\n", ret_integer);
    }
    ret_integer = romanToInt("XVIII");
    if(ret_integer != 18){
        myprintf("Failed XVIII (18)\n");
        puthex(ret_integer);
        status = 1;
    } else {
        myprintf("Passed 'XVIII', val:%d\n", ret_integer);
    }
    ret_integer = romanToInt("XXIV");
    if(ret_integer != 24){
        myprintf("Failed XXIV (24)\n");
        puthex(ret_integer);
        status = 1;
    } else {
        myprintf("Passed 'XXIV', val:%d\n", ret_integer);
    }

    if(status == 1) {
        myprintf("Some FAILED\n");
    } else {
        myprintf("All PASSED\n");
    }
    return status;
}


