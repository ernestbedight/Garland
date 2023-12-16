#ifndef STRING_H
#define STRING_H


#include <stdint.h>
#include <terminal/terminal.h>
#include <memory/memory.h>


uint32_t    strlen          (const char *str);
char*       uint64_to_string( uint64_t input );
char*       hex_to_string   ( uint64_t input );
char*       placepoint      (uint64_t num, uint8_t offset);

#endif