#include "../lib/wildio.h"

int main(void) {

    volatile char ps2_data;

    setUart('-');  // Initial UART debug output

    while (1) {
        ps2_data = readPs2();         // Read from PS/2 (MMIO at 0xf0040000)

        switch (ps2_data & 0xFF) {    // Always mask to ensure 8-bit comparison
            case W:
                setUart('1');
                break;
            case A:
                setUart('2');
                break;
            case S:
                setUart('3');
                break;
            case D:
                setUart('4');
                break;
            default:
                setUart('0');
                break;
        }
    }
}