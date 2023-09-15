#include <IDT/isr.h>


NORETURN void exception_handler(uint8_t num)
{
    print("interrupt called:%c%s%n%c",0xFF0000,exception_messages[num],0xFFFFFF);
    __asm__ volatile ("cli; hlt");
}