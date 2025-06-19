#include "../lib/wildio.h"

int main(void) {

    volatile char ps2_data = '-';

    putCharUart(ps2_data);  // Initial UART debug output

    while (1) {
        ps2_data = readPs2();         // Read from PS/2 (MMIO at 0xf0040000)
        //putCharUart(ps2_data);
        
        switch (ps2_data & 0xFF) {    // Always mask to ensure 8-bit comparison
            case W:
                putCharUart('1');
                break;
            case A:
                putCharUart('2');
                break;
            case S:
                putCharUart('3');
                break;
            case D:
                putCharUart('4');
                break;
            default:
                putCharUart('0');
                break;
        }
    }
}