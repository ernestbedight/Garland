#include "kernel_include.h"


/*void print_memory_layout(void)
{
    print("KERNEL START:    %h%n",&KERNEL_START);
    print("KERNEL END:      %h%n",&KERNEL_END);

    print("KERNEL SIZE:     %s%n",uint64_to_string(((uint64_t)&KERNEL_END - (uint64_t)&KERNEL_START)/1024));
    print("ENTRY COUNT:     %d%n%n",memmap_req.response->entry_count);

    for(uint64_t i = 0;i < 116;i++){print("\b");}
    print("%n");
    for(uint8_t i = 0; i < memmap_req.response->entry_count; i++)
    {
        char * text = uint64_to_string((memmap_req.response->entries[i]->length)/1024);
        print("\b\b entry base:  0x%h%x",memmap_req.response->entries[i]->base,300);
        print("\b\b entry size:  %s%x",text,600);
        print("\b\b entry type:  %s%x  \b\b%n",mem_types[memmap_req.response->entries[i]->type],900);
    }
    for(uint64_t i = 0;i < 116;i++){print("\b");}
}
*/

#define RGB_DRAW    draw_coord(x,y,rgb,framebuffer_base);            \
                    x++;                            \
                    if(x > 1919){x = 0;y++;}        \
                    if(y > 1079){y = 0;}

void rgb_line(uint64_t x, uint64_t y, uint32_t height){
    uint64_t x_offset = x;
    for(uint64_t count = 0; count < 10; count++)
    {
        uint32_t rgb;
        unsigned int i;
        for(i = 0; i <= BLUE; i++)
        {
            rgb = RED | i<<8; 
            RGB_DRAW;
        }
        while(--i > 0)
        {
            rgb = GREEN | i<<16; 
            RGB_DRAW;
        }
        for(i = 0; i <= BLUE; i++)
        {
            rgb = GREEN | i; 
            RGB_DRAW;
        }
        while(--i > 0)
        {
            rgb = BLUE | i<<8;  
            RGB_DRAW;
        }
        for(i = 0; i <= 0xFF; i++)
        {
            rgb = BLUE | i<<16; 
            RGB_DRAW;
        }
        while(--i > 0)
        {
            rgb = RED | i;
            RGB_DRAW;
        }
        y++;
        x=x_offset;
        if(y > 1079){y = 0;x = 0;}
    }
}