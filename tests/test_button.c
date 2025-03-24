#include "wildio.h"

int main(void) {
    while(1) {
        for (int i = 0; i < BUTTON_COUNT; i++) {
            if (readButton(i)) {
                setLed(i, 1);
            } else {
                setLed(i, 0);
            }
        }
    }
}