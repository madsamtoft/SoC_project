#include "wildio.h"

int main(void) {
    int ps2_data = 0;
    int uart_data = 0;
    while(1) {
        ps2_data = readPs2();
        if (uartReady() & 1) {
            setUart(ps2_data + '0');
        }
    }
}