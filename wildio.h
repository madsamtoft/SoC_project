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

#define LED_BASE_ADDR 0xf0010000
#define SWITCH_BASE_ADDR 0xf0020000
#define BUTTON_BASE_ADDR 0xf0030000
#define PS2_BASE_ADDR 0xf0040000

#define UART_BASE_ADDR 0xf0000000
#define UART_SEND_RECIEVE 0xf0000004



//Not yet implemented
#define VGA_BASE_ADDR 0xf0000000
#define USB_BASE_ADDR 0xf0000000
//

#define LED_COUNT 16
#define SWITCH_COUNT 16
#define BUTTON_COUNT 4

#include "wildio.c"

#endif
