#include "start/kernel_include.h"

__attribute__((cdecl)) void     gdt_init(void);
__attribute__((cdecl)) uint8_t  SSE_init(void);
__attribute__((cdecl)) uint8_t  FPU_init(void);


void _start(void) {

    uint64_t framebuffer_dimensions[3];


    screenInit  ();   //initialize screen's framebuffer 
    bg          (TERMINAL_BACKGROUND_COLOUR,framebuffer_base);   //set a default blue background
    print       ("WELCOME TO GARLAND OPERATING SYSTEM!%n"); 
    dimension   (framebuffer_dimensions);
   
    print       ("resolution:      %dx%d %n",framebuffer_dimensions[2],framebuffer_dimensions[1]);

    gdt_init    ();//initialize the global descriptor table

    idt_init    ();

    if(FPU_init())  {
                    print("%cfailed to initialize the FPU:%ndo not use floating points through it%n%c",RED,TERMINAL_FOREGROUND_COLOUR);
                    }

    if(SSE_init())  {
                    print("%cfailed to initialize the SSE%c%n",RED,TERMINAL_FOREGROUND_COLOUR);
                    }

    uint64_t memory_size                    = calculate_memory_size()*100/BYTE_GIB_RATIO;
    uint64_t memory_size_digits             = number_of_digits(memory_size) - 2;
    uint64_t usable_memory_size             = calculate_usable_memory()*100/BYTE_GIB_RATIO;
    uint64_t usable_memory_size_digits      = number_of_digits(usable_memory_size) - 2;


    print("memory size:%x%sGiB%n",20,placepoint(memory_size, memory_size_digits));
    print("usable memory:%x%sGiB%n",20,placepoint(usable_memory_size, usable_memory_size_digits));

    hcf();
}
