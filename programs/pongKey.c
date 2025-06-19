#include "../lib/wildvga.h"
#include "../lib/wildio.h"

#define BALL_SIZE 6
#define BALL_SPEED 1

#define WALL_WIDTH 5
#define WALL_HEIGHT 60
#define WALL_MARGIN 2
#define WALL_SPEED 4

#define SCREEN_OFFSET 5 // Offset for the right wall to fit on the screen
#define FPS 60

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

void drawBall(Ball ball, char color);
void updateBall(Ball* ball, Wall lWall, Wall rWall);

void drawWall(Wall wall, char color);
void updateWalls(Wall* lWall, Wall* rWall, char key);

int xOutOfBounds(Ball* ball);
int yOutOfBounds(Ball* ball);
int touchPaddle(Ball ball, Wall lWall, Wall rWall);

//void printKeyboardInfo(char key);
void printBallInfo(Ball ball);

int main() {
    int wallRightYPos = VGA_X_LIM - WALL_WIDTH - WALL_MARGIN - SCREEN_OFFSET + 1;

    Ball ball = {VGA_X_LIM/2, VGA_Y_LIM/2, BALL_SPEED, BALL_SPEED};
    Wall wallLeft = {WALL_MARGIN, WALL_MARGIN};
    Wall wallRight = {wallRightYPos, WALL_MARGIN}; //{VGA_X_LIM - WALL_MARGIN, WALL_MARGIN};

    volatile char btns = 0;
    char btnU = 0;
    char btnD = 0;
    char btnL = 0;
    char btnR = 0;
    volatile char sw = 0;
    volatile char key = '0';


    // Initialize the screen as black
    drawScreen(BLACK);

    while(1) {
        startTimer(1000/FPS);
        
        // Read Keyboard Input
        key = readPs2() & 0xFF;
        
        // Overwrite last frame
        drawBall(ball, BLACK);
        drawWall(wallLeft, BLACK);
        drawWall(wallRight, BLACK);

        // Update Sprites
        updateWalls(&wallLeft, &wallRight, key);
        updateBall(&ball, wallLeft, wallRight);

        // Print keyboard press to UART
        //printKeyboardInfo(key);
        printBallInfo(ball);

        // Draw Updated Positions
        drawBall(ball, WHITE);
        drawWall(wallLeft, WHITE);
        drawWall(wallRight, WHITE);
        
        waitTimer();
    }
    return 0;
}

void drawBall(Ball ball, char color) {
    int x = ball.x;
    int y = ball.y;
    
    drawSquare(x, y, BALL_SIZE, color, 0);
}

void updateBall(Ball* ball, Wall lWall, Wall rWall) {
    int x = ball->x;
    int y = ball->y;
    int vy = ball->vy;
    int vx = ball->vx;

    // Paddle collision — must come before wall collision
    if(touchPaddle(*ball, lWall, rWall)) {
        vx *= -1; // Reverse direction
    }

    // Top/bottom screen bounce
    if (yOutOfBounds(ball)) {
        vy *= -1;
    }

    // Left or right screen edge bounce
    if (xOutOfBounds(ball)) {
        x = VGA_X_LIM/2;
        y = VGA_Y_LIM/2;
        vx *= -1;
    }

    ball->x = x + vx;
    ball->y = y + vy;
    ball->vy = vy;
    ball->vx = vx;
}

void drawWall(Wall wall, char color) {
    int x = wall.x;
    int y = wall.y;

    drawRectangle(x, y, WALL_WIDTH, WALL_HEIGHT, color, 0);
}

void updateWalls(Wall* lWall, Wall* rWall, char key) {
    int lWall_y = lWall->y;
    int lWall_yBot = lWall_y + WALL_HEIGHT;

    int rWall_y = rWall->y;
    int rWall_yBot = rWall_y + WALL_HEIGHT;
    
    // Left Wall
    if ((lWall_y > 0 + WALL_MARGIN) && ((key & 0xFF) == W)) { 
        lWall_y -= WALL_SPEED;
    } else if ((lWall_yBot < VGA_Y_LIM - WALL_MARGIN) && ((key & 0xFF) == S)) {
        lWall_y += WALL_SPEED;
    }

    // Right Wall
    if ((rWall_y > 0 + WALL_MARGIN) && ((key & 0xFF) == I)) { 
        rWall_y -= WALL_SPEED;
    } else if ((rWall_yBot < VGA_Y_LIM - WALL_MARGIN) && ((key & 0xFF) == K)) {
        rWall_y += WALL_SPEED;
    }

    lWall->y = lWall_y;
    rWall->y = rWall_y;
}

int xOutOfBounds(Ball* ball) {
    int x = ball->x;
    int y = ball->y;

    // Check if the ball is out of x-bounds
    return (x < 0 || x >= VGA_X_LIM-BALL_SIZE-SCREEN_OFFSET) ? 1 : 0;
}

int yOutOfBounds(Ball* ball) {
    int x = ball->x;
    int y = ball->y;

    // Check if the ball is out of y-bounds
    return (y < 0 || y > VGA_Y_LIM-BALL_SIZE) ? 1 : 0;
}

int touchPaddle(Ball ball, Wall lWall, Wall rWall) {
    int xLeft = ball.x;
    int xRight = ball.x + BALL_SIZE;
    int yTop = ball.y;;
    int yBot = ball.y; + BALL_SIZE;

    int vx = ball.vx;

    // Left paddle coordinates
    int lWall_xRight = lWall.x + WALL_WIDTH;
    int lWall_xLeft = lWall.x;
    int lWall_yTop = lWall.y;
    int lWall_yBot = lWall.y + WALL_HEIGHT;

    // Right paddle coordinates
    int rWall_xRight = rWall.x + WALL_WIDTH;
    int rWall_xLeft = rWall.x;
    int rWall_yTop = rWall.y;
    int rWall_yBot = rWall.y + WALL_HEIGHT;

    // Check if the ball is touching any paddle
    if (
        (xLeft <= lWall_xRight && xRight >= lWall_xLeft) && yBot >= lWall_yTop && yTop <= lWall_yBot && vx < 0) {
        return 1; // Touching left paddle
    } else if (
        (xRight >= rWall_xLeft && xLeft <= rWall_xRight) && yBot >= rWall_yTop && yTop <= rWall_yBot && vx > 0) {
        return 1; // Touching right paddle
    }
    return 0; // Not touching any paddle
}

void printBallInfo(Ball ball) {
    int x = ball.x;
    char xString[5] = "";
    numToString(x, xString);
    
    int y = ball.y;
    char yString[5] = "";
    numToString(y, yString);

    printToUart(xString);
    putCharUart(',');
    printToUart(yString);
    putCharUart('\r');
}

/*
void printKeyboardInfo(char key) {
    char outString[2] = "";

    switch (key & 0xFF) {    // Always mask to ensure 8-bit comparison
        case W:
            outString[0] = 'W';
            break;
        case A:
            outString[0] = 'A';
            break;
        case S:
            outString[0] = 'S';
            break;
        case D:
            outString[0] = 'D';
            break;
        case I:
            outString[0] = 'I';
            break;
        case J:
            outString[0] = 'J';
            break;
        case K:
            outString[0] = 'K';
            break;
        case L:
            outString[0] = 'L';
            break;
        default:
            outString[0] = '0';
            break;
    }

    outString[1] = '\r';
    printToUart(outString);
}

*/
