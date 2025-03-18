#include "wildio.h"

int main(void) {
    while(1) {
        for(int i = 0; i < 10000000; i++) {
            setLed(0, 1);
            setLed(1, 0);
            setLed(2, 1);
            setLed(3, 0);
            setLed(4, 1);
            setLed(5, 0);
            setLed(6, 1);
            setLed(7, 0);
            setLed(8, 1);
            setLed(9, 0);
            setLed(10, 1);
            setLed(11, 0);
            setLed(12, 1);
            setLed(13, 0);
            setLed(14, 1);
            setLed(15, 0);
        }
        for(int i = 0; i < 10000000; i++) {
            setLed(0, 0);
            setLed(1, 1);
            setLed(2, 0);
            setLed(3, 1);
            setLed(4, 0);
            setLed(5, 1);
            setLed(6, 0);
            setLed(7, 1);
            setLed(8, 0);
            setLed(9, 1);
            setLed(10, 0);
            setLed(11, 1);
            setLed(12, 0);
            setLed(13, 1);
            setLed(14, 0);
            setLed(15, 1);
        }
    }
    return 0;
}