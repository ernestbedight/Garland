#This files setups the FPU (not usable in the main kernel)

.include "common_assembly.S"
#include <framebuffer/values/colours.h>

/*
value_37F  0x37F
value_37E  0x37E
*/

.extern print

.section .text

value_37A:
    .long 0x37A

FPU_success_message:
    .asciz "%cFPU has been setup %c%n"
FPU_error_message:
    .asciz "%cFPU not present on the designed system %c%n"

.global FPU_init

FPU_init:

    mov     $FPU_success_message, %rdi
    mov     $GREEN , %rsi
    mov     $TERMINAL_FOREGROUND_COLOUR, %rdx
    call    print

    mov     $1, %eax
    cpuid
    test    $1, %rdx  
                
    jz .noFPU      

    FLDCW [value_37A]   

    mov  $0, %rax
    ret

    .noFPU:
        mov     $FPU_error_message, %rdi
        mov     $RED , %rsi
        mov     $TERMINAL_FOREGROUND_COLOUR , %rdx
        call    print
        mov     $1, %rax
        ret
  