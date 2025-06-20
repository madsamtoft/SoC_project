int main(void) {
    volatile int waitTime = 100000;
    volatile int ledState = 0b1111111111111111;
    volatile int i = 0;
    while (1) {
        while (i < waitTime) {
            i++;
        }
        ledState = ~ledState;
        setLeds(ledState);
    }
}