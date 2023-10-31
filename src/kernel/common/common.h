#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>
#include <terminal/terminal.h>

#define PACKED     __attribute__((packed))
#define ALIGNED_10 __attribute__((aligned(0x10)))
#define NORETURN   __attribute__((noreturn))

#define NULL ((void *)0UL)

#define assembly_print(...) print(__VA_ARGS__)  

void hcf(void);

#endif