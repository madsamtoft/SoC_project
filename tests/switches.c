#include "wildio.h"
#include <stdio.h>

int main(void) {
    int uart_ready = 0;
    int led_state = 0;
    while (1) {
        for (int i = 0; i < SWITCH_COUNT; i++) {
            setLed(i, readSwitch(i));

            uart_ready = uartReady();
            led_state = getLeds();
            if (uart_ready & 0b1) {
                setUart(led_state & 0xF);
            }
            delay(100000);
            uart_ready = uartReady();
            led_state = getLeds();
            if (uart_ready & 0b1) {
                setUart(led_state & 0xF);
            }
        }
    }
    return 0;
}
