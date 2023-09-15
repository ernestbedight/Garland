#ifndef TERMINAL_H
#define TERMINAL_H


#include <framebuffer/framebuffer.h>
#include <terminal/IBM_font.h>
#include <stdarg.h>
#include <string_func.h>

void    change_color    (uint32_t colour);

void    putchar             (unsigned char c, uint64_t x, uint64_t y);
void    print               (char * text,...);
void    print_num           (int64_t num);
void    flag                (int64_t num);

void    print_stubb         (void);
void    print_num_stub      (void);
void    change_color_stubb  (void);
void    invalid             (void);
void    newline             (void);
void    tab                 (void);
void    print_hex_stubb     (void);
void    define_x            (void);

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

#endif