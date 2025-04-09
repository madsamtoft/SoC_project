#include "wildio.h"
#include <stdio.h>

int main(void) {
    while (1) {
        for (int i = 0; i < SWITCH_COUNT; i++) {
            setLed(i, readSwitch(i));
        }
        if (uartReady() & 0b1) {
            setUart(led_state);
        }
        delay(100000);
        if (uartReady() & 0b1) {
            setUart(led_state);
        }
    }
    return 0;
}
