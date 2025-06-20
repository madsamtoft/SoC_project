#include "../lib/wildio.h"

int main(void) {
    const char buffer[] = "Hello World\n";
    while(1) {
        for (int i = 0; buffer[i] != '\0'; i++) {
            putCharUart(buffer[i]);
        }
    }
}