#include "../../lib/wildvga.h"

void wait(volatile int delay);

int main(void) {
    int x = 0;
    int y = 0;
    int w = 30;
    int h = 30;
    int dirX = 1;
    int dirY = 1;
    int c = 0;
    while(1) {
        drawScreen(BLACK);
        drawRectangle(x, y, w, h, c++ >> 4, 0);

        x += dirX;
        y += dirY;

        if(x+w >= VGA_X_LIM-1 || x <= 0) {
            dirX *= -1;
        }
        if(y+h >= VGA_Y_LIM-1 || y <= 0) {
            dirY *= -1;
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
