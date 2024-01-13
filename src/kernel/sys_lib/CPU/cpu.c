#include "cpu.h"

void hcf() {
    asm ("cli");
    for (;;)
    {
        asm ("hlt");
    }
}

void wrmsr(uint32_t msr, uint64_t value) {
    uint32_t edx = value >> 32;
    uint32_t eax = (uint32_t)value;
    asm volatile ("wrmsr"
                  :
                  : "a" (eax), "d" (edx), "c" (msr)
                  : "memory");
}

uint64_t rdtsc(void) {
    uint32_t edx = 0;
    uint32_t eax = 0;
    asm volatile ("rdtsc"
                  : "=r" (edx), "=r" (eax) ::
                  );
    return  ((uint64_t)edx << 32) | eax;
}
