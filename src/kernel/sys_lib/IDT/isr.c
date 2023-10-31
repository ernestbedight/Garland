#include <IDT/isr.h>


NORETURN void exception_handler(uint8_t num)
{
    print("%n%cINTERRUPT CALLED:%n%tNUMBER:%d%n%tREASON:%s%n%c",YELLOW,num-1,exception_messages[num-1],TERMINAL_FOREGROUND_COLOUR);
    __asm__ volatile ("cli; hlt");
}