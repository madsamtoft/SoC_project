#include "wildio.h"

int main(void) {
    volatile char ps2_data;
    ps2_data = '-';
    setUart(ps2_data);

    while(1) {
        ps2_data = readPs2();
        setUart(ps2_data);
    }
    setLeds(0xFFFF);
}