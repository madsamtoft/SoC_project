#include "wildio.h"

int volatile * const led = (int *)LED_BASE_ADDR;
int volatile * const switches = (int *)SWITCH_BASE_ADDR;
int volatile * const buttons = (int *)BUTTON_BASE_ADDR;

int setLeds(int value) {
    if (value > 0xffff) {
        return -1;
    }
    *led = value;
    return *led;
}

int readSwitches(void) {
    return *switches;
}

int readButtons(void) {
    return *buttons;
}
