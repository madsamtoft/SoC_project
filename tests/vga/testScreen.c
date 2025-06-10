#include "../wildvga.h"

void nextColor(char* r, char* g, char* b);
void wait(volatile int delay);

int main(void) {
    char r = 3;
    char g = 0;
    char b = 0;
    char c = 0;
    while(1) {
        c = color(r, g, b);
        drawScreen(c); 
        nextColor(&r, &g, &b);
        wait(5000000);
    }
    return 0;
}

void wait(volatile int delay) {
    while (delay > 0) {
        delay--;
    }
    return;
}

void nextColor(char* r, char* g, char* b) {
    if (*r == 3 && *g == 0 && *b == 0) {
        *r = 2;
        *g = 1;
        *b = 0;
    } else if (*r == 2 && *g == 1 && *b == 0) {
        *r = 1;
        *g = 2;
        *b = 0;
    } else if (*r == 1 && *g == 2 && *b == 0) {
        *r = 0;
        *g = 3;
        *b = 0;
    } else if (*r == 0 && *g == 3 && *b == 0) {
        *r = 0;
        *g = 2;
        *b = 1;
    } else if (*r == 0 && *g == 2 && *b == 1) {
        *r = 0;
        *g = 1;
        *b = 2;
    } else if (*r == 0 && *g == 1 && *b == 2) {
        *r = 0;
        *g = 0;
        *b = 3;
    } else if (*r == 0 && *g == 0 && *b == 3) {
        *r = 1;
        *g = 0;
        *b = 2;
    } else if (*r == 1 && *g == 0 && *b == 2) {
        *r = 2;
        *g = 0;
        *b = 1;
    } else if (*r == 2 && *g == 0 && *b == 1) {
        *r = 3;
        *g = 0;
        *b = 0;
    } else {
        *r = 0;
        *g = 0;
        *b = 0;
    }
    
}
