#include "../lib/wildvga.h"
#include "../lib/wildio.h"

#define BALL_RADIUS 4

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
    int x_start = VGA_X_LIM/2;
    int y_start = VGA_Y_LIM/2;

    Ball ball = {x_start, y_start, 1, 0}; // Center of screen

    while(1) {
        // Instantiate timer
        startTimer(500);

        // Erase last ball
        drawBall(&ball, BLACK);
        
        // Update ball position
        updateBall(&ball);

        // Draw ball
        drawBall(&ball, WHITE);

        // Wait for timer to run out
        waitTimer();
    }
    
    startTimer(1000);
    setLeds(0xFFFF);
    waitTimer();
    return 0;
}

void drawBall(Ball* ball, char color) {
    //drawRectangle(ball->x, ball->y, BALL_RADIUS, BALL_RADIUS, color, 0);
    drawCircle(ball->x, ball->y, BALL_RADIUS, color, 0);
}

void updateBall(Ball* ball) {
    if (ball->x <= 0 || ball->x + 2*BALL_RADIUS >= VGA_X_LIM) {
        ball->vx *= -1;
    }
    if (ball->y <= 0 || ball->y + 2*BALL_RADIUS >= VGA_Y_LIM) {
        ball->vy *= -1;
    }

    ball->x += ball->vx;
    ball->y += ball->vy;

    setLeds(ball->x); // Debug
}
