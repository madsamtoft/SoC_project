#include "wildio.h"
#include "wildvga.h"

void refreshScreen();

int main(void) {
    while(1) {
        refreshScreen(); 
    }
    setLeds(0xAAAA);
    return 0;
}

void refreshScreen() {
    int sw = 0;
    int x = 0;
    int y = 0;

    while(y < VGA_Y_LIM) {
        while(x < VGA_X_LIM) {
            sw = *switches & 0b111111;
            // setLeds(sw);
            setPixel(x, y, sw);
            x = x+1;
        }
        x = 0;
        y = y+1;
    }
    y = 0;
}
