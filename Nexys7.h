// Memory address definitions of the wildcat implementation on a Nexys7 board
#include <stdint.h>

#define LED 0xf0010000
#define SWITCH 0xf0020000
#define BUTTON 0xf0030000

volatile uint32_t *led_ptr    = (volatile uint32_t *) LED;
volatile uint32_t *switch_ptr = (volatile uint32_t *) SWITCH;
volatile uint32_t *button_ptr = (volatile uint32_t *) BUTTON;