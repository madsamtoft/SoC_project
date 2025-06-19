#include "../lib/wildvga.h"
#include "../lib/wildio.h"

#define BALL_SIZE 6
#define BALL_SPEED 1

#define WALL_WIDTH 5
#define WALL_HEIGHT 60
#define WALL_MARGIN 2
#define WALL_SPEED 4

#define SCREEN_OFFSET 8 // Offset for the right wall to fit on the screen

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
void respawnBall(Ball* ball, int vx, int vy);
void checkOutOfBounds(Ball* ball);
void drawWall(Wall wall, char color);
void updateWall(Wall* wall, char u, char d);
void moveBall(Ball* ball, char u, char d, char l, char r);
void printBallInfo(Ball ball);


int main() {
    Ball ball = {VGA_X_LIM/2, VGA_Y_LIM/2, BALL_SPEED, BALL_SPEED};
    Wall wallLeft = {WALL_MARGIN, WALL_MARGIN};
    Wall wallRight = {VGA_X_LIM - WALL_MARGIN - SCREEN_OFFSET, WALL_MARGIN}; //{VGA_X_LIM - WALL_MARGIN, WALL_MARGIN};

    volatile char btns = 0;
    char btnU = 0;
    char btnD = 0;
    char btnL = 0;
    char btnR = 0;
    volatile char sw = 0;


    // Initialize the screen as black
    drawScreen(BLACK);

    //DEBUG
    for(int i = 0; i < VGA_Y_LIM; i++) {
        setPixel(0, i, RED, 0); // wall Left
        setPixel(VGA_X_LIM-4, i, GREEN, 0); // wall Right
    }

    while(1) {
        startTimer(1000/15);
        btns = readButtons();
        btnU = (btns >> 0) & 0b1;
        btnD = (btns >> 2) & 0b1;
        btnL = (btns >> 3) & 0b1;
        btnR = (btns >> 1) & 0b1;
        sw = readSwitches();

        //int key = readPs2();

        switch(readSwitches() & 0b11) {
            case 0b00:
                // Move paddles with buttons
                drawBall(ball, BLACK);
                drawWall(wallLeft, BLACK);
                drawWall(wallRight, BLACK);

                updateWall(&wallLeft, btnU, btnL);
                updateWall(&wallRight, btnR, btnD);
                updateBall(&ball, wallLeft, wallRight);

                drawBall(ball, WHITE);
                drawWall(wallLeft, WHITE);
                drawWall(wallRight, WHITE);
                break;
            case 0b01:
                // Move ball with buttons
                drawBall(ball, BLACK);
                drawWall(wallLeft, BLACK);
                drawWall(wallRight, BLACK);

                moveBall(&ball, btnU, btnD, btnL, btnR);
                checkOutOfBounds(&ball);

                drawBall(ball, WHITE);
                drawWall(wallLeft, WHITE);
                drawWall(wallRight, WHITE);
                break;
            default:
                // Default case, do nothing
                break;
        }
        printBallInfo(ball);
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

    int xLeft = x;
    int xRight = x + BALL_SIZE;
    int yTop = y;
    int yBot = y + BALL_SIZE;

    int lWall_xRight = lWall.x + WALL_WIDTH;
    int lWall_yTop = lWall.y;
    int lWall_yBot = lWall.y + WALL_HEIGHT;

    int rWall_xLeft = rWall.x;
    int rWall_yTop = rWall.y;
    int rWall_yBot = rWall.y + WALL_HEIGHT;

    // Paddle collision — must come before wall collision
    /*
    if(x <= lWall_xRight && y <= lWall_yBot && y >= lWall_yTop && vx < 0) {
        vx *= -1;
    }
    else if(xRight >= rWall_xLeft && y <= rWall_yBot && y >= rWall_yTop && vx > 0) {
        vx *= -1;
    }
    */

    // Top/bottom screen bounce
    if (yTop <= 0 && vy < 0) {
        vy *= -1;
    }
    else if (yBot >= VGA_Y_LIM && vy > 0) {
        vy *= -1;
    }

    // Left or right screen edge bounce
    if (xRight >= VGA_X_LIM - SCREEN_OFFSET) { // -4 only for my shitty screen
        ball->x = VGA_X_LIM/2;
        ball->y = VGA_Y_LIM/2;
        ball->vx = -1*BALL_SPEED;
        ball->vy = vy;
        return;
    }
    else if (xLeft <= 2) { // 2 set for debugging purposes
        ball->x = VGA_X_LIM/2;
        ball->y = VGA_Y_LIM/2;
        ball->vx = 1*BALL_SPEED;
        ball->vy = vy;
        return;
    }

    ball->x = x + vx;
    ball->y = y + vy;
    ball->vy = vy;
    ball->vx = vx;

    //DEBUGGING
    for (int i = 0; i < VGA_Y_LIM; i++) {
        setPixel(lWall_xRight, i, RED, 0); // wall Right

        setPixel(x, i, BLUE, 0);        // ball Left
        setPixel(xRight, i, GREEN, 0);  // ball Right
    }
}


void respawnBall(Ball* ball, int vx, int vy) {
    ball->x = VGA_X_LIM/2;
    ball->y = VGA_Y_LIM/2;
    ball->vx = vx;
    ball->vy = vy;
}


void checkOutOfBounds(Ball* ball) {
    int x = ball->x;
    int y = ball->y;

    // Check if the ball is out of bounds
    if (x < -BALL_SIZE || x >= VGA_X_LIM+BALL_SIZE || y < 0-BALL_SIZE || y >= VGA_Y_LIM+BALL_SIZE) {
        x = VGA_X_LIM/2;
        y = VGA_Y_LIM/2;
        ball->x = x;
        ball->y = y;
    }
}

void drawWall(Wall wall, char color) {
    int x = wall.x;
    int y = wall.y;

    drawRectangle(x, y, WALL_WIDTH, WALL_HEIGHT, color, 0);
}

void updateWall(Wall* wall, char u, char d) {
    int y = wall->y;
    int yTop = y;
    int yBot = y + WALL_HEIGHT;

    /* keyboard
    if (yBot < VGA_Y_LIM - WALL_MARGIN && yTop > WALL_MARGIN) {
        switch(leftKey & 0xFF) {
            case W: y -= WALL_SPEED; break;
            case A: y += WALL_SPEED; break;
            default: break;
        }
        switch (rightKey & 0xFF) {
            case D: y -= WALL_SPEED; break;
            case S: y += WALL_SPEED; break;
            default: break;
        }
    }
    */
    
    //* buttons
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

    if ((y <= 0 && vy < 0) || (y+BALL_SIZE >= VGA_Y_LIM && vy > 0)) {
        vy *= 0;
    }

    ball->x = x + vx;
    ball->y = y + vy;
    ball->vx = vx;
    ball->vy = vy;
}

void printBallInfo(Ball ball) {
    int x = ball.x;
    char xString[] = "xxx";
    numToString(x, xString);
    
    int y = ball.y;
    char yString[] = "xxx";
    numToString(y, yString);

    printToUart(xString);
    putCharUart(',');
    printToUart(yString);
    putCharUart('\r');
}