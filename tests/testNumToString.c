#include "../lib/wildio.h"

int main() {
    int i = 0;
    char string[] = "xxx";
    while(1) {
        startTimer(1000);
        numToString(i, string);

        printToUart(string);
        putCharUart('\r');
        // putCharUart('\n');
        putCharUart(0);
        
        setLeds(i++);
        waitTimer();
    }
}