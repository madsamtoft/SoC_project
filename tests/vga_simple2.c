#include "wildio.h"

// void refreshScreen(char color);

int main(void) {
    int sw = 0;
    // while(1) {
        int x = 0;
        int y = 0;
    
        while(y < VGA_Y_MAX) {
            while(x < VGA_X_MAX) {
                sw = *switches & 0b111111;
                setPixel(x, y, sw);
                // return 1; // Only draw one pixel
                x = x+1;
            }
            x = 0;
            y = y+1;
        }
        y = 0;
    // }
    setLeds(0xFFFF);
    return 0;
}

