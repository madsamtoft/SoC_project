#include "wildio.h"
volatile int wait = 0;

int main(void) {
    int ps2_data = 0;
    int uart_data = 0;
    int uart_ready = 0;
    while(1) {
        ps2_data = readPs2();
        uart_ready = uartReady();
        int value = 0;
        int x = 1;
        if (uart_ready & 0b1 & (ps2_data == 0b0)) {
            for(int i = 0; i < 8; i++) {
                while(!(uart_ready & 0b1)) {
                    wait++;
                }
                wait = 0;
                value += ps2_data << i;
            }
            setUart(value);
        }
    }
}