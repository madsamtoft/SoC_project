#ifndef WILDVGA_H
#define WILDVGA_H

#define VGA_BASE_ADDR 0xf0100000
#define VGA_X_LIM 320
#define VGA_Y_LIM 240
#define VGA_C_LIM 64

volatile char * const vga = (char *) VGA_BASE_ADDR;

const char BLACK =  0b000000;
const char WHITE =  0b111111;
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

void setPixel(int x, int y, char c, char wrap) {
    if(wrap) {
        x %= VGA_X_LIM;
        y %= VGA_Y_LIM;
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
            setPixel(x, y, c, 0);
            x = x+1;
        }
        x = 0;
        y = y+1;
    }
}

void drawRectangle(int x, int y, int w, int h, char c, char wrap) {
    // Draws a rectangle with:
    // x - top left x-coordinate
    // y - top left y-coordinate
    // w - horizontal width
    // h - vertical height
    // c - color value
    int xlim = x + w;
    int ylim = y + h;
    for(int i = y; i < ylim; i++) {
        for(int j = x; j < xlim; j++) {
            setPixel(j, i, c, wrap);
        }
    }
}

int sqrtApprox(int n) {
    int x = 0;
    while(x*x <= n) {
        x++;
    }
    if((x*x - n) <= (n - (x-1)*(x-1))) {
        return x;
    }
    return x-1;
}

int inCircle(int x, int y, int xCenter, int yCenter, unsigned int r) {
    int dx = x - xCenter;
    int dy = y - yCenter;
    int d = sqrtApprox(dx*dx + dy*dy);
    if (d <= r) {
        return 1;
    }
    return 0;
}

void drawCircle(int x, int y, unsigned int r, unsigned char c, char wrap) {
    // Draw a circle with:
    // x - top left x-coordinate
    // y - top left y-coordinate
    // r - radius
    // c - color value
    int xCenter = x + r;
    int yCenter = y + r;
    int xLim = x + 2*r;
    int yLim = y + 2*r;
    for(int i = y; i < yLim; i++) {
        for(int j = x; j < xLim; j++) {
            if(inCircle(j, i, xCenter, yCenter, r)) {
                setPixel(j, i, c, wrap);
            }
        }
    }
}

#endif
