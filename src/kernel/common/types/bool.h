#ifndef BOOL_H
#define BOOL_H

#if defined(__STDC__) && __STDC_VERSION__ >= 199901L
    #include <stdbool.h>
#else
    typedef enum { false, true } bool;
#endif

#endif