#include "wildio.h"
#include "keyboard_scancodes.h"

int volatile * const leds = (int *)LED_BASE_ADDR;
int volatile * const switches = (int *)SWITCH_BASE_ADDR;
int volatile * const buttons = (int *)BUTTON_BASE_ADDR;
int volatile * const ps2 = (int *)PS2_BASE_ADDR;

int volatile * const uart_status = (int *)UART_STATUS;
int volatile * const uart_data = (int *)UART_DATA;

int volatile * vga = (volatile int *) VGA_BASE_ADDR;

static int led_state;
static int switch_state;
static int button_state;
static int ps2_state;
static int uart_status_state;
static int vga_state[X_MAX * Y_MAX];

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
    switch_state = *switches;
    return switch_state;
}

int readButtons(void) {
    button_state = *buttons;
    return button_state;
}

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

// Set/Read individual values for LEDs, Switches and Buttons
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

void setPixel(int x, int y, int color) {
    if ((x < 0 || x >= X_MAX) || (y < 0 || y >= Y_MAX) || (color < 0 || color >= C_MAX)) {
        return;
    }
    int addr = (y << X_BIT_WIDTH) | x;
    vga[addr] = color;
}

//// READ KEYBOARD SCANCODES
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