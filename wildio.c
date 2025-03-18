

#include "wildio.h"

int volatile * const leds = (int *)LED_BASE_ADDR;
int volatile * const switches = (int *)SWITCH_BASE_ADDR;
int volatile * const buttons = (int *)BUTTON_BASE_ADDR;

// Set/Read all values for LEDs, Switches and Buttons
int setLeds(int value) {
    if (value > 0xffff) {
        return 0;
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

// Set/Read individual values for LEDs, Switches and Buttons
int setLed(int led, int value) {
    if (led < 0 || led >= LED_COUNT) {
        return 0;
    }
    if (value < 0 || value > 1) {
        return 0;
    }
    if (value == 1) {
        *leds |= 1 << led;
    } else {
        *leds ^= 1 << led;
    }
    return *leds;
}

int readButton(int button) {
    if (button < 0 || button >= BUTTON_COUNT) {
        return 0;
    }
    return (readButtons() >> button) & 1;
}

int readSwitch(int sw) {
    if (sw < 0 || sw >= SWITCH_COUNT) {
        return 0;
    }
    return (readSwitches() >> sw) & 1;
}