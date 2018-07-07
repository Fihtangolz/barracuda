// Unified Extensible Firmware Interface
// Base on Version 2.7 Errata A August 2017
inline namespace UEFI {

}

char *vidptr = (char*)0xb8000;

void clearScreen() {
    for(unsigned int j = 0; j < 80 * 25 * 2; j+=2) { //25 lines, 80 symbols, 2 byte per symbols (first ASCII code, second attribute-byte)
        vidptr[j] = ' ';
        vidptr[j+1] = 0x02;
    }
}

void printOnScreen(const char* str) {
    for(unsigned int j = 0, i=0; str[j] != '\0'; i+=2, ++j) {
        vidptr[i] = str[j];
        vidptr[i+1] = 0x07;
    }
}

void kmain(void){
    clearScreen();
    printOnScreen("Barracuda's kernel v was start");

    return;
}