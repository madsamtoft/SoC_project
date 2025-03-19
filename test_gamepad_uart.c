#include "wildio.h"

int main(void) {
    int ps2_data = 0;
    int uart_data = 0;
    int uart_ready = 0;
    while(1) {
        ps2_data = readPs2();
        uart_ready = uartReady();
        if (uart_ready) {
            setUart(ps2_data);
        }
    }
}