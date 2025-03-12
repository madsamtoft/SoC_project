#include "wildio.h"

int main(void) {
    while(1) {
        for(int i = 0; i < LED_COUNT; i++) {
            setLed(i, readSwitch(i));
        }
    }
    return 0;
}