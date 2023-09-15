section .text

extern pushall
extern popall
extern print

%macro PRINT_STUBB 3
    mov rdi, %1
    mov rsi, %2
    mov rdx, %3
    call print
%endmacro

success_message DB "%cSSE detected %c %n",0
error_message   DB "%cSSE not present on the designed system %c %n",0


global SSE_init

SSE_init:
    mov eax, 0x1
    cpuid
    test rdx, 1<<25
    jz .noSSE
    PRINT_STUBB success_message ,0x7CFC00, 0xFFFFFF

    mov rax, cr0
    and ax, 0xFFFB		
    or ax, 0x2			
    mov cr0, rax
    mov rax, cr4
    or ax, 3 << 9
    mov cr4, rax
    mov rax, $0
    ret
.noSSE:
    PRINT_STUBB error_message ,0xFF0000, 0xFFFFFF
    mov rax, $1
    ret
