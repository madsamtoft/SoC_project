#include "../lib/wildio.h"

int main(void) {
    while(1) {
        if(readSwitch(0)) {
            setLed(0, 1);
        } else {
            setLed(0, 0);
        }
    }
    return 0;
}