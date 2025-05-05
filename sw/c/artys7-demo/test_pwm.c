#include <stdbool.h>
#include <stdint.h>

#include "demo_system.h"
#include "pwm.h"

void pwm_example() {

    // PWM variables
    uint32_t counter    = UINT8_MAX;
    uint32_t brightness = 0;
    bool ascending      = true;
    // The three least significant bits correspond to RGB, where B is the leas significant.
    uint8_t color = 7;

    while(1){
        // Going from bright to dim on PWM
        for (int i = 0; i < NUM_PWM_MODULES; i++) {
          set_pwm(PWM_FROM_ADDR_AND_INDEX(PWM_BASE, i), ((1 << (i % 3)) & color) ? counter : 0,
                  brightness ? 1 << (brightness - 1) : 0);
        }
        if (ascending) {
          brightness++;
          if (brightness >= 5) {
            ascending = false;
          }
        } else {
          brightness--;
          // When LEDs are off cycle through the colors
          if (brightness == 0) {
            ascending = true;
            color++;
            if (color >= 8) {
              color = 1;
            }
          }
        }
    }

}
