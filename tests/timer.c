#include "../lib/wildio.h"

int main(void) {
    int state = 0;
    int leds;
    while(1) {
        startTimer(1000);
        leds = state ? 0xAAAA : 0x5555; // Toggle bits
        state = !state; // Toggle state
        setLeds(leds);
        waitTimer();
    }
}