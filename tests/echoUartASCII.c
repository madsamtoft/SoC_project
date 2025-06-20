#include "../lib/wildio.h"

void char_to_hex_string(char c, char *hex_str) {
    const char hex_digits[] = "0123456789ABCDEF";
    unsigned char uc = (unsigned char)c;

    hex_str[0] = hex_digits[(uc >> 4) & 0x0F];  // High nibble
    hex_str[1] = hex_digits[uc & 0x0F];         // Low nibble
    hex_str[2] = '\0';                          // Null terminator
}


int main() {
    char c;
    char prefix[] = "0x";
    char hexString[] = "00";
    char postfix[] = "\r\n";
    while(1) {
        c = getCharUart();
        char_to_hex_string(c, hexString);

        setLeds(c);
        putCharUart(c);
        
        printToUart("  test  ");
        printToUart(prefix);
        printToUart(hexString);
        printToUart(postfix);
    }

}