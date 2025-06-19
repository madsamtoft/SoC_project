#include "../lib/wildio.h"

int main() {
    int i = 0;
    while(1) {
        startTimer(1000);
        char buffer[] = {'i', ' ', '=', ' ', (char)i, '\r', '\n', '\0'};
        printToUart(buffer);
        setLeds(i++);
        waitTimer();
    }
}