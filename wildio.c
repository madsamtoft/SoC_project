#include "wildio.h"

int volatile * const leds = (int *)LED_BASE_ADDR;
int volatile * const switches = (int *)SWITCH_BASE_ADDR;
int volatile * const buttons = (int *)BUTTON_BASE_ADDR;

int setLeds(int value) {
    if (value > 0xffff) {
        return -1;
    }
    *leds = value;
    return *leds;
}

int readSwitches(void) {
    return *switches;
}

int readButtons(void) {
    return *buttons;
}
