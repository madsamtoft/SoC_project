#include "../lib/wildvga.h"
#include "../lib/wildio.h"
#include <stdint.h>

#define BALL_SIZE 6
#define BALL_SPEED 1

#define WALL_WIDTH 5
#define WALL_HEIGHT 60
#define WALL_MARGIN 2
#define WALL_SPEED 4

#define FPS 30

struct pongBall {
    int16_t x;
    int16_t y;
    int8_t vx;
    int8_t vy;
};
typedef struct pongBall Ball;

struct pongWall {
    int16_t x;
    int16_t y;
};
typedef struct pongWall Wall;


void drawBall(Ball* ball, char color);
void updateBall(Ball* ball);
void drawWall(Wall* wall, char color);
void updateWall(Wall* wall, char u, char d);
void moveBall(Ball* ball, char u, char d, char l, char r);
void printBallInfo(Ball* ball);


int main() {
    Ball ball = {VGA_X_LIM/2, VGA_Y_LIM/2, BALL_SPEED, BALL_SPEED};
    Wall wallLeft = {WALL_MARGIN, WALL_MARGIN};
    Wall wallRight = {VGA_X_LIM - WALL_WIDTH - WALL_MARGIN, WALL_MARGIN};

    volatile char btns = 0;
    char btnU = 0;
    char btnD = 0;
    char btnL = 0;
    char btnR = 0;
    volatile char sw = 0;

    drawScreen(BLACK);

    while(1) {
        startTimer(1000/FPS);
    
        // clearLine(20);
        // printBallInfo(&ball);
        
        btns = readButtons();
        btnU = (btns >> 0) & 0b1;
        btnD = (btns >> 2) & 0b1;
        btnL = (btns >> 3) & 0b1;
        btnR = (btns >> 1) & 0b1;
        sw = readSwitches();

        // Draw old positions black
        drawBall(&ball, BLACK);
        drawWall(&wallLeft, BLACK);
        drawWall(&wallRight, BLACK);

        // Update all the pieces
        updateBall(&ball);
        updateWall(&wallLeft, btnU, btnL);
        updateWall(&wallRight, btnR, btnD);
        
        // Draw the pieces white
        drawBall(&ball, WHITE);
        drawWall(&wallLeft, WHITE);
        drawWall(&wallRight, WHITE);

        waitTimer();
    }

    return 0;
}

void drawBall(Ball* ball, char color) {
    int x = ball->x;
    int y = ball->y;

    drawSquare(x, y, BALL_SIZE, color, 0);
}

void updateBall(Ball* ball) {
    int16_t x = ball->x;
    int16_t xLeft = x;
    int16_t xRight = x + BALL_SIZE;

    int16_t y = ball->y;
    int16_t yTop = y;
    int16_t yBot = y + BALL_SIZE;

    int8_t vx = ball->vx;
    int8_t vy = ball->vy;

    // int16_t lWall_xRight = lWall->x + WALL_WIDTH;
    // int16_t lWall_yTop = lWall->y;
    // int16_t lWall_yBot = lWall->y + WALL_HEIGHT;
    
    // int rWall_xLeft = rWall.x + WALL_WIDTH;
    // int rWall_yTop = rWall.y;
    // int rWall_yBot = rWall.y + WALL_HEIGHT;
    
    // if(xLeft <= lWall_xRight && yBot >= lWall_yTop && yTop <= lWall_yBot) {
    //     vx = 1;
    // }
    // if(xRight >= rWall_xLeft && yBot >= rWall_yTop && yTop <= rWall_yBot) {
    //     vx = -1;
    // }

    if(xRight >= VGA_X_LIM) {
        vx = -BALL_SPEED;
    }
    if(xLeft <= 0) {
        vx = BALL_SPEED;
    }
    
    if(yBot >= VGA_Y_LIM) {
        vy = -BALL_SPEED;
    }
    if(yTop <= 0) {
        vy = BALL_SPEED;
    }

    ball->x = x + vx;
    ball->y = y + vy;
    ball->vx = vx;
    ball->vy = vy;
}

void drawWall(Wall* wall, char color) {
    int x = wall->x;
    int y = wall->y;

    drawRectangle(x, y, WALL_WIDTH, WALL_HEIGHT, color, 0);
}

void updateWall(Wall* wall, char u, char d) {
    int y = wall->y;
    int yTop = y;
    int yBot = y + WALL_HEIGHT;

    if(d && !u && yBot < VGA_Y_LIM - WALL_MARGIN) {
        y += WALL_SPEED;
    } else if (!d && u && yTop > 0 + WALL_MARGIN) {
        y -= WALL_SPEED;
    }

    wall->y = y;
}

void printBallInfo(Ball* ball) {
    int x = ball->x;
    char xString[5] = "";
    numToString(x, xString);
    
    int y = ball->y;
    char yString[5] = "";
    numToString(y, yString);

    printToUart(xString);
    putCharUart(',');
    printToUart(yString);
    putCharUart('\r');
}