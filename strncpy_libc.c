/** Custom implementation of strncpy().
  *
  * This code is an from an embedded C compiler library.
  */

#include "strncpy_s_custom.h"

#define UNUSED(x) (void)(x)

int strncpy_libc(char* s1, size_t dummy, const char* s2, size_t n)
{
    char *result = s1;

	UNUSED(dummy);

    if (n == 0) return 0;
    while ((*s1++ = *s2++) && --n != 0);  // COPY STRING
    if (n > 1)
    {
        --n;
        do *s1++ = 0; while (--n);       // TERMINATION PADDING
    }
    return 0;
}

#if 0

char* strncpy_libc(char* s1, const char* s2, size_t n)
{
    char *result = s1;

    if (n == 0) return result; 
	
	while ((*s1++ = *s2++) && --n != 0);  // COPY STRING
    if (n > 1)
    {
        --n;
        do *s1++ = 0; while (--n);       // TERMINATION PADDING
    }
    return result;
}

#endif