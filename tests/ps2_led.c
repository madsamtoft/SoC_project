#include "wildio.h"

int main(void) {
    int ps2_data = 0;
    while(1) {
        ps2_data = readPs2() & 0xFFFF;
        setLeds(ps2_data);
    }
}