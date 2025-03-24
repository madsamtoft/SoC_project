#include "wildio.h"

int main(void) {
    while(1) {
        setLeds(readSwitches());
    }
    return 0;
}