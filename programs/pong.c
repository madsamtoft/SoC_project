#include "../tests/wildvga.h"
#include "../tests/wildio.h"

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


void drawBall(Ball ball);
void updateBall(Ball* ball, Wall lWall);
void drawWall(Wall wall);
void updateWall(Wall* wall, char u, char d);
void moveBall(Ball* ball, char u, char d, char l, char r);


int main() {
    Ball ball = {10, 10, BALL_SPEED, BALL_SPEED};
    Ball* ballPtr = &ball;

    Wall wallLeft = {WALL_MARGIN, WALL_MARGIN};
    Wall* wallLeftPtr = &wallLeft;
    Wall wallRight = {VGA_X_LIM - WALL_MARGIN, WALL_MARGIN};
    Wall* wallRightPtr = &wallRight;

    volatile char btns = 0;
    char btnU = 0;
    char btnD = 0;
    char btnL = 0;
    char btnR = 0;
    volatile char sw = 0;

    while(1) {
        btns = readButtons();
        btnU = (btns >> 0) & 0b1;
        btnD = (btns >> 2) & 0b1;
        btnL = (btns >> 3) & 0b1;
        btnR = (btns >> 1) & 0b1;
        sw = readSwitches();

        updateBall(ballPtr, wallLeft);
        updateWall(wallLeftPtr, btnU, btnL);
        updateWall(wallRightPtr, btnR, btnD);
        
        drawScreen(sw & 0b111111);
        drawBall(ball);
        drawWall(wallLeft);
        drawWall(wallRight);
        
        wait(600000);
    }

    return 0;
}

void drawBall(Ball ball) {
    int x = ball.x;
    int y = ball.y;

    // drawCircle(x, y, BALL_RADIUS, WHITE, 0);
    drawSquare(x, y, BALL_SIZE, WHITE, 0);
}

void updateBall(Ball* ball, Wall lWall) {
    int x = ball->x;
    int xLeft = x;
    int xRight = x + BALL_SIZE;
    
    int y = ball->y;
    int yTop = y;
    int yBot = y + BALL_SIZE;

    int vx = ball->vx;
    int vy = ball->vy;

    int lWall_xRight = lWall.x + WALL_WIDTH;
    int lWall_yTop = lWall.y;
    int lWall_yBot = lWall.y + WALL_HEIGHT;
    
    // int rWall_xLeft = rWall.x + WALL_WIDTH;
    // int rWall_yTop = rWall.y;
    // int rWall_yBot = rWall.y + WALL_HEIGHT;


    if(xRight >= VGA_X_LIM || xLeft <= 0) {
        vx *= -1;
    }
    
    if(xLeft <= lWall_xRight && yBot >= lWall_yTop && yTop <= lWall_yBot) {
        vx = 1;
    }
    // if(xRight >= rWall_xLeft && yBot >= rWall_yTop && yTop <= rWall_yBot) {
    //     vx = -1;
    // }
    if(yBot >= VGA_Y_LIM || yTop <= 0) {
        vy *= -1;
    }

    ball->x = x + vx;
    ball->y = y + vy;
    ball->vx = vx;
    ball->vy = vy;
}

void drawWall(Wall wall) {
    int x = wall.x;
    int y = wall.y;

    drawRectangle(x, y, WALL_WIDTH, WALL_HEIGHT, WHITE, 0);
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

// Temp
void moveBall(Ball* ball, char u, char d, char l, char r) {
    int x = ball->x;
    int y = ball->y;
    int vx = ball->vx;
    int vy = ball->vy;

    if(r && !l) {
        vx = 1;
    } else if (!r && l) {
        vx = -1;
    } else {
        vx = 0;
    }
    if(d && !u) {
        vy = 1;
    } else if (!d && u) {
        vy = -1;
    } else {
        vy = 0;
    }

    ball->x = x + vx;
    ball->y = y + vy;
    ball->vx = vx;
    ball->vy = vy;
}