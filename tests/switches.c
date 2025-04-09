#include "wildio.h"
#include <stdio.h>

int main(void) {
    int uart_ready = 0;
    int led_state = 0;
    int switch_state = 0;
    while (1) {
        for (int i = 0; i < SWITCH_COUNT; i++) {
            switch_state = readSwitch(i);
            setLed(i, switch_state);
        }
        delay(100000);
        uart_ready = uartReady();
        led_state = switch_state;
        if (uart_ready & 0b1) {
            setUart((led_state & 0xF) + '0');
        }
    }
    return 0;
}
