#include <stdio.h>

void drawBall4x4(int x, int y, char color) {
    const char bitmap[4][4] = {
        {0, 1, 1, 0},
        {1, 1, 1, 1},
        {1, 1, 1, 1},
        {0, 1, 1, 0}
    };

    for (int dy = 0; dy < 4; dy++) {
        for (int dx = 0; dx < 4; dx++) {
            if (bitmap[dy][dx]) {
                setPixel(x + dx, y + dy, color, 0);
            }
        }
    }
}