#ifndef TERMINAL_H
#define TERMINAL_H

#include <framebuffer/framebuffer.h>
#include "fonts/IBM_8x16_font.h"
#include "fonts/u8g2_4x6_font.h"
#include <stdarg.h>
#include <string_functions.h>
#include <framebuffer/framebuffer.h>

#define SCREEN_HEIGHT   1080
#define SCREEN_WIDTH    1920
#define MAX_VERTICAL_CHARS_1080p    67
#define MAX_HORIZONTAL_CHARS_1080p  240
#define CHAR_HEIGHT                 16
#define CHAR_WIDTH                  8
#define TEXT_BUFFER_SIZE            2073600

void        putchar             (unsigned char c, uint64_t x, uint64_t y, uint32_t * framebuffer_selector);
void        copy_text_buffer    (void);
void        print               (char * text,...);
void        print_num           (int64_t num);
void        flag                (int64_t num);
void        change_color        (uint32_t colour);
void        print_stubb         (void);
void        print_num_stub      (void);
void        change_color_stubb  (void);
void        invalid             (void);
void        newline             (void);
void        tab                 (void);
void        print_hex_stubb     (void);
void        define_x            (void);
uint64_t    return_x_counter    (void);
uint64_t    return_y_counter    (void);

#define STRNG print_stubb
#define NUMBR print_num_stub
#define COLOR change_color_stubb
#define EMPTY invalid
#define NEWLN newline
#define TABSP tab
#define HEXNM print_hex_stubb
#define DEFNX define_x

static void (*func_list[])(void) =
{
    EMPTY,EMPTY,
    COLOR,NUMBR,
    EMPTY,EMPTY,
    EMPTY,HEXNM,
    EMPTY,EMPTY,
    EMPTY,EMPTY,
    EMPTY,NEWLN,
    EMPTY,EMPTY,
    EMPTY,EMPTY,
    STRNG,TABSP,
    EMPTY,EMPTY,
    EMPTY,DEFNX,
    EMPTY,EMPTY
};

static unsigned char text_buffer[TEXT_BUFFER_SIZE];

#endif