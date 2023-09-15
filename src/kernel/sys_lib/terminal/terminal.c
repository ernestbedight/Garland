#include <terminal/terminal.h>

static  int16_t   x_counter = 4;
static  uint16_t  y_counter = 4;
static  uint32_t  color     = 0xFFFFFF;
        va_list * va_stubb;

void  putchar (unsigned char c, uint64_t x, uint64_t y)
{

    uint8_t     cx      =0,
                cy      =0;
    uint8_t     mask[8] ={128,64,32,16,8,4,2,1};
    uint8_t *   glyph   =IBM_VGA_8x16+(c*16);
 
    for(cy=0;   cy<16;  cy++)
    {
        for(cx=0;   cx<8;   cx++)
        {
            if(glyph[cy]&mask[cx]) draw_coord(x+cx,y+cy,color);
        }
    }
    return;
}

void    print         (char * text,...)
{
    va_list       va;
    uint64_t      i  = 0;

    va_start(va, text );
    
    while(text[i])
    {
        if(y_counter >= 1072){y_counter = 4;bg(0x0000FF) ;}
        if(x_counter >= 1920){y_counter+=16;x_counter = 4;}

        if (text[i] != '%')
        {
            putchar (text[i++],x_counter,y_counter);
            x_counter+=8;
            continue;        
        }
        
        va_stubb = &va;
        
        func_list[text[++i]-97]();
        ++i;
        
    }

    va_end(va);
    return;
}
void    print_num     (int64_t num)
{
    char *  number;
            number = uint64_to_string(num);
    print(number);
    return; 
}


void change_color(uint32_t colour)
{
    color = colour;
    return;
}

//FUNCTION WRAPS

void    print_stubb   (void)
{
    char * text = va_arg(*va_stubb, void*);
    print(text);
    return;
}


void change_color_stubb(void)
{
    color = va_arg(*va_stubb, void*);
    return;
}

void    print_num_stub(void)
{
   
    int64_t num     = va_arg(*va_stubb, void*);
    char *  number  = uint64_to_string(num);
    print(number);
    return; 
}

void    print_hex_stubb     (void)
{
    int64_t num     = va_arg(*va_stubb, void*);
    char *  number = hex_to_string(num);
    print(number);
    return; 
}

void invalid(void)
{
    return;
}
void newline(void)
{
    x_counter =   4;
    y_counter +=  16;
    return;
    
}
void tab(void)
{
    x_counter+= 32;
    return;
}

void flag (int64_t num)
{
    print       ("FLAG ");
    print_num   (num);
    print       ("%n");
    return;
}

void    define_x            (void)
{
    x_counter   = va_arg(*va_stubb, void*);
}