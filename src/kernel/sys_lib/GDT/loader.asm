BITS 64

extern print

%macro PRINT_STUBB 1
    mov rdi, %1
    call print
%endmacro

section .data

success_message DB "GDT setup %n",0
gdt64:
    dq 0

.code: equ $ - gdt64
    dq (1 << 44) | (1 << 47) | (1 << 41) | (1 << 43) | (1 << 53)

.data: equ $ - gdt64
    dq (1 << 44) | (1 << 47) | (1 << 41)

.pointer:
    dw .pointer - gdt64 - 1
    dq gdt64


section .text

global gdt_init
gdt_init:
   
    lgdt [gdt64.pointer]
    push 0x08
    PRINT_STUBB success_message
    push .return
    retfq

.return:

   ret