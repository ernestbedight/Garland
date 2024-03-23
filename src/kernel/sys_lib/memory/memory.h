#ifndef MEMORY_H
#define MEMORY_H

#include <limine.h>
#include <stdint.h>
#include <terminal/terminal.h>
#include <types/bool.h>

#define PAGE_SIZE   0x1000
#define BYTE_GIB_RATIO 1073741824

#define USABLE_MEMORY_CONDITIONS(entry_type)    entry_type != LIMINE_MEMMAP_RESERVED            &&  \
                                                entry_type != LIMINE_MEMMAP_FRAMEBUFFER         &&  \
                                                entry_type != LIMINE_MEMMAP_KERNEL_AND_MODULES  &&  \
                                                entry_type != LIMINE_MEMMAP_BAD_MEMORY

extern                  uint64_t                KERNEL_START;
extern                  uint64_t                KERNEL_END;
extern volatile struct  limine_memmap_request   memmap_req;
//extern uint64_t   KERNEL_SIZE; 

uint64_t    calculate_memory_size(void);
uint64_t    calculate_usable_memory(void);

void        initialize_allocator();
uint64_t    request_page(uint8_t order);
uint8_t     free_page(uint64_t address);




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


#define WRITE(var, val)    (*((volatile typeof(val) *)(&(var))) = (val))

#define READ(var)          (*((volatile typeof(var) *)(&(var))))


#endif