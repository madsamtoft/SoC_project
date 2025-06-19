#include "../lib/wildio.h"

int main(void) {
    volatile int ps2_data;
    volatile int uart_ready;
    volatile char key;
    while(1) {
        char buffer[] = "Hello World\n";

        for (int i = 0; buffer[i] != '\0'; i++) {
            setUart(buffer[i]);
        }
    }
}