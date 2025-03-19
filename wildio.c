#include "wildio.h"

int volatile * const leds = (int *)LED_BASE_ADDR;
int volatile * const switches = (int *)SWITCH_BASE_ADDR;
int volatile * const buttons = (int *)BUTTON_BASE_ADDR;
int volatile * const ps2 = (int *)PS2_BASE_ADDR;

int volatile * const uart = (int *)UART_BASE_ADDR;
int volatile * const uart_send_recieve = (int *)UART_SEND_RECIEVE;

static int led_state = 0;

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

int readPs2(void) {
    return *ps2;
}

int setUart(int value) {
    *uart_send_recieve = value;
    return *uart_send_recieve;
}

int uartReady(void) {
    return *uart;
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
        led_state |= 1 << led;
    } else {
        led_state &= ~(1 << led);
    }
    *leds = led_state;
    return led_state;
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