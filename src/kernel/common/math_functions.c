#include <math_functions.h>

uint64_t abs (uint64_t i)
{
    return i < 0 ? -i : i;
}

uint64_t number_of_digits(uint64_t number)
{
    uint8_t  number_of_digits = 0;
    while(number > 0){
        number_of_digits++;
        number /= 10;
    }
    return number_of_digits;
}