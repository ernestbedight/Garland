//This files contains the default OS's terminal text management unit

#include <terminal/terminal.h>

static  uint64_t  x_counter = 0;
static  uint64_t  y_counter = 0;
static  uint32_t  color     = TERMINAL_FOREGROUND_COLOUR;
        va_list * va_stubb;
static  uint64_t  text_buffer_position = 0;  
static  uint64_t  offset = 0;

static uint8_t offset_switch = 0;
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

void copy_text_buffer(void)
{
    uint64_t vertical_counter_backup = 0;
    uint64_t offset_backup = offset;
    for(uint64_t vertical_counter = 0 ; vertical_counter <= SCREEN_HEIGHT ; vertical_counter++)
    {
        if(offset + vertical_counter - vertical_counter_backup >= SCREEN_HEIGHT)
        {
                offset_backup = 0;
                vertical_counter_backup = vertical_counter;
        }
        for(uint64_t horizontal_counter = 0; horizontal_counter <= SCREEN_WIDTH; horizontal_counter++)
        {
            if(text_buffer[horizontal_counter + (vertical_counter-vertical_counter_backup+offset)*SCREEN_WIDTH] != BLACK){
            framebuffer_base[horizontal_counter + vertical_counter * SCREEN_WIDTH] = text_buffer[horizontal_counter + (vertical_counter-vertical_counter_backup+offset)*SCREEN_WIDTH];
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
        
        if(x_counter >= SCREEN_WIDTH)
        {
            x_counter = 1;
            y_counter+= 16;
            if(offset_switch) offset+=16;
            if(offset >= SCREEN_HEIGHT)
            {
                offset = 0;
            }
            copy_text_buffer();
            for(uint64_t horizontal_counter = 0; horizontal_counter <= SCREEN_WIDTH; horizontal_counter++)
            {
                text_buffer[horizontal_counter + ((offset_switch)?offset : y_counter)*SCREEN_WIDTH] = RED;
            }

            
        }
        if(y_counter >= SCREEN_HEIGHT)
        {
            offset_switch = 1;
            offset+=16;
            if(offset >= SCREEN_HEIGHT){offset = 0;}
            x_counter = 0;
            copy_text_buffer();
            y_counter = SCREEN_HEIGHT - 16;
            
        }

        if (text[i] != '%')
        {

            putchar( text[i++],x_counter,(offset_switch)?offset:y_counter,framebuffer_base);
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
    print   (number);
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
    x_counter =     0;
    y_counter +=    16;
    for(uint64_t horizontal_counter = 0; horizontal_counter <= MAX_HORIZONTAL_CHARS_1080p; horizontal_counter++)
    {
        text_buffer[horizontal_counter + ((offset_switch)?offset : y_counter)*MAX_HORIZONTAL_CHARS_1080p] = NULL;
    }
    offset += 16;

    return;
    
}
void tab(void)
{
    x_counter+= 2;
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