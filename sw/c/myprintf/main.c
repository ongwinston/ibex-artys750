// Copyright lowRISC contributors.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0


#include "demo_system.h"
#include "timer.h"
#include "test_myprintf.h"


int main(void) {

    int status = 0;

    test_uart();

    while(1) {
        asm volatile("nop");
    }


    return status;
}