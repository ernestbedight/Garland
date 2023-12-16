#This files setups the SSE (not usable in the main kernel)

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
    mov     $0x1, %eax
    cpuid
    test    $(1<<25), %rdx
    jz      .noSSE
    mov     %cr0, %rax
    and     $0xFFFB , %ax		
    or      $0x2, %ax			
    mov     %rax, %cr0
    mov     %cr4, %rax
    or      $(3 << 9), %ax
    mov     %rax, %cr4 
    mov     $0  , %rax
    ret
.noSSE:
    mov     $1, %rax
    ret
