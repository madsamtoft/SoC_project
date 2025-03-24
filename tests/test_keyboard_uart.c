
#include "wildio.h"

int main(void) {
    while(1) {
        if(readPs2() == W) {
            setLed(0, 1);
        } else {
            setLed(0, 0);
        }
    }
    return 0;
}