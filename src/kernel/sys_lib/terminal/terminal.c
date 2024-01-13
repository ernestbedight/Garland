//This files contains the default OS's terminal text management unit

#include <terminal/terminal.h>

uint64_t    x_counter             = 0;
uint64_t    y_counter             = 0;
uint32_t    color                 = TERMINAL_FOREGROUND_COLOUR;
va_list *   va_stubb;
uint64_t    text_buffer_position  = 0;  
uint64_t    offset                = 0;
uint8_t     offset_switch         = 0;
uint64_t    text_line_to_write    = 0;
uint32_t    text_buffer[TEXT_BUFFER_SIZE];
uint32_t    save_buffer [TEXT_BUFFER_SIZE];
letter      mask_buffer[MAX_TOTAL_CHARS_1080p];
letter      char_buffer[MAX_TOTAL_CHARS_1080p];


void _terminal_print(void);
void _terminal_print_num(void);
void _terminal_change_color(void);
void _terminal_invalid(void);
void _terminal_newline(void);
void _terminal_tab(void);
void _terminal_print_hex(void);
void _terminal_define_x(void);

#define STRNG _terminal_print
#define NUMBR _terminal_print_num
#define COLOR _terminal_change_color
#define EMPTY _terminal_invalid
#define NEWLN _terminal_newline
#define TABSP _terminal_tab
#define HEXNM _terminal_print_hex
#define DEFNX _terminal_define_x

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

#define CHECK_OFFSET                           if(offset >= MAX_VERTICAL_CHARS_1080p) offset = 0;
#define CLEAR_BUFFER_LINE(line, buffer)        for(uint64_t x_black = 0; x_black < MAX_HORIZONTAL_CHARS_1080p; x_black++){buffer[(line)*MAX_HORIZONTAL_CHARS_1080p+x_black].char_num = NULL;buffer[(line)*MAX_HORIZONTAL_CHARS_1080p+x_black].char_colour = color;}    

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
            if(glyph[cy]&mask[cx]){
                draw_coord(x+cx,y+cy,color,framebuffer_selector);
            }
            else{
                draw_coord(x+cx,y+cy,TERMINAL_BACKGROUND_COLOUR,framebuffer_selector);
            }
        }
    }
    return;
}



void copy_to_framebuffer(void)
{
    for(uint64_t fb_flush_sl = 0; fb_flush_sl <= TEXT_BUFFER_SIZE; fb_flush_sl++)
    {
        if(save_buffer[fb_flush_sl] != text_buffer[fb_flush_sl])
        {
            framebuffer_base[fb_flush_sl] = text_buffer[fb_flush_sl];
            save_buffer[fb_flush_sl] = text_buffer[fb_flush_sl];
        }
    }
}

void flush_text_buffer(void)
{
    uint64_t vertical_printing_limit = MAX_VERTICAL_CHARS_1080p;
    uint64_t offset_copy    = offset;

    for(uint64_t v_flush_sl = 0, v_buffer_flush_sl = 0; v_flush_sl < vertical_printing_limit; v_flush_sl++, v_buffer_flush_sl++)
    {
        if(v_buffer_flush_sl + offset_copy == MAX_VERTICAL_CHARS_1080p){
            v_buffer_flush_sl = 0;
            offset_copy = 0;
        }

        for(uint64_t h_flush_sl = 0; h_flush_sl < MAX_HORIZONTAL_CHARS_1080p; h_flush_sl++)
        {
            letter selected_letter      = char_buffer[( offset_copy + v_buffer_flush_sl)*MAX_HORIZONTAL_CHARS_1080p + h_flush_sl];
            letter * mask_letter_selector = &mask_buffer[h_flush_sl + v_flush_sl * MAX_HORIZONTAL_CHARS_1080p];

            if(selected_letter.char_num != mask_letter_selector->char_num || selected_letter.char_colour != mask_letter_selector->char_colour){

                color = selected_letter.char_colour;
                putchar(selected_letter.char_num,h_flush_sl * 8, v_flush_sl * 16, framebuffer_base);
                mask_letter_selector->char_num = selected_letter.char_num;
                mask_letter_selector->char_colour = selected_letter.char_colour;
                continue;
            }

        }
    }
}

//print does work as intended
void    print         (char * text,...)
{
    va_list       va;
    uint64_t      i  = 0;

    va_start(va, text );
    
    while(text[i])
    {  
        //Checking horizontal character limit to avoid overflow
        if(x_counter >= MAX_HORIZONTAL_CHARS_1080p)
        {
            y_counter++     ;
            x_counter = 0   ;
            if(offset_switch)
            {
                offset++;
                CHECK_OFFSET;
                CLEAR_BUFFER_LINE(offset,char_buffer)
            }
        }
        //Checking vertical character limit to avoid overflow
        if(y_counter >= MAX_VERTICAL_CHARS_1080p)
        {
            // offset switch is checked to ensure that the terminal doesn't start scrolling before reaching the end at lest one time
            if(!offset_switch){
                offset = 0;
                offset_switch = 1;
                y_counter = MAX_VERTICAL_CHARS_1080p - 1;
            }
            else{
                y_counter = MAX_VERTICAL_CHARS_1080p - 1;
            }
            CLEAR_BUFFER_LINE(offset,char_buffer);
        }
        
        // this is only valid as long as mouse scrolling isn't enabled so it'll be likely changed in the future
        text_line_to_write =  (offset_switch)?((offset <= 0)?MAX_VERTICAL_CHARS_1080p-1:(offset-1)):y_counter;


        if (text[i] != '%')
        {
            char_buffer[x_counter +(text_line_to_write) * MAX_HORIZONTAL_CHARS_1080p].char_num = text[i];
            char_buffer[x_counter +(text_line_to_write) * MAX_HORIZONTAL_CHARS_1080p].char_colour = color;
            i++;
            x_counter++;
            continue;        
        }
        
        va_stubb = &va;
        func_list[text[++i]-97]();
        i++;
    }
    flush_text_buffer();
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

void _terminal_print(void)
{
    char * text = va_arg(*va_stubb, void*);
    print(text);
    return;
}


void _terminal_change_color(void)
{
    color = va_arg(*va_stubb, void*);
    return;
}

void _terminal_print_num(void)
{
   
    int64_t num     = va_arg(*va_stubb, void*);
    char *  number  = uint64_to_string(num);
    print(number);
    return; 
}

void _terminal_print_hex(void)
{
    int64_t num     = va_arg(*va_stubb, void*);
    char *  number = hex_to_string(num);
    print(number);
    return; 
}

void _terminal_invalid(void)
{
    return;
}
void _terminal_newline(void)
{
    if(offset_switch){
        CLEAR_BUFFER_LINE(offset,char_buffer)
        offset    ++;
    }
    x_counter =   0;
    y_counter +=  1;
    CHECK_OFFSET;
    return;
    
}
void _terminal_tab(void)
{
    x_counter+= 3;
    return;
}


void  _terminal_define_x            (void)
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

void flag (int64_t num)
{
    print       ("FLAG ");
    print_num   (num);
    print       ("%n");
    return;
}