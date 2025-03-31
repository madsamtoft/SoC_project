#include "wildio.h"

int main(void) {
    int index = 0;
    while(1) {
        for(int i = 0; i < 1000000; i++) {
            volatile int a = 0;
        }
        setLed(index, 0);
        index = (index + 1) % 16;
        setLed(index, 1);
    }
    return 0;
}