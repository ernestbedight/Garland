#include <framebuffer/framebuffer.h>


uint32_t*                    framebuffer_base;
struct limine_framebuffer*   framebuffer;
uint8_t                      bytesPerPixel;
uint16_t                     pitch;

static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};



void screenInit(void) {

    //Gets and calculates the necessary data for the graphic computation

    if (framebuffer_request.response == NULL
     || framebuffer_request.response->framebuffer_count < 1) {
        hcf();
    }

    framebuffer      = framebuffer_request.response->framebuffers[0];
    framebuffer_base = framebuffer->address;
    bytesPerPixel    = framebuffer->bpp / 32;
    pitch            = framebuffer->pitch / 4;
    for(uint64_t point_selector = 0; point_selector <= TEXT_BUFFER_SIZE; point_selector++)
    {
        text_buffer[point_selector] = BLACK;
    }
    
}

void dimension(uint64_t measures[3])
{
    //Assigns the argument the framebuffer dimensions

    measures[0]     = framebuffer->height * framebuffer->width;
    measures[1]     = framebuffer->height;
    measures[2]     = framebuffer->width;
}

void bg(uint32_t colour, uint32_t * buffer)
{
    uint64_t colour_64 = colour | ((uint64_t)colour << 32);
    //Changes the background colour to the designated one
    for(uint64_t i =0; i < 1036800; i++)
    {
                    ((uint64_t * )buffer)[i]   = colour_64;
    }
}

void draw_coord_deprecated(uint64_t x, uint64_t y, uint32_t colour) 
{  
    //Changes a pixel's colour in the designated coordinates
    //Deprecated because it has been substituted (for C language's use) by the macro version however it can still be used

    framebuffer_base[(x) + (y * pitch)] = colour;
}

void draw(uint64_t tot, uint32_t colour)
{
    framebuffer_base[tot] = colour;
}


void draw_rectangle(uint64_t x, uint64_t y, uint32_t width, uint32_t height, uint32_t colour)
{
    //Draws a full rectangle as specified in coordinates and size
    
    for (uint64_t i = 0; i < width; i++)
    {
        for (uint64_t k = 0; k < height; k++)
        {
            framebuffer_base[((x + i)) + ((y + k) * pitch)] = colour;
        }
    }
}

void draw_line( int x1, int y1, int x2, int y2, uint32_t colour)
{

    //Draws a line from A(x,y) to B(x,y) in the passed colour

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
            draw_coord(px, py, colour,framebuffer_base);
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
            draw_coord(px, py, colour,framebuffer_base);
        }
    }
}

