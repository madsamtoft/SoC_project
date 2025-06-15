#include "wildio.h"

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

/*
With the code and this startTimer, the code will tage 1.1ms to run each iteration in simulation

void startTimer(int time) {
    int time_ms = time * 100; // Convert to milliseconds (approximately)
    *timer_start = time_ms;
}
*/