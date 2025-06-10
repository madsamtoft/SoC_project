#include "../wildvga.h"
#include "../wildio.h"

void wait(volatile int delay);

int main(void) {
    int x = 0;
    int y = 0;
    int w = 10;
    int h = 10;
    char c = 0b100001;
    while(1) {
        drawRectangle(x, y, w, h, c, 1);

        if(readButtons()) {
            x++;
            w--;
            c++;
            wait(5000000);
        }

        if(x >= VGA_X_LIM) {
            x = 0;
        }
        if(y >= VGA_Y_LIM) {
            y = 0;
        }
    }
    return 0;
}

void wait(volatile int delay) {
    while (delay > 0) {
        delay--;
    }
    return;
}
