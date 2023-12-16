//This files contains the default OS's terminal text management unit

#include <terminal/terminal.h>

static  uint64_t  x_counter             = 0;
static  uint64_t  y_counter             = 0;
static  uint32_t  color                 = TERMINAL_FOREGROUND_COLOUR;
        va_list * va_stubb;
static  uint64_t  text_buffer_position  = 0;  
static  uint64_t  offset                = 0;
static  uint8_t   offset_switch         = 0;
static  uint64_t  text_line             = 0;
static  uint64_t  text_line_above       = 0;

#define CHECK_OFFSET            if(offset >= SCREEN_HEIGHT) offset = 0;
#define CLEAR_LINE(line)              for(uint64_t y_black = 0; y_black <= 16; y_black++){for(uint64_t x_black = 0; x_black <= SCREEN_WIDTH; x_black++){text_buffer[line*SCREEN_WIDTH+x_black+y_black*SCREEN_WIDTH] = BLACK;}}    

void  putchar (unsigned char c, uint64_t x, uint64_t y, uint32_t * framebuffer_selector)
{

    uint8_t     cx      =0,
                cy      =0;
    uint8_t     mask[8] ={128,64,32,16,8,4,2,1};
    uint8_t *   glyph   =IBM_VGA_8x16+(c*16);
 
    for(cy=0;   cy<CHAR_HEIGHT;  cy++)
    {
        for(cx=0;   cx<CHAR_WIDTH;   cx++)
        {
            if(glyph[cy]&mask[cx]){draw_coord(x+cx,y+cy,color,framebuffer_selector);}
        }
    }
    return;
}

void copy_to_framebuffer(void)
{
    bg(TERMINAL_BACKGROUND_COLOUR,framebuffer_base);
    for(uint64_t scroller = 0; scroller <= TEXT_BUFFER_SIZE/2; scroller++)
    {
        ((uint64_t *)framebuffer_base)[scroller] = ((uint64_t *)text_framebuffer_buffer)[scroller];
    }
}

void copy_text_buffer(void)
{
    bg(TERMINAL_BACKGROUND_COLOUR,text_framebuffer_buffer);
    uint64_t text_y_counter_opposite    = 0;
    uint64_t text_buffer_pixel_selector = 0;
    uint64_t offset_stubb               = (offset_switch)?offset:0;

    for(uint64_t text_y_counter = 0;text_y_counter <= SCREEN_HEIGHT-((offset_switch)?0:(8)); text_y_counter++)
    {
        
        text_buffer_pixel_selector = (offset_stubb + (text_y_counter - text_y_counter_opposite)) * SCREEN_WIDTH;
        if(text_buffer_pixel_selector >= TEXT_BUFFER_SIZE-(8*SCREEN_WIDTH))
        {
            text_y_counter_opposite = text_y_counter;
            offset_stubb = 0;
            text_buffer_pixel_selector = 0;
        }
        for(uint64_t text_x_counter = 0;text_x_counter <= SCREEN_WIDTH;text_x_counter++)
        {

            if(text_buffer[text_buffer_pixel_selector + text_x_counter] != BLACK) 
            {
                text_framebuffer_buffer[text_x_counter + text_y_counter*SCREEN_WIDTH] = text_buffer[text_buffer_pixel_selector + text_x_counter];
            }
        }
    }

}

void    print         (char * text,...)
{
    va_list       va;
    uint64_t      i  = 0;

    va_start(va, text );
    
    while(text[i])
    {  
        if(x_counter >= 1916)
        {
            CHECK_OFFSET        ;
            y_counter   +=  16  ;
            x_counter   =   0   ;
            if(offset_switch)
            {
                offset     +=  16;
                if(offset >= 1072)
                {
                    offset = 0;
                }
            CLEAR_LINE(text_line_above)
            }
            if(y_counter >= 1072)
            {

                if(!offset_switch){
                    offset = 0;
                    offset_switch = 1;
                    y_counter = 1072;
                    CLEAR_LINE(offset);
                }
                else{
                    y_counter = 1056;
                }
                CLEAR_LINE(text_line_above);
            }

        }
        text_line =  (offset_switch)?((offset <= 0)?1056:offset-16):y_counter;
        text_line_above =  (offset_switch)?((offset >= 1056)?0:offset+16):y_counter;
        if (text[i] != '%')
        {

            
            putchar (text[i++],x_counter,text_line,text_buffer);
            x_counter+=8;
            continue;        
        }
        
        va_stubb = &va;
        func_list[text[++i]-97]();
        ++i;
    }
    copy_text_buffer();
    copy_to_framebuffer();
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
    if(offset_switch){
        CLEAR_LINE(text_line_above)
        offset    +=  16;
    }
    x_counter =   0;
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

uint64_t return_x_counter(void)
{
    return x_counter;
}

uint64_t return_y_counter(void)
{
    return y_counter;
}