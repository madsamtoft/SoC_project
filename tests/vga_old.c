#include "wildio.h"
// #include <stdio.h>

// #define VGA_BASE_ADDR 0xf0100000
// volatile char * const vga = (volatile char *) VGA_BASE_ADDR;

// const int XLIM = 320;
// const int YLIM = 240;

void refreshScreen(char color);
void setPixel(int x, int y, char c);

int main(void) {
    while(1) {
        char sw = readSwitches() & 0b111111;
        refreshScreen(sw);
    }
    return 0;
}

void refreshScreen(char color) {
    int x = 0;
    int y = 0;

    while(y < VGA_Y_MAX) {
        while(x < VGA_X_MAX) {
            setPixel(x, y, color);
            x = x+1;
        }
        x = 0;
        y = y+1;
    }
}

void setPixel(int x, int y, char c) {
    int xOffset = x & 0x1ff;
    int yOffset = (y & 0xff) << 9;
    volatile char * addrPtr = vga + xOffset + yOffset;
    // printf("%x, %d\n", addrPtr, c);
    *addrPtr = c;
    return;
}
