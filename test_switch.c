#include "wildio.h"

int main(void) {
    while(1) {
        setLed(0, readSwitch(0));
        setLed(1, readSwitch(0));
        setLed(2, readSwitch(0));
        setLed(3, readSwitch(0));
        setLed(4, readSwitch(0));
        setLed(5, readSwitch(0));
        setLed(6, readSwitch(0));
        setLed(7, readSwitch(0));
        setLed(8, readSwitch(0));
        setLed(9, readSwitch(0));
        setLed(10, readSwitch(0));
        setLed(11, readSwitch(0));
        setLed(12, readSwitch(0));
        setLed(13, readSwitch(0));
        setLed(14, readSwitch(0));
        setLed(15, readSwitch(0));
    }
    return 0;
}