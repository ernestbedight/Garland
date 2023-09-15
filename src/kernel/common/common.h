#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>

#define PACKED     __attribute__((packed))
#define ALIGNED_10 __attribute__((aligned(0x10)))
#define NORETURN   __attribute__((noreturn))

#define NULL ((void *)0UL)

void hcf(void);

#endif