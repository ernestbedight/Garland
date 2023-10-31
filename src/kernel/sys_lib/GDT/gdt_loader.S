#include <framebuffer/values/colours.h>

.extern print

.section .data

success_message:
    .asciz "%cGDT has been setup %c%n"
gdt64:
    .quad 0

code:
    .quad (1 << 44) | (1 << 47) | (1 << 41) | (1 << 43) | (1 << 53)

data:
    .quad (1 << 44) | (1 << 47) | (1 << 41)

pointer:
    .word pointer - gdt64 - 1
    .quad gdt64


.section .text

.global gdt_init

gdt_init:
    lgdt    [pointer]
    mov     $success_message, %rdi
    mov     $GREEN , %rsi
    mov     $TERMINAL_FOREGROUND_COLOUR , %rdx
    call    print
    ret
