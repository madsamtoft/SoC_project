#include "../lib/wildio.h"

int main() {
    unsigned char c;
    while(1) {
        c = getCharUart();
        putCharUart(c);
        setLeds(c);
    }
}