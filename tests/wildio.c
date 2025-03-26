#include "wildio.h"

int volatile * const leds = (int *)LED_BASE_ADDR;
int volatile * const switches = (int *)SWITCH_BASE_ADDR;
int volatile * const buttons = (int *)BUTTON_BASE_ADDR;
int volatile * const ps2 = (int *)PS2_BASE_ADDR;

int volatile * const uart_status = (int *)UART_STATUS;
int volatile * const uart_data = (int *)UART_DATA;

static int led_state = 0;

// Set/Read all values for LEDs, Switches and Buttons
void setLeds(int value) {
    if (value > 0xffff) {
        led_state = 0b1010010000100101;
    } else {
        led_state = value;
    }
    *leds = led_state;
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
    *uart_data = value;
    return *uart_data;
}

int uartReady(void) {
    return *uart_status;
}

// Set/Read individual values for LEDs, Switches and Buttons
void setLed(int led, int value) {
    if (led < 0 || led >= LED_COUNT) {
        led_state = 0b0101101111011010;
    } else if (value < 0 || value > 1) {
        led_state = 0b1010010000100101;
    } else if (value == 1) {
        led_state |= 1 << led;
    } else {
        led_state &= ~(1 << led);
    }
    *leds = led_state;
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