/** Custom implementation of strncpy_s().
  * Free (largely de-Microsoftified) rendering of an implementation 
  * found at http://www.winehq.org/.
  */

#include "strncpy_s_custom.h"
#include <errno.h>

int strncpy_s_wine(char *dest, size_t numberOfElements, const char *src, size_t count)
{
    size_t i, end;

    if(!count) {
        if(dest && numberOfElements)
            *dest = 0;
        return 0;
    }

    if (dest == NULL) return EINVAL;
    if (src == NULL) return EINVAL;
    if (numberOfElements == 0) return EINVAL;

    if(count!=_TRUNCATE && count<numberOfElements)
        end = count;
    else
        end = numberOfElements-1;

    for(i=0; i<end && src[i]; i++)
        dest[i] = src[i];

    if(!src[i] || end==count || _TRUNCATE) {
        dest[i] = '\0';
        return 0;
    }

//    MSVCRT_INVALID_PMT("dest[numberOfElements] is too small", EINVAL);
    dest[0] = '\0';
    return EINVAL;
}
