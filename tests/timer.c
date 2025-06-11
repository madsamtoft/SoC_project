#include "wildio.h"

int main(void) {
    setLeds(0b1010101010101010);
    timer();
    setLeds(0b0101010101010101);
}