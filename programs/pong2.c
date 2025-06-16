#include "../lib/wildvga.h"
#include "../lib/wildio.h"

#define BALL_RADIUS 3

struct pongBall {
    int x;
    int y;
    int vx;
    int vy;
};
typedef struct pongBall Ball;

void drawBall(Ball *ball, char color);
void updateBall(Ball* ball);

int main() {
    Ball ball = {160, 120, 1, 1}; // Center of screen
    Ball *ballPointer = &ball;

    drawScreen(BLACK); // Clear screen

    while(1) {
        // Erase old ball
        drawBall(ballPointer, BLACK);

        // Update ball position
        updateBall(ballPointer);

        // Draw new ball
        drawBall(ballPointer, WHITE);

        // Delay to control speed (adjust for your system)
        wait(100000);
    }

    return 0;
}

void drawBall(Ball* ball, char color) {
    drawCircle(ball->x, ball->y, BALL_RADIUS, color, 0);
}

void updateBall(Ball* ball) {
    int x = ball->x;
    int y = ball->y;
    int vx = ball->vx;
    int vy = ball->vy;

    // Bounce off left/right walls
    if (x - BALL_RADIUS <= 0 || x + BALL_RADIUS >= VGA_X_LIM - 1) {
        vx *= -1;
    }
    // Bounce off top/bottom walls
    if (y - BALL_RADIUS <= 0 || y + BALL_RADIUS >= VGA_Y_LIM - 1) {
        vy *= -1;
    }

    ball->x += vx;
    ball->y += vy;
    ball->vx = vx;
    ball->vy = vy;
}
