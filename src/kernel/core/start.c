#include "start_action/global_include.h"

__attribute__((cdecl)) void     gdt_init(void);
__attribute__((cdecl)) uint8_t  SSE_init(void);
__attribute__((cdecl)) uint8_t  FPU_init(void);


void _start(void) {

    uint64_t framebuffer_dimensions[3];


    screenInit  ();   //initialize screen's framebuffer 
    bg          (TERMINAL_BACKGROUND_COLOUR,framebuffer_base);   //set a default blue background

    //bg        (0xf4c430);   saffron yellow
    print       ("WELCOME TO UDMOS - Untethered Data Manager Operating System%n"); 
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


    rgb_line(10,return_y_counter()+50,50);

    uint64_t memory_size                    = calculate_memory_size()*100/BYTE_GIB_RATIO;
    uint64_t memory_size_digits             = number_of_digits(memory_size) - 2;
    uint64_t usable_memory_size             = calculate_usable_memory()*100/BYTE_GIB_RATIO;
    uint64_t usable_memory_size_digits      = number_of_digits(usable_memory_size) - 2;


    print("memory size:%x%sGiB%n",200,placepoint(memory_size, memory_size_digits));
    print("usable memory:%x%sGiB%n",200,placepoint(usable_memory_size, usable_memory_size_digits));
    for(int i = 0; i<700; i++){
    print("A B C D E F G H I J K L M N O P Q R S T U V W X Y Z a b c d e f %cg%c h i j k l m n o p q r s t u v w x y z ",RED,TERMINAL_FOREGROUND_COLOUR);
    }
    uint32_t a = 4/0;
    hcf();
}
