#include "wildio.h"

int main(void) {
    int xlim = 320;
    int ylim = 240;
    char clim = 0b111111;

    int x = 0;
    int y = 0;
    char c = 0;

    while(1) {
        int sw = readSwitches() & 0b111111;
        setPixel(x, y, sw);
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
    }
    return 0;
}
