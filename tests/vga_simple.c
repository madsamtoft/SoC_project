// #include "wildio.h"
// #include <stdio.h>

#define VGA_BASE_ADDR 0xf0100000
volatile char * const vga = (volatile char *) VGA_BASE_ADDR;


void setPixel(int x, int y, char c);
// void wait(int cc);

int main(void) {
    int xlim = 320/4;
    int ylim = 240;
    char clim = 0b111111;

    int x = 0;
    int y = 0;
    char c = 0;

    while(1) {
        setPixel(x, y, c);
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

// void wait(int cc) {
//     volatile int i = 0;
//     while(i < cc) {
//         i += 1;
//     }
// }

void setPixel(int x, int y, char c) {
    volatile char * addrPtr = vga + (x & 0x1ff) + ((y & 0xff) << 9);
    // printf("%x, %d\n", addrPtr, c);
    *addrPtr = c;
    return;
}
