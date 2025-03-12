#ifndef WILDIO_H
#define WILDIO_H

#define LED_BASE_ADDR 0xf0010000
#define SWITCH_BASE_ADDR 0xf0020000
#define BUTTON_BASE_ADDR 0xf0030000

//Not yet implemented
#define VGA_BASE_ADDR 0xf0000000
#define USB_BASE_ADDR 0xf0000000
//

#define LED_COUNT 16
#define SWITCH_COUNT 16
#define BUTTON_COUNT 4

#include "wildio.c"

#endif
