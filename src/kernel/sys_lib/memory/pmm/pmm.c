#include <memory/memory.h>

uint64_t calculate_memory_size(void)
{
    uint64_t size = 0;
    for(uint8_t entry_number = 0; entry_number < memmap_req.response->entry_count; entry_number++)
    {
        uint64_t entry_type = memmap_req.response->entries[entry_number]->type;
        if(entry_type != LIMINE_MEMMAP_RESERVED && entry_type != LIMINE_MEMMAP_FRAMEBUFFER)
        {
            size+= memmap_req.response->entries[entry_number]->length;
        }
    }
    return size;
}

uint64_t calculate_usable_memory(void)
{
    uint64_t size = 0;
    for(uint8_t entry_number = 0; entry_number < memmap_req.response->entry_count; entry_number++)
    {
        uint64_t entry_type = memmap_req.response->entries[entry_number]->type;
        if(USABLE_MEMORY_CONDITIONS(entry_type))
        {
            size+= memmap_req.response->entries[entry_number]->length;
        }
    }
    return size;
}


