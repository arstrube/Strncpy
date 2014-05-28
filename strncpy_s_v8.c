/** Custom implementation of strncpy_s().
  *
  * This code is an adaptation of the code found at:
  * https://v8.googlecode.com/svn/trunk/src/platform-win32.cc
  */

#include "strncpy_s_custom.h"
#include "assert.h"

int strncpy_s_v8(char* dest, size_t dest_size, const char* source, size_t count) {
  assert(source != NULL);
  assert(dest != NULL);
  assert(dest_size > 0);

  if (count == _TRUNCATE) {
    while (dest_size > 0 && *source != 0) {
      *(dest++) = *(source++);
      --dest_size;
    }
    if (dest_size == 0) {
      *(dest - 1) = 0;
      return STRUNCATE;
    }
  } else {
    while (dest_size > 0 && count > 0 && *source != 0) {
      *(dest++) = *(source++);
      --dest_size;
      --count;
    }
  }
  assert(dest_size > 0);
  *dest = 0;
  return 0;
}

