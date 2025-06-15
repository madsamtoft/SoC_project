/* MMIO handler for MobyDeck implementation of Martin Schöeberls wildcat RV32I processor
    Original code by Martin Schöeberl: https://github.com/schoeberl/wildcat
    Modified by:
    - Dejan Joel Künnemeyer
    - Bertram Fink-Jacobsen
    - Mads Amtoft Pedersen
        Our repo: https://github.com/madsamtoft/wildcat_MobyDeck
    
    This file is part of the MobyDeck project.
    This file is licensed under the MIT License.
    See the LICENSE file for more information.
*/

#ifndef WILDIO_H
#define WILDIO_H
#include "keyboard_scancodes.h"

#define LED_BASE_ADDR    0xf0010000
#define SWITCH_BASE_ADDR 0xf0020000
#define BUTTON_BASE_ADDR 0xf0030000
#define PS2_BASE_ADDR    0xf0040000

#define TIMER_START_ADDR 0xf0050000
#define TIMER_END_ADDR   0xf0050004

#define UART_STATUS      0xf0000000
#define UART_DATA        0xf0000004

#define LED_COUNT 16
#define SWITCH_COUNT 16
#define BUTTON_COUNT 4

// Variables
volatile int * const leds = (int *)LED_BASE_ADDR;
volatile int * const switches = (int *)SWITCH_BASE_ADDR;
volatile int * const buttons = (int *)BUTTON_BASE_ADDR;
volatile char * const ps2 = (char *)PS2_BASE_ADDR;

volatile int * const timer_start = (int *)TIMER_START_ADDR;
volatile int * const timer_end = (int *)TIMER_END_ADDR;

volatile int * const uart_status = (int *)UART_STATUS;
volatile char * const uart_data = (char *)UART_DATA;

static int led_state;
static int switch_state;
static int button_state;
static char ps2_state;

static int uart_status_state;

// Functions
void wait(volatile long delay) {
    while (delay > 0) {
        delay--;
    }
    return;
}

void startTimer(int time) {
    *timer_start = time;
}

void waitTimer() {
    int count = 0;
    while(*timer_end != 1) {
        count += 1;
    }
    count = 0;
}

void timer(int time) {
    startTimer(time);
    waitTimer();
}

// Led Functions
void setLeds(int value) {
    if (value > 0xffff) {
        led_state = 0b1010010000100101;
    } else {
        led_state = value;
    }
    *leds = led_state;
}

int setLed(int led, int value) {
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
    return led_state;
}

/*
void toggleLed(int led) {
    if (led < 0 || led >= LED_COUNT) {
        return;
    }
    led_state ^= (1 << led);
    *leds = led_state;
}

void clearLeds(void) {
    led_state = 0;
    *leds = led_state;
}

int returnLeds(void) {
    int count = 0;
    int value = led_state;

    for (int i = 0; i < LED_COUNT; i++) {
        if (value & (1 << i)) {
            count++;
        }
    }
    return count;
}
*/

// Switch Functions
int readSwitches(void) {
    switch_state = *switches;
    return switch_state;
}

int readSwitch(int sw) {
    if (sw >= 0 && sw < SWITCH_COUNT) {
        switch_state = *switches;
        return (switch_state >> sw) & 0b1;
    }
    return 0;
}

// Button Functions
int readButtons(void) {
    button_state = *buttons;
    return button_state;
}

int readButton(int button) {
    if (button >= 0 && button < BUTTON_COUNT) {
        button_state = *buttons;
        return (button_state >> button) & 0b1;
    }
    return 0;
}

// PS2/UART Functions
int readPs2(void) {
    ps2_state = *ps2;
    return ps2_state;
}

int setUart(char value) {
    *uart_data = value;
    return *uart_data;
}

int uartReady(void) {
    uart_status_state = *uart_status;
    return uart_status_state;
}

#endif
