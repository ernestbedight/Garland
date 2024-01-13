#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "values/colours.h"
#include <limine.h>
#include <stdint.h>
#include <attributes/attributes.h>
#include <math/math_functions.h>
#include <terminal/terminal.h>


extern          uint32_t*               framebuffer_base;
extern struct   limine_framebuffer*     framebuffer;
extern          uint8_t                 bytesPerPixel;
extern          uint16_t                pitch;
      

#define draw_coord( x,y,colour,framebuffer_selection) framebuffer_selection[(x) + ((y) * pitch)] = colour

#define sign(x) ((x < 0) ? -1 :((x > 0) ? 1 : 0))

void dimension              (uint64_t measures[3]);
void draw                   (uint64_t tot, uint32_t colour);
void draw_rectangle         (uint64_t x, uint64_t y, uint32_t width, uint32_t height, uint32_t colour);
void screenInit             (void);
void bg                     (uint32_t colour, uint32_t * buffer);
void draw_line              ( int x1, int y1, int x2, int y2, uint32_t colour);
void _draw_coord_deprecated  (uint64_t x, uint64_t y, uint32_t colour);

#endif