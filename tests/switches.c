#include "wildio.h"
#include <stdio.h>

int main(void) {
    int uart_ready = 0;
    int leds_state = 0;
    int switch_state = 0;
    while (1) {
        for (int i = 0; i < SWITCH_COUNT; i++) {
            switch_state = readSwitch(i);
            setLed(i, switch_state);
        }
        //delay(100000);
        uart_ready = uartReady();
        leds_state = returnLeds();
        if (uart_ready & 0b1) {
            setUart((leds_state < 10) ? ('0' + leds_state) : ('A' + (leds_state - 10)));
        }
    }
    return 0;
}
