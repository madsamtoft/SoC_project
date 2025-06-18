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


void drawBall(Ball ball, char color);
void updateBall(Ball* ball, Wall lWall);
void drawWall(Wall wall, char color);
void updateWall(Wall* wall, char u, char d);
void moveBall(Ball* ball, char u, char d, char l, char r);


int main() {
    Ball ball = {VGA_X_LIM/2, VGA_Y_LIM/2, BALL_SPEED, BALL_SPEED};
    Ball* ballPtr = &ball;

    Wall wallLeft = {WALL_MARGIN, WALL_MARGIN};
    Wall* wallLeftPtr = &wallLeft;
    Wall wallRight = {VGA_X_LIM - 2*WALL_MARGIN - 2*WALL_WIDTH, WALL_MARGIN}; //{VGA_X_LIM - WALL_MARGIN, WALL_MARGIN};
    Wall* wallRightPtr = &wallRight;

    volatile char btns = 0;
    char btnU = 0;
    char btnD = 0;
    char btnL = 0;
    char btnR = 0;
    volatile char sw = 0;


    // Initialize the screen as black
    drawScreen(BLACK);

    //temp
    setPixel(1, 1, RED, 0);
    setPixel(VGA_X_LIM-1, VGA_Y_LIM-1, GREEN, 0);

    while(1) {
        startTimer(1000/30);
        btns = readButtons();
        btnU = (btns >> 0) & 0b1;
        btnD = (btns >> 2) & 0b1;
        btnL = (btns >> 3) & 0b1;
        btnR = (btns >> 1) & 0b1;
        sw = readSwitches();

        //int key = readPs2();
        

        drawBall(ball, BLACK);
        drawWall(wallLeft, BLACK);
        drawWall(wallRight, BLACK);

        updateBall(ballPtr, wallLeft);
        updateWall(wallLeftPtr, btnU, btnL);
        updateWall(wallRightPtr, btnR, btnD);
        
        //drawScreen(sw & 0b111111);
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
    
    // drawCircle(x, y, BALL_RADIUS, WHITE, 0);
    drawSquare(x, y, BALL_SIZE, color, 0);
}

void updateBall(Ball* ball, Wall lWall) {
    int x = ball->x;
    int y = ball->y;
    int vx = ball->vx;
    int vy = ball->vy;

    int xLeft = x;
    int xRight = x + BALL_SIZE;
    int yTop = y;
    int yBot = y + BALL_SIZE;

    int lWall_xRight = lWall.x + WALL_WIDTH;
    int lWall_yTop = lWall.y;
    int lWall_yBot = lWall.y + WALL_HEIGHT;

    // Paddle collision — must come before wall collision
    if(x <= lWall_xRight && y <= lWall_yBot && y >= lWall_yTop && vx < 0) {
        vx *= -1;
    }

    // Left or right screen edge bounce
    if (xRight >= VGA_X_LIM - 4 && vx > 0) { // -4 only for my shitty screen
        x = VGA_X_LIM/2;
        y = VGA_Y_LIM/2;
        vx = -BALL_SPEED;
    }
    else if (xLeft <= 0 && vx < 0) {
        x = VGA_X_LIM/2;
        y = VGA_Y_LIM/2;
        vx = BALL_SPEED;
    }


    // Top/bottom screen bounce
    if (yTop <= 0 && vy < 0) {
        vy *= -1;
    }
    else if (yBot >= VGA_Y_LIM && vy > 0) {
        vy *= -1;
    }

    //DEBUGGING
    for (int i = 0; i < VGA_Y_LIM; i++) {
        setPixel(lWall_xRight, i, RED, 0); // wall Right

        setPixel(x, i, BLUE, 0);        // ball Left
        setPixel(xRight, i, GREEN, 0);  // ball Right
    }

    ball->x = x + vx;
    ball->y = y + vy;
    ball->vx = vx;
    ball->vy = vy;

    // Check if the ball is out of bounds
    if (x < 0 || x >= VGA_X_LIM || y < 0 || y >= VGA_Y_LIM) {
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

    switch (r & l) {
        case 0b10: vx = 1;
        case 0b01: vx = -1;
        default: vx = 0;
    }

    switch (d & u) {
        case 0b10: vy = 1;
        case 0b01: vy = -1;
        default: vy = 0; 
    }

    ball->x = x + vx;
    ball->y = y + vy;
    ball->vx = vx;
    ball->vy = vy;
}