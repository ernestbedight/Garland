
#include <limine.h>
#include <framebuffer/framebuffer.h>
#include <terminal/terminal.h>
#include <IDT/idt.h>
#include <common.h>
#include <memory/memory.h>

__attribute__((cdecl)) void     gdt_init(void);
__attribute__((cdecl)) uint8_t  SSE_init(void);
__attribute__((cdecl)) uint8_t  FPU_init(void);


void _start(void) {

    uint64_t framebuffer_dimensions[3];

    screenInit  ();   //initialize screen's framebuffer 
    bg          (0x182673);   //set a default blue background
    //bg        (0xf4c430);   saffron yellow 
    print       ("screen initialized%n");
    dimension   (framebuffer_dimensions);
   
    print("resolution:      %dx%d %n",framebuffer_dimensions[2],framebuffer_dimensions[1]);

    gdt_init    ();//initialize the global descriptor table
    print       ("GDT initialized%n");



    idt_init    ();
    print       ("IDT initialized%n");

    
    
    if(FPU_init())  {
                    print("%cfailed to initialize the FPU:%ndo not use floating points through it%n%c",0xFF0000,0XFFFFFF);
                    }

    else            {print("FPU initialized%n");}

    if(SSE_init())  {
                    print("%cfailed to initialize the SSE%c%n",0xFF0000,0xFFFFFF);
                    }

    else            {print("SSE initialized%n");}


    print("KERNEL START:    %h%n",&KERNEL_START);
    print("KERNEL END:      %h%n",&KERNEL_END);

    print("KERNEL SIZE:     %s%n",uint64_to_string(((uint64_t)&KERNEL_END - (uint64_t)&KERNEL_START)/1024));
    print("ENTRY COUNT:     %d%n%n",memmap_req.response->entry_count);

    for(uint64_t i = 0;i < 113;i++){print("\b");}
    print("%n");
    for(uint8_t i = 0; i < memmap_req.response->entry_count; i++)
    {
        char * text = uint64_to_string((memmap_req.response->entries[i]->length)/1024);
        print("\b entry base:  0x%h%x",memmap_req.response->entries[i]->base,300);
        print("\b entry size:  %s%x",text,600);
        print("\b entry type:  %s%x\b%n",mem_types[memmap_req.response->entries[i]->type],900);
    }
    for(uint64_t i = 0;i < 113;i++){print("\b");}
    hcf();
}
