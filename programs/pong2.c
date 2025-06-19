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

//#define DEBUG 0 //uncomment for debug mode

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
void moveBall(Ball* ball, char u, char d, char l, char r);
void respawnBall(Ball* ball, int vx, int vy);

void drawWall(Wall wall, char color);
void updateWallButtons(Wall* wall, char u, char d);

int xOutOfBounds(Ball* ball);
int yOutOfBounds(Ball* ball);
int touchPaddle(Ball ball, Wall lWall, Wall rWall);

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

    
    #ifdef DEBUG //DEBUGGING
    for(int i = 0; i < VGA_Y_LIM; i++) {
        setPixel(0, i, RED, 0); // wall Left
        setPixel(VGA_X_LIM - SCREEN_OFFSET, i, GREEN, 0); // wall Right
    }
    #endif

    while(1) {
        startTimer(1000/FPS);
        
        //Read switches for choosing modes
        sw = readSwitches();
        
        switch(readSwitches() & 0b11) {
            case 0b00: // Move paddles with buttons
                // Read Button Input
                btns = readButtons();
                btnU = (btns >> 0) & 0b1;
                btnD = (btns >> 2) & 0b1;
                btnL = (btns >> 3) & 0b1;
                btnR = (btns >> 1) & 0b1;
                
                // Overwrite last frame
                drawBall(ball, BLACK);
                drawWall(wallLeft, BLACK);
                drawWall(wallRight, BLACK);

                // Update Sprites
                updateWallButtons(&wallLeft, btnU, btnL);
                updateWallButtons(&wallRight, btnR, btnD);
                updateBall(&ball, wallLeft, wallRight);

                // Draw Updated Positions
                drawBall(ball, WHITE);
                drawWall(wallLeft, WHITE);
                drawWall(wallRight, WHITE);
                break;

            case 0b01: // Move ball with buttons
                // Overwrite last frame
                drawBall(ball, BLACK);
                drawWall(wallLeft, BLACK);
                drawWall(wallRight, BLACK);

                // Update Ball
                moveBall(&ball, btnU, btnD, btnL, btnR);

                // Print coordinates of the ball
                printBallInfo(ball);
                
                // Draw Updated Positions
                drawBall(ball, WHITE);
                drawWall(wallLeft, WHITE);
                drawWall(wallRight, WHITE);
                break;

            default:
                // Default case, do nothing
                break;
        }
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

    
    #ifdef DEBUG //DEBUGGING
    for (int i = 0; i < VGA_Y_LIM; i++) {
        setPixel(lWall.x+WALL_WIDTH, i, RED, 0); // wall Right

        setPixel(x, i, BLUE, 0);        // ball Left
        setPixel(x+BALL_SIZE, i, GREEN, 0);  // ball Right
    }
    #endif
}

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

    if (yOutOfBounds(ball)) {
        vy *= 0;
    }

    if (xOutOfBounds(ball)) {
        respawnBall(ball, vx, vy);
        return; // Do not update position if out of bounds
    }

    ball->x = x + vx;
    ball->y = y + vy;
    ball->vx = vx;
    ball->vy = vy;
}

void respawnBall(Ball* ball, int vx, int vy) {
    ball->x = VGA_X_LIM/2;
    ball->y = VGA_Y_LIM/2;
    ball->vx = vx;
    ball->vy = vy;
}

void drawWall(Wall wall, char color) {
    int x = wall.x;
    int y = wall.y;

    drawRectangle(x, y, WALL_WIDTH, WALL_HEIGHT, color, 0);
}

void updateWallButtons(Wall* wall, char u, char d) {
    int y = wall->y;
    int yTop = y;
    int yBot = y + WALL_HEIGHT;
    
    //* buttons
    if(d && !u && yBot < VGA_Y_LIM - WALL_MARGIN) {
        y += WALL_SPEED;
    } else if (!d && u && yTop > 0 + WALL_MARGIN) {
        y -= WALL_SPEED;
    }

    wall->y = y;
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