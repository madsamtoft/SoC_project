#ifndef WILDVGA_H
#define WILDVGA_H

#define VGA_BASE_ADDR 0xf0100000
#define VGA_X_LIM 320
#define VGA_Y_LIM 240
#define VGA_C_MAX 64

volatile char * const vga = (char *) VGA_BASE_ADDR;

const char BLACK =  0b000000;
const char RED =    0b110000;
const char GREEN =  0b001100;
const char BLUE =   0b000011;

unsigned char color(unsigned char r, unsigned char g, unsigned char b) {
    if(r > 0b11) {
        r = 0b11;
    }
    if(g > 0b11) {
        b = 0b11;
    }
    if(b > 0b11) {
        b = 0b11;
    }
    return (r << 4) + (g << 2) + (b);
}

void setPixel(int x, int y, char c) {
    // Modulo x and y
    while(x >= VGA_X_LIM) {
        x -= VGA_X_LIM;
    }
    while(y >= VGA_Y_LIM) {
        y -= VGA_Y_LIM;
    }

    int xOffset = x & 0x1ff;
    int yOffset = (y & 0xff) << 9;
    volatile char * addrPtr = vga + (xOffset + yOffset); // Only works because charsize is 1 byte
    *addrPtr = c;
}

void drawScreen(char c) {
    int x = 0;
    int y = 0;

    while(y < VGA_Y_LIM) {
        while(x < VGA_X_LIM) {
            setPixel(x, y, c);
            x = x+1;
        }
        x = 0;
        y = y+1;
    }
}

void drawRectangle(int x, int y, int w, int h, char c) {
    int xlim = x + w;
    int ylim = y + h;
    for(int i = y; i < ylim; i++) {
        for(int j = x; j < xlim; j++) {
            setPixel(j, i, c);
        }
    }
}

#endif
