/** Custom implementations of strncpy_s()
  */

#include <errno.h>

/** Wine implementation */

int     strncpy_s_wine (char *dest, size_t numberOfElements, const char *src, size_t count);

/** Safe c library implementation */

#define EOK       0 // OK
#define ESNULLP 400 // NULL pointer
#define ESZEROL 401 // zero length
#define ESLEMAX 403 // length exceeds max limit
#define ESOVRLP 404 // strings overlap
#define ESNOSPC 406 // not enough space to copy src

errno_t strncpy_s_safe (char *dest, rsize_t dmax, const char *src, rsize_t slen);

/** V8 implementation */

#define STRUNCATE 80
int     strncpy_s_v8   (char* dest, size_t dest_size, const char* source, size_t count);
