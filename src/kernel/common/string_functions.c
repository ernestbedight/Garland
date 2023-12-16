#include <string_functions.h>

uint32_t strlen(const char *str) {
    
	int i = 0;

	while (str[i] != (char)0)
    {
		++i;
	}
	return i;
}

char* uint64_to_string( uint64_t input )
{
   static char  text[20];   
                text[20]     ='\0';
   uint8_t      loc          =20;

   while (input)
   {
       --loc;
       text[loc] = (input%10)+'0';
       input/=10;
   }
   if (loc==20)
   {
      --loc;
       text[loc] = '0';
   }
   return &text[loc];
}

char* hex_to_string( uint64_t input )
{
   static char  text[20];
                text[20] ='\0';
   uint8_t      loc      =20;
   
   while (input)
   {
       --loc;
       text[loc] = (input%16)+((input%16 > 9)? 0x37 :'0');
       input/=16;
   }
   if (loc==20)
   {
      --loc;
       text[loc] = '0';
   }
   return &text[loc];
}

char* placepoint(uint64_t num, uint8_t offset)
{
    static char string[20];
    char * string_stubb = uint64_to_string(num);
                

    for(uint8_t i = 20; i > offset ; i--)
    {
        string[i] = string_stubb[i-1];
    }

    string[offset] = '.';

    for(uint8_t i = offset; i > 0 ; i--)
    {
        string[i-1] = string_stubb[i-1];
    }
    return &string[0];
}