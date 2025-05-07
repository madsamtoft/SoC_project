#include "wildio.h"

int main(void) {
    volatile int ps2_data;
    volatile int uart_ready;
    volatile char key;
    while(1) {
        ps2_data = readPs2();
        key = readKey(ps2_data);
        setUart(key);
    }
}