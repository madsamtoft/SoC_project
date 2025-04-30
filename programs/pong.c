// #include <stdio.h>

// VGA base address: 0xf010_0000
// VGA address decomposition: 0b00000000_00000000_0yyyyyyy_xxxxxxxx
// VGA data: 0b00000000_00000000_00000000_00000000_00rrbbgg
#define VGA_BASE_ADDR 0xf0100000
int volatile * const vga = (volatile int *) VGA_BASE_ADDR;

struct pongBall {
    int x;
    int y;
};
typedef struct pongBall Ball;

void printPixel(int x, int y);
void printBall(Ball *ball);

int main() {
    Ball ball = {0, 0};
    Ball *ballPointer = &ball;

    printBall(ballPointer);

    // printf("x = %d\n", ball.x);
    // printf("y = %d", ball.y);

    return 0;
}





void printPixel(int x, int y) {

}

void printBall(Ball *ball) {
    int x = ball->x;
    int y = ball->y;

    printPixel(x-1, y-1);
    printPixel(x,   y-1);
    printPixel(x+1, y-1);

    printPixel(x-1, y);
    printPixel(x,   y);
    printPixel(x+1, y);
    
    printPixel(x-1, y+1);
    printPixel(x,   y+1);
    printPixel(x+1, y+1);
}