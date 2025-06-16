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
    int x = ball->x;
    int y = ball->y;
    int vx = ball->vx;
    int vy = ball->vy;

    // Bounce off left/right walls
    if (x <= 0) {
        vx *= -1;
        x = 0;
    } else if (x + (BALL_RADIUS*2) >= VGA_X_LIM) {
        vx *= -1;
        x = VGA_X_LIM - 2*BALL_RADIUS;
    }

    // Bounce off top/bottom walls
    if (y <= 0) {
        vy *= -1;
        y = 0;
    } else if (y + (BALL_RADIUS*2) >= VGA_Y_LIM) {
        vy *= -1;
        y = VGA_Y_LIM - 2*BALL_RADIUS;
    }
    

    ball->x += vx;
    ball->y += vy;
    ball->vx = vx;
    ball->vy = vy;
}
