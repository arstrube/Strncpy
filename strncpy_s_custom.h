/** Custom implementations of strncpy_s()
  */

int     strncpy_s_wine (char *dest, size_t numberOfElements, const char *src, size_t count);

errno_t strncpy_s_safe (char *dest, rsize_t dmax, const char *src, rsize_t slen);
