#define LED_BASE_ADDR    0xf0010000
#define SWITCH_BASE_ADDR 0xf0020000

int volatile * const leds = (int *)LED_BASE_ADDR;
int volatile * const switches = (int *)SWITCH_BASE_ADDR;

static int led_state;
static int switch_state;

int getSwitch(int switch_num) {
    switch_state = *switches;
    return (switch_state >> switch_num) & 0x1;
}

void setLed(int led, int state) {
    if (state) {
        led_state |= (1 << led);
    } else {
        led_state &= ~(1 << led);
    }
    *leds = led_state;
}

int main(void) {
    while(1) {
        for(int i = 0; i < 16; i++) {
            if (getSwitch(i)) {
                setLed(i, 1);
            } else {
                setLed(i, 0);
            }
        }
    }
}