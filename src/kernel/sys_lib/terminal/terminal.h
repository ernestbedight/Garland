#ifndef TERMINAL_H
#define TERMINAL_H

#include <framebuffer/framebuffer.h>
#include "fonts/IBM_8x16_font.h"
#include <stdarg.h>
#include <strings/string_functions.h>
#include <framebuffer/framebuffer.h>

#define SCREEN_HEIGHT   1080
#define SCREEN_WIDTH    1920
#define MAX_VERTICAL_CHARS_1080p    67
#define MAX_HORIZONTAL_CHARS_1080p  239
#define MAX_TOTAL_CHARS_1080p       (MAX_HORIZONTAL_CHARS_1080p * MAX_VERTICAL_CHARS_1080p)
#define CHAR_HEIGHT                 16
#define CHAR_WIDTH                  8
#define TEXT_BUFFER_SIZE            2073600

void        copy_to_framebuffer (void);
void        putchar             (unsigned char c, uint64_t x, uint64_t y, uint32_t * framebuffer_selector);
void        copy_text_buffer    (void);
void        print               (char * text,...);
void        print_num           (int64_t num);
void        flag                (int64_t num);
void        change_color        (uint32_t colour);

uint64_t    return_x_counter    (void);
uint64_t    return_y_counter    (void);


typedef struct{
    uint16_t char_num;
    uint32_t char_colour;
}letter;

#endif