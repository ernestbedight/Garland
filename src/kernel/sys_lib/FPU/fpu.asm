extern print

%macro PRINT_STUBB 3
    mov rdi, %1
    mov rsi, %2
    mov rdx, %3
    call print
%endmacro

value_37F DW 0x37F
value_37E DW 0x37E
value_37A DW 0x37A

FPU_success_message DB "%cFPU detected %c%n",0
FPU_error_message DB "%cFPU not present on the designed system %c%n",0

global FPU_init

FPU_init:

    mov eax, 0x1
    cpuid
    test rdx, 1  
                
    jz .noFPU      

    FLDCW [value_37A]   

    PRINT_STUBB FPU_success_message, 0x7CFC00, 0xFFFFFF

    mov rax, $0
    ret

    .noFPU:
        PRINT_STUBB FPU_error_message, 0xFF0000, 0xFFFFFF
        mov rax, $1
        ret
  