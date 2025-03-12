#include "wildio.h"

int main(void) {
    while(1) {
        for(int i = 0; i < 1000000; i++) {
            setLed(0, 0);
        }
        for(int i = 0; i < 1000000; i++) {
            setLed(0, 1);
        }
    }
    return 0;
}