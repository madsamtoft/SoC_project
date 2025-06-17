#include <stdio.h>

#define PADDLE_WIDTH 8
#define PADDLE_HEIGHT 16

void draw4x4(int x, int y, char color);
void drawPaddle(int x, int y, char color);

int main(void) {
    // Example usage of the drawBall4x4 function
    //draw4x4(0, 0, 'W'); // Draw a red ball at position (5, 5)
    drawPaddle(0, 0, 'W');
    return 0;
}


void draw4x4(int x, int y, char color) {
    const char bitmap[4] = {
        0b0110,
        0b1111,
        0b1111,
        0b0110
    };

    for (int dy = 0; dy < 4; dy++) {
        for (int dx = 0; dx < 4; dx++) {
            if (bitmap[dy] & (1 << (3 - dx))) {
                //setPixel(x + dx, y + dy, color, 0);
                printf("Drawing pixel at (%d, %d) with color %c\n", x + dx, y + dy, color);
            }
        }
    }
}

void drawPaddle(int x, int y, char color) {
    
    const char sprite[PADDLE_HEIGHT] = {
        0b00111100,
        0b00111100,
        0b00111100,
        0b00111100,
        0b00111100,
        0b00111100,
        0b00111100,
        0b00111100,
        0b00111100,
        0b00111100,
        0b00111100,
        0b00111100,
        0b00111100,
        0b00111100,
        0b00111100,
        0b00111100
    };

    for (int dy = 0; dy < PADDLE_HEIGHT; dy++) {
        for (int dx = 0; dx < PADDLE_WIDTH; dx++) {
            if (sprite[dy] & (1 << (PADDLE_WIDTH - 1 - dx))) {
                printf("%c", color);
                //setPixel(x + dx, y + dy, color, 0);
            } else {
                printf(" ");
            }
        }
        printf("\t %d\n", dy);
    }
}