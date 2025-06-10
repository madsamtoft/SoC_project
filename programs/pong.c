#include "../tests/wildvga.h"
#include "../tests/wildio.h"

#define BALL_RADIUS 3

struct pongBall {
    int x;
    int y;
    int vx;
    int vy;
};
typedef struct pongBall Ball;

void drawBall(Ball *ball);
void updateBall(Ball* ball);

int main() {
    Ball ball = {10, 10, 1, 1};
    Ball *ballPointer = &ball;
    char btnU = 0;
    char btnD = 0;
    char btnL = 0;
    char btnR = 0;

    while(1) {
        drawScreen(BLACK);
        drawBall(ballPointer);
        btnU = readButton(BTN_UP);
        btnD = readButton(BTN_DOWN);
        btnL = readButton(BTN_LEFT);
        btnR = readButton(BTN_RIGHT);
        updateBall(ballPointer);
        wait(1666666);
    }

    return 0;
}

void drawBall(Ball* ball) {
    int x = ball->x;
    int y = ball->y;

    drawCircle(x, y, BALL_RADIUS, WHITE, 0);
}

void updateBall(Ball* ball) {
    int oldX = ball->x;
    int oldY = ball->y;
    int vx = ball->vx;
    int vy = ball->vy;

    if(oldX+BALL_RADIUS*2 >= VGA_X_LIM || oldX < 0) {
        vx *= -1;
    }
    if(oldY+BALL_RADIUS*2 >= VGA_Y_LIM || oldY < 0) {
        vy *= -1;
    }

    int newX = oldX + vx;
    int newY = oldY + vy;

    ball->vx = vx;
    ball->vy = vy;
    ball->x = newX;
    ball->y = newY;
}

void moveBall(Ball* ball, char u, char d, char l, char r) {
    int vx = ball->vx;
    int vy = ball->vy;

    if(r && !l) {
        vx = 1;
    } else if (!r && l) {
        vx = -1;
    }
    if(d && !u) {
        vy = 1;
    } else if (!d && u) {
        vy = -1;
    }

    ball->vx = vx;
    ball->vy = vy;
}