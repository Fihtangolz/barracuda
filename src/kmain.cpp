char *VGAtextBuff = (char*)0xb8000;

//support ansi
//ansi colors + background color
//escape symbol
//Cursor Navigation
//

void clearScreen() {
    for(unsigned int j = 0; j < 80 * 25 * 2; j+=2) { //25 lines, 80 symbols, 2 byte per symbols (first ASCII code, second attribute-byte)
        VGAtextBuff[j] = ' ';
        VGAtextBuff[j+1] = 0x02;
    }
}

void printOnScreen(const char* str) {
    for(unsigned int j = 0, i=0; str[j] != '\0'; i+=2, ++j) {
        VGAtextBuff[i] = str[j];
        VGAtextBuff[i+1] = 0x07;
    }
}

#define HARD_INLINE __attribute__((always_inline))
//TODO __inline __declspec(naked) research
//HARD_INLINE void readPort(){
//    asm
//    {
//        mov edx, [esp + 4]
//        in al, dx
//        ret
//    }
//}
//
//HARD_INLINE void writePort(){
//    asm
//    {
//        mov   edx, [esp + 4]
//        mov   al, [esp + 4 + 4]
//        out   dx, al
//        ret
//    }
//}

//memory management
//+get ram number

//Programs Execution
//https://github.com/torvalds/linux/tree/v4.3/arch/x86/entry/syscalls
namespace ELF {
    struct header{
        e_ident[16]
        e_type
        e_machine
        e_version
        e_entry
        e_phoff
        e_shoff
        e_flags
        e_ehsize
        e_phentsize
        e_phnum
        e_shentsize
        e_shnum
        e_shstrndx
    };
    struct programHeaderTable {
        p_type
        p_flags
        p_offset
        p_vaddr
        p_paddr
        p_filesz
        p_memsz
        p_flags
        p_align
    };
} //ELF END


void kmain(void){
    clearScreen();
    //sometimes better then bolgenOS
    //HollyC compiler maybe include in next version
    printOnScreen("Barracuda's kernel v was start\n");
    printOnScreen("test\n");
    return;
}