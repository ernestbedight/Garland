#ifndef STRING_H
#define STRING_H


#include <stdint.h>
#include <terminal/terminal.h>
#include <memory/memory.h>


uint32_t    strlen          (const char *str);
char*       ulltoa_d        ( uint64_t input );
char*       ulltoa_h        ( uint64_t input );
char*       placepoint      (uint64_t num, uint8_t offset);

#endif