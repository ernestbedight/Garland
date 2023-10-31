.section .text

.extern pushall
.extern popall
.extern print

success_message:
    .asciz "%cSSE detected %c %n"
error_message:
    .asciz "%cSSE not present on the designed system %c %n"


.global SSE_init

SSE_init:
    mov $0x1, %eax
    cpuid
    test $(1<<25), %rdx
    jz .noSSE

#PRINT_STUBB success_message ,0x00FF00, 0x000000

    mov %cr0, %rax
    and $0xFFFB, %ax		
    or $0x2, %ax			
    mov %rax, %cr0
    mov %cr4, %rax
    or $(3 << 9), %ax
    mov %rax, %cr4 
    mov $0, %rax
    ret
.noSSE:
#PRINT_STUBB error_message ,0xFF0000, 0x000000
    mov $1, %rax
    ret
