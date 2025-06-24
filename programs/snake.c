#include "../lib/wildvga.h"
#include "../lib/wildio.h"

#define SNAKE_SIZE 8
#define INITIAL_LENGTH 5
#define MAX_SNAKE_LENGTH 100
#define FOOD_SIZE SNAKE_SIZE
#define SPEED 8  // Lower is faster

typedef enum { W, S, A, D } Direction;

typedef struct {
    int x, y;
} Point;

Point snake[MAX_SNAKE_LENGTH];
int snakeLength = INITIAL_LENGTH;
Direction dir = D;

Point food;

char running = 1;

void drawPoint(Point p, char color) {
    drawSquare(p.x, p.y, SNAKE_SIZE, color, 0);
}

void spawnFood() {
    food.x = (rand() % (VGA_X_LIM / FOOD_SIZE)) * FOOD_SIZE;
    food.y = (rand() % (VGA_Y_LIM / FOOD_SIZE)) * FOOD_SIZE;
}

int isCollision(Point p1, Point p2) {
    return p1.x == p2.x && p1.y == p2.y;
}

void moveSnake() {
    // Shift segments
    for (int i = snakeLength - 1; i > 0; i--) {
        snake[i] = snake[i - 1];
    }

    // Move head
    if (dir == W) snake[0].y -= SNAKE_SIZE;
    if (dir == S) snake[0].y += SNAKE_SIZE;
    if (dir == A) snake[0].x -= SNAKE_SIZE;
    if (dir == D) snake[0].x += SNAKE_SIZE;
}

int outOfBounds(Point p) {
    return p.x < 0 || p.x >= VGA_X_LIM || p.y < 0 || p.y >= VGA_Y_LIM;
}

int checkSelfCollision() {
    for (int i = 1; i < snakeLength; i++) {
        if (isCollision(snake[0], snake[i])) return 1;
    }
    return 0;
}

void updateDirection() {
    char key = readPs2() & 0xFF;

    switch (key) {
        case W: if (dir != S) dir = W; break;
        case S: if (dir != W) dir = S; break;
        case A: if (dir != D) dir = A; break;
        case D: if (dir != A) dir = D; break;
    }
}

int main() {
    drawScreen(BLACK);

    // Initialize snake in center
    int startX = VGA_X_LIM / 2;
    int startY = VGA_Y_LIM / 2;
    for (int i = 0; i < snakeLength; i++) {
        snake[i].x = startX - i * SNAKE_SIZE;
        snake[i].y = startY;
    }

    spawnFood();

    while (running) {
        startTimer(1000 / SPEED);

        // Clear tail
        drawPoint(snake[snakeLength - 1], BLACK);

        // Handle input
        updateDirection();

        // Move snake
        moveSnake();

        // Check collisions
        if (outOfBounds(snake[0]) || checkSelfCollision()) {
            running = 0;
            break;
        }

        // Check food
        if (isCollision(snake[0], food)) {
            if (snakeLength < MAX_SNAKE_LENGTH) {
                snake[snakeLength] = snake[snakeLength - 1]; // extend last segment
                snakeLength++;
            }
            spawnFood();
        }

        // Draw snake
        for (int i = 0; i < snakeLength; i++) {
            drawPoint(snake[i], GREEN);
        }

        // Draw food
        drawPoint(food, RED);

        waitTimer();
    }

    // Game over screen
    drawScreen(BLACK);
    printToUart("GAME OVER\r");

    return 0;
}