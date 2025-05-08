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
#define VGA_BASE_ADDR    0xf0100000

#define UART_STATUS      0xf0000000
#define UART_DATA        0xf0000004

#define LED_COUNT 16
#define SWITCH_COUNT 16
#define BUTTON_COUNT 4

#define VGA_X_MAX 320
#define VGA_Y_MAX 240
#define VGA_C_MAX 64


// Variables
volatile int * const leds = (int *)LED_BASE_ADDR;
volatile int * const switches = (int *)SWITCH_BASE_ADDR;
volatile int * const buttons = (int *)BUTTON_BASE_ADDR;
volatile int * const ps2 = (int *)PS2_BASE_ADDR;

volatile int * const uart_status = (int *)UART_STATUS;
volatile int * const uart_data = (int *)UART_DATA;

volatile char * const vga = (volatile char *) VGA_BASE_ADDR;
volatile int * const vga_int = (int *) VGA_BASE_ADDR;

static int led_state;
static int switch_state;
static int button_state;
static int ps2_state;
static int uart_status_state;
// static int vga_state[VGA_X_MAX * VGA_Y_MAX];

// Functions
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

int setUart(int value) {
    *uart_data = value;
    return *uart_data;
}

int uartReady(void) {
    uart_status_state = *uart_status;
    return uart_status_state;
}

// VGA Functions
void setPixel(int x, int y, char c) {
    int xOffset = x & 0x1ff; 
    int yOffset = (y & 0xff) << 9;
    volatile char * addrPtr = vga + xOffset + yOffset;
    *addrPtr = c;
}

//// KEYBOARD SCANCODES (WIP)
char readKey(int val) {
    if (val <= 0x0F) {
        return '0';

    } else if (val <= 0x1F) {
        return '1';

    } else if (val <= 0x2F) {
        return '2';

    } else if (val <= 0x3F) {
        return '3';

    } else if (val <= 0x4F) {
        return '4';

    } else if (val <= 0x5F) {
        return '5';

    } else if (val <= 0x6F) {
        return '6';

    } else if (val <= 0x7F) {
        return '7';

    } else if (val <= 0x8F) {
        return '8';

    } else if (val <= 0x9F) {
        return '9';
    }
    else if (val <= 0xAF) {
        return 'A';

    } else if (val <= 0xBF) {
        return 'B';

    } else if (val <= 0xCF) {
        return 'C';

    } else if (val <= 0xDF) {
        return 'D';

    } else if (val <= 0xEF) {
        return 'E';

    } else if (val <= 0xFF) {
        return 'F';
    }
    else {
        return '?';
    }
}

/*
char readKey(int val) {
    if(val == ESC) {
        return 'x';
    } else if(val == F1) {
        return '1';
    } else if(val == F2) {
        return '2';
    } else if(val == F3) {
        return '3';
    } else if(val == F4) {
        return '4';
    } else if(val == F5) {
        return '5';
    } else if(val == F6) {
        return '6';
    } else if(val == F7) {
        return '7';
    } else if(val == F8) {
        return '8';
    } else if(val == F9) {
        return '9';
    } else if(val == F10) {
        return 'A';
    } else if(val == F11) {
        return 'B';
    } else if(val == F12) {
        return 'C';
    } else if(val == TILDE) {
        return '~';
    } else if(val == ONE) {
        return '1';
    } else if(val == TWO) {
        return '2';
    } else if(val == THREE) {
        return '3';
    } else if(val == FOUR) {
        return '4';
    } else if(val == FIVE) {
        return '5';
    } else if(val == SIX) {
        return '6';
    } else if(val == SEVEN) {
        return '7';
    } else if(val == EIGHT) {
        return '8';
    } else if(val == NINE) {
        return '9';
    } else if(val == ZERO) {
        return '0';
    } else if(val == MINUS) {
        return '-';
    } else if(val == EQUALS) {
        return '=';
    } else if(val == BACKSPACE) {
        return '<';
    } else if(val == TAB) {
        return '>';
    } else if(val == Q) {
        return 'q';
    } else if(val == W) {
        return 'w';
    } else if(val == E) {
        return 'e';
    } else if(val == R) {
        return 'r';
    } else if(val == T) {
        return 't';
    } else if(val == Y) {
        return 'y';
    } else if(val == U) {
        return 'u';
    } else if(val == I) {
        return 'i';
    } else if(val == O) {
        return 'o';
    } else if(val == P) {
        return 'p';
    } else if(val == LEFTBRACKET) {
        return '[';
    } else if(val == RIGHTBRACKET) {
        return ']';
    } else if(val == BACKSLASH) {
        return '\\';
    } else if (val == CAPSLOCK) {
        return '!';
    } else if(val == A) {
        return 'a';
    } else if(val == S) {
        return 's';
    } else if(val == D) {
        return 'd';
    } else if(val == F) {
        return 'f';
    } else if(val == G) {
        return 'g';
    } else if(val == H) {
        return 'h';
    } else if(val == J) {
        return 'j';
    } else if(val == K) {
        return 'k';
    } else if(val == L) {
        return 'l';
    } else if(val == SEMICOLON) {
        return ';';
    } else if(val == APOSTROPHE) {
        return '\'';
    } else if(val == ENTER) {
        return 'E';
    } else if(val == LEFTSHIFT) {
        return 'S';
    } else if(val == Z) {
        return 'z';
    } else if(val == X) {
        return 'x';
    } else if(val == C) {
        return 'c';
    } else if(val == V) {
        return 'v';
    } else if(val == B) {
        return 'b';
    } else if(val == N) {
        return 'n';
    } else if(val == M) {
        return 'm';
    } else if(val == COMMA) {
        return ',';
    } else if(val == PERIOD) {
        return '.';
    } else if(val == FORWARD_SLASH) {
        return '/';
    } else if(val == RIGHTSHIFT) {
        return 'R';
    } else if(val == LEFTCTRL) {
        return '^';
    } else if(val == LEFTALT) {
        return '@';
    } else if(val == SPACE) {
        return ' ';
    } else if(val == RIGHTALT) {
        return '@';
    } else if(val == RIGHTCTRL) {
        return '^'; 
    } else {
        return '?';
    }
}
*/

#endif
