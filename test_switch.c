#include "wildio.h"

int main(void) {
    while(1) {
        setLed(0, readSwitch(0));
        setLed(1, readSwitch(1));
        setLed(2, readSwitch(2));
        setLed(3, readSwitch(3));
        setLed(4, readSwitch(4));
        setLed(5, readSwitch(5));
        setLed(6, readSwitch(6));
        setLed(7, readSwitch(7));
        setLed(8, readSwitch(8));
        setLed(9, readSwitch(9));
        setLed(10, readSwitch(10));
        setLed(11, readSwitch(11));
        setLed(12, readSwitch(12));
        setLed(13, readSwitch(13));
        setLed(14, readSwitch(14));
        setLed(15, readSwitch(15));
    }
    return 0;
}