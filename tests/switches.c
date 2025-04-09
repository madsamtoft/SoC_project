#include "wildio.h"

int main(void) {
    int switch_index = 0;
    int switch_value = 0;
    while(1) {
        switch_value = readSwitch(switch_index);
        setLeds(switch_value);
        switch_index = (switch_index + 1) % SWITCH_COUNT;
    }
    return 0;
}