#include <framebuffer/framebuffer.h>


uint32_t*                    framebuffer_base;
uint32_t*                    framebuffer_buffer;
struct limine_framebuffer*   framebuffer;
uint8_t                      bytesPerPixel;
uint16_t                     pitch;



static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};

void screenInit(void) {

    if (framebuffer_request.response == NULL
     || framebuffer_request.response->framebuffer_count < 1) {
        hcf();
    }

    framebuffer      = framebuffer_request.response->framebuffers[0];
    framebuffer_base = framebuffer->address;
    bytesPerPixel    = framebuffer->bpp / 32;
    pitch            = framebuffer->pitch / 4;
    
}

void dimension(uint64_t measures[3])
{
    measures[0]     = framebuffer->height * framebuffer->width;
    measures[1]     = framebuffer->height;
    measures[2]     = framebuffer->width;
}

void bg(uint32_t colour)
{
    for(uint64_t i =0; i < framebuffer->height * framebuffer ->width; i++)
    {
        uint32_t *  fb_ptr      = framebuffer->address;
                    fb_ptr[i]   = colour;
    }
}

void draw_coord_deprecated(uint64_t x, uint64_t y, uint32_t color) 
{  
    framebuffer_base[(x) + (y * pitch)] = color;
}

void draw(uint64_t tot, uint32_t color)
{
    framebuffer_base[tot] = color;
}


void drawRectangle(uint64_t x, uint64_t y, uint32_t width, uint32_t height, uint32_t color)
{
    for (uint64_t i = 0; i < width; i++)
    {
        for (uint64_t k = 0; k < height; k++)
        {
            framebuffer_base[((x + i)) + ((y + k) * pitch)] = color;
        }
    }
}

void draw_line( int x1, int y1, int x2, int y2)
{
    int dx      = x2-x1;
    int dy      = y2-y1;
    int dxabs   = abs(dx);
    int dyabs   = abs(dy);
    int sdx     = sign(dx);
    int sdy     = sign(dy);
    int x       = 0;
    int y       = 0;
    int px      = x1;
    int py      = y1;

    if (dxabs>=dyabs) {
        for(int i=0;i<dxabs;i++){
            y+=dyabs;
            if (y>=dxabs)
            {
                y  -= dxabs;
                py += sdy;
            }
            px += sdx;
            draw_coord(px, py, 0xFFFFFF);
        }
    }
    else {
        for(int i=0;i<dyabs;i++)
        {
            x+=dxabs;
            if (x>=dyabs)
            {
                x-=dyabs;
                px+=sdx;
            }
            py+=sdy;
            draw_coord(px, py, 0xFFFFFF);
        }
    }
}