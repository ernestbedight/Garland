#ifndef CPU_H
#define CPU_H

#include <stdint.h>

void        hcf     (void);
void        _wrmsr  (uint32_t msr, uint64_t value);
uint64_t    rdtsc   (void);

#endif