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

#define TIMER_TARGET_ADDR 0xf0050000
#define TIMER_DONE_ADDR   0xf0050004

#define UART_STATUS      0xf0000000
#define UART_DATA        0xf0000004

#define LED_COUNT 16
#define SWITCH_COUNT 16
#define BUTTON_COUNT 4

#define BTN_UP    0b0001
#define BTN_RIGHT 0b0010
#define BTN_DOWN  0b0100
#define BTN_LEFT  0b1000

// Variables
volatile int * const leds = (int *)LED_BASE_ADDR;
volatile int * const switches = (int *)SWITCH_BASE_ADDR;
volatile int * const buttons = (int *)BUTTON_BASE_ADDR;
volatile char * const ps2 = (char *)PS2_BASE_ADDR;

volatile int * const timer_target = (int *)TIMER_TARGET_ADDR;
volatile int * const timer_done = (int *)TIMER_DONE_ADDR;

volatile int * const uart_status = (int *)UART_STATUS;
volatile int * const uart_data = (int *)UART_DATA;

static int led_state;
static int switch_state;
static int button_state;
static char ps2_state;

static int uart_status_state;

// Functions
void wait(volatile int delay) {
    while (delay > 0) {
        delay--;
    }
    return;
}

// Hardware timer/wait function
void startTimer(int ms) {
    *timer_target = ms;
}

void waitTimer() {
    volatile int count = 0;
    while(*timer_done != 1) {
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

int readButton(int btn) {
    button_state = *buttons;
    return button_state & btn;
}

// PS2/UART Functions
int readPs2(void) {
    ps2_state = *ps2;
    return ps2_state;
}

void putCharUart(int value) {
    // Wait for the UART tx bit to show that transmitting is ready,
    // and then put the data onto it
    //
    // value - the 8 bit character to put
    unsigned char tx_ready;
    do {
        tx_ready = *uart_status & 0b01;
    } while (!tx_ready);
    *uart_data = value;
}

int getCharUart() {
    // Wait for the UART rx bit to show that recieving is ready,
    // and then return the data
    unsigned char rx_ready;
    do {
        rx_ready = *uart_status & 0b10;
    } while (!rx_ready);
    return *uart_data;
}

void clearLine(int lim) {
    for(unsigned int i = 0; i < lim; i++) {
        putCharUart(' ');
    }
    putCharUart('\r');
}

char digitToChar(unsigned char digit) {
    if (digit > 9) {
        return 'x';
    }
    return '0' + digit;
}

void numToString(int num, char* string) {
    // Convert any number in the range 0-999 to a string
    //
    // num - The number to convert
    // string - pointer to the string's base address
    // int i = num < 0;
    // string[0] = '-';
    if (num > 999) {
        string[0] = '+';
        string[1] = '+';
        string[2] = '+';
    } else if (num < 0) {
        string[0] = '-';
        string[1] = '-';
        string[2] = '-';
    } else {
        string[0] = digitToChar((num/100) % 10);    // Hundreds
        string[1] = digitToChar((num/10) % 10);     // Tens
        string[2] = digitToChar(num % 10);          // Ones
    }
    string[3] = '\0';
}

// void putCharOnceUart(int value) {
//     // Put the given value on the UART output,
//     // and then set it to 0 as soon as possible
//     putCharUart(value);
//     putCharUart(0);
// }

void printToUart(char string[]) {
    // Print the given string to the UART output
    // WARNING: Strings are problematic with the current memory loading technique
    //
    // string - the char array to be printed
    for(int i = 0; string[i] != '\0'; i++) {
        putCharUart(string[i]);
    }
}

#endif
