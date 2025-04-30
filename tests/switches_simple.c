#define LED_BASE_ADDR    0xf0010000
#define SWITCH_BASE_ADDR 0xf0020000

int volatile * const leds = (int *)LED_BASE_ADDR;
int volatile * const switches = (int *)SWITCH_BASE_ADDR;

static int led_state;
static int switch_state;

int main(void) {
    while(1) {
        switch_state = *switches;
        led_state = switch_state;
        *leds = led_state;
    }
}