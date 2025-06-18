#include "../lib/wildvga.h"
#include "../lib/wildio.h"

#define BALL_SIZE 6
#define BALL_SPEED 1

#define WALL_WIDTH 5
#define WALL_HEIGHT 60
#define WALL_MARGIN 2
#define WALL_SPEED 4

struct pongBall {
    int x;
    int y;
    int vx;
    int vy;
};
typedef struct pongBall Ball;

struct pongWall {
    int x;
    int y;
};
typedef struct pongWall Wall;

// Function declarations
void fsm(Ball* ball, Wall* wallLeft, Wall* wallRight, char btnU, char btnD, char btnL, char btnR);
void drawBall(Ball ball, char color);
void updateBall(Ball* ball, Wall lWall, Wall rWall);
void checkCollision(Ball* ball, Wall lWall, Wall rWall);
void checkOutOfBounds(Ball* ball);
void drawWall(Wall wall, char color);
void updateWall(Wall* wall, char u, char d);
void moveBall(Ball* ball, char u, char d, char l, char r);

int main() {
    Ball ball = {VGA_X_LIM/2, VGA_Y_LIM/2, BALL_SPEED, BALL_SPEED};
    Wall wallLeft = {WALL_MARGIN, WALL_MARGIN};
    Wall wallRight = {VGA_X_LIM - 2*WALL_MARGIN - 2*WALL_WIDTH, WALL_MARGIN};

    volatile char btns = 0;
    char btnU = 0;
    char btnD = 0;
    char btnL = 0;
    char btnR = 0;
    volatile char sw = 0;

    drawScreen(BLACK);
    setPixel(1, 1, RED, 0);
    setPixel(VGA_X_LIM-1, VGA_Y_LIM-1, GREEN, 0);

    while(1) {
        startTimer(1000 / 30);

        btns = readButtons();
        btnU = (btns >> 0) & 0b1;
        btnD = (btns >> 2) & 0b1;
        btnL = (btns >> 3) & 0b1;
        btnR = (btns >> 1) & 0b1;
        sw = readSwitches();

        fsm(&ball, &wallLeft, &wallRight, btnU, btnD, btnL, btnR);

        waitTimer();
    }

    return 0;
}

void fsm(Ball* ball, Wall* wallLeft, Wall* wallRight, char btnU, char btnD, char btnL, char btnR) {
    switch(readSwitches() & 0b11) {
        case 0b00:
            drawBall(*ball, BLACK);
            drawWall(*wallLeft, BLACK);
            drawWall(*wallRight, BLACK);

            updateWall(wallLeft, btnU, btnL);
            updateWall(wallRight, btnR, btnD);
            updateBall(ball, *wallLeft, *wallRight);

            drawBall(*ball, WHITE);
            drawWall(*wallLeft, WHITE);
            drawWall(*wallRight, WHITE);
            break;
        case 0b01:
            drawBall(*ball, BLACK);
            drawWall(*wallLeft, BLACK);
            drawWall(*wallRight, BLACK);

            moveBall(ball, btnU, btnD, btnL, btnR);
            checkCollision(ball, *wallLeft, *wallRight);
            checkOutOfBounds(ball);

            drawBall(*ball, WHITE);
            drawWall(*wallLeft, WHITE);
            drawWall(*wallRight, WHITE);
            break;
        default:
            break;
    }
}

void drawBall(Ball ball, char color) {
    drawSquare(ball.x, ball.y, BALL_SIZE, color, 0);
}

void updateBall(Ball* ball, Wall lWall, Wall rWall) {
    checkCollision(ball, lWall, rWall);
    ball->x += ball->vx;
    ball->y += ball->vy;
    checkOutOfBounds(ball);
}

void checkCollision(Ball* ball, Wall lWall, Wall rWall) {
    int xLeft = ball->x;
    int xRight = ball->x + BALL_SIZE;
    int yTop = ball->y;
    int yBot = ball->y + BALL_SIZE;

    int lWall_xRight = lWall.x + WALL_WIDTH;
    int lWall_yTop = lWall.y;
    int lWall_yBot = lWall.y + WALL_HEIGHT;

    int rWall_xLeft = rWall.x;
    int rWall_yTop = rWall.y;
    int rWall_yBot = rWall.y + WALL_HEIGHT;

    if (xLeft <= lWall_xRight && yBot >= lWall_yTop && yTop <= lWall_yBot && ball->vx < 0) {
        ball->vx *= -1;
    } else if (xRight >= rWall_xLeft && yBot >= rWall_yTop && yTop <= rWall_yBot && ball->vx > 0) {
        ball->vx *= -1;
    }

    if (yTop <= 0 && ball->vy < 0) {
        ball->vy *= -1;
    } else if (yBot >= VGA_Y_LIM && ball->vy > 0) {
        ball->vy *= -1;
    }

    if (xRight >= VGA_X_LIM - 4 && ball->vx > 0) {
        ball->x = VGA_X_LIM/2;
        ball->y = VGA_Y_LIM/2;
        ball->vx = -BALL_SPEED;
    } else if (xLeft <= 2 && ball->vx < 0) {
        ball->x = VGA_X_LIM/2;
        ball->y = VGA_Y_LIM/2;
        ball->vx = BALL_SPEED;
    }
}

void checkOutOfBounds(Ball* ball) {
    if (ball->x < 0 || ball->x >= VGA_X_LIM || ball->y < 0 || ball->y >= VGA_Y_LIM) {
        ball->x = VGA_X_LIM/2;
        ball->y = VGA_Y_LIM/2;
    }
}

void drawWall(Wall wall, char color) {
    drawRectangle(wall.x, wall.y, WALL_WIDTH, WALL_HEIGHT, color, 0);
}

void updateWall(Wall* wall, char u, char d) {
    int yTop = wall->y;
    int yBot = yTop + WALL_HEIGHT;

    if (d && !u && yBot < VGA_Y_LIM - WALL_MARGIN) {
        wall->y += WALL_SPEED;
    } else if (!d && u && yTop > WALL_MARGIN) {
        wall->y -= WALL_SPEED;
    }
}

void moveBall(Ball* ball, char u, char d, char l, char r) {
    if (r && !l) ball->vx = 1;
    else if (!r && l) ball->vx = -1;
    else ball->vx = 0;

    if (d && !u) ball->vy = 1;
    else if (!d && u) ball->vy = -1;
    else ball->vy = 0;

    ball->x += ball->vx;
    ball->y += ball->vy;
}
