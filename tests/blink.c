#include "wildio.h"

int main(void) {
    while(1) {
        for(int i = 0; i < 1000000; i++) {
            setLeds(0XAAAA);
        }
        for(int i = 0; i < 1000000; i++) {
            setLeds(0X5555);
        }
    }
    return 0;
}