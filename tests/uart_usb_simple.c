#include "../lib/wildio.h"

int main(void) {
    volatile char ps2_data;
    ps2_data = '-';
    putCharUart(ps2_data);

    while(1) {
        ps2_data = readPs2();
        putCharUart(ps2_data);
    }
    setLeds(0xFFFF);
}