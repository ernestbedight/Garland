#ifndef ISR_H
#define ISR_H

#include <common.h>
#include <terminal/terminal.h>
NORETURN void exception_handler(uint8_t num);
char * exception_messages[32] = 
{
    "division error",
    "debug",
    "non maskable interrupt",
    "breakpoint",
    "overflow",
    "bound range exceeded",
    "invalid Opcode",
    "device not aviable",
    "double fault",
    "Coprocessor Segment Overrun",
    "invalid TSS",
    "segment not present",
    "Stack Segment fault",
    "General Protection fault",
    "Page Fault",
    "Reserved",
    "x87 floating point exception",
    "aligment check",
    "machine check",
    "SIMD floating point exception",
    "virtualization exception",
    "control protection exception",
    "Reserved",
    "Hypervisor Injection exception",
    "VMM communication exception",
    "security exception",
    "Reserved",
    "Triple Fault",
    "Fpu Error interrupt"
};

#endif

