#include "wildio.h"

int main(void) {
    int xlim = 0b10100000;
    int ylim = 0b01111000;
    int clim = 0b111111;

    int x = 0;
    int y = 0;
    int c = 0;

    while(1) {
        x = x+1;
        if (x >= xlim) {
            x = 0;
            y = y+1;
            if (y >= ylim) {
                y = 0;
                c = c+1;
                if (c >= clim) {
                    c = 0;
                }
            }
        }
        setPixel(x, y, c);
    }
}