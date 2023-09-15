#ifndef MEMORY_H
#define MEMORY_H

#include <limine.h>
#include <stdint.h>

extern                  uint64_t                KERNEL_START;
extern                  uint64_t                KERNEL_END;
extern volatile struct  limine_memmap_request   memmap_req;
//extern uint64_t   KERNEL_SIZE; 
void memminit(void);


static char * mem_types[8]=
{
    "USABLE",
    "RESERVED"    ,      
    "ACPI_RECLAIMABLE",
    "ACPI_NVS",
    "BAD_MEMORY",
    "BOOTLOADER_RECLAIMABLE",
    "KERNEL_AND_MODULES",
    "FRAMEBUFFER"
};

#endif