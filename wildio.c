#include "wildio.h"

int volatile * const led = (int *)LED_BASE_ADDR;
int volatile * const switches = (int *)SWITCH_BASE_ADDR;
int volatile * const buttons = (int *)BUTTON_BASE_ADDR;

int setLed(int index, int value) {
    if (index < 0 || index > LED_COUNT) {
        return -1;
    }
    *led = ((value & 1) << index) | (*led & ~(1 << index));
    return *led;
}

int readSwitch(int index) {
    if (index < 0 || index > SWITCH_COUNT) {
        return -1;
    }
    return (*switches >> index) & 1;
}

int readButton(int index) {
    if (index < 0 || index > BUTTON_COUNT) {
        return -1;
    }
    return (*buttons >> index) & 1;
}

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
