#ifndef CORE_H
#define CORE_H

#include <limine.h>
#include <framebuffer/framebuffer.h>
#include <terminal/terminal.h>
#include <IDT/idt.h>
#include <memory/memory.h>

void print_memory_layout(void);
void rgb_line(uint64_t x, uint64_t y, uint32_t height);

#endif