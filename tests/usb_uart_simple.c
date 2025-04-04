#include "wildio.h"

int main(void) {
    int ps2_data = 0;
    int uart_ready = 0;
    char key = ' ';
    while(1) {
        ps2_data = readPs2();
        uart_ready = uartReady();
        key = readKey(ps2_data);
        if (uart_ready & 0b1) {
            setUart(key);
        }
    }
}