#include "wildio.h"

int main(void) {
    while(1) {
        setLed(0, readSwitch(0));
    }
    return 0;
}