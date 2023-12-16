//This file contains the exception handler, for now it's a common one but it'll be updated to specific in the future

#include <IDT/isr.h>


NORETURN void exception_handler(uint8_t num, uint64_t address)
{
    print("%n%cINTERRUPT CALLED:%n%tNUMBER:%d%n%tREASON:%s%n%tADDRESS:%h%n%c%n",YELLOW,num-1,exception_messages[num-1],address,TERMINAL_FOREGROUND_COLOUR);
    __asm__ volatile ("cli; hlt");
}