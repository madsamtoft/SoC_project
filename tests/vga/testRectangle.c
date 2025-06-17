#include "../../lib/wildvga.h"

void wait(volatile int delay);

int main(void) {
    int x = 0;
    int y = 0;
    int w = 20;
    int h = 20;
    char c = 0b111111;
    while(1) {
        drawRectangle(x++, y++, w, h, c++, 1);
        if(x >= VGA_X_LIM) {
            x = 0;
        }
        if(y >= VGA_Y_LIM) {
            y = 0;
        }
        wait(1000000);
    }
    return 0;
}

void wait(volatile int delay) {
    while (delay > 0) {
        delay--;
    }
    return;
}
