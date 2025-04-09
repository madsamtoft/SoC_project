#include "wildio.h"

int main(void) {
    while (1) {
        for (int i = 0; i < SWITCH_COUNT; i++) {
            setLed(i, readSwitch(i));
        }
        delay(100000);
    }
    return 0;
}
