#ifndef __HLIB_UTILS_HELPERS_STRING
#define __HLIB_UTILS_HELPERS_STRING

#include <string.h>
#include "calloc.h"

#define HLIB_STRCAT(dest, src)                                                                \
  ({                                                                                          \
    unsigned long __STRCAT_SRC_LEN = (src) == NULL ? 0 : strlen((char *)(src));               \
    unsigned long __STRCAT_DEST_LEN = (dest) == NULL ? 0 : strlen((char *)(dest));            \
    char *__HLIB_STRCAT_DEST = HLIB_CALLOC_N(char, __STRCAT_SRC_LEN + __STRCAT_DEST_LEN + 1); \
    if (__STRCAT_DEST_LEN)                                                                    \
      strcpy(__HLIB_STRCAT_DEST, (char *)(dest)), free((char *)(dest));                       \
    if (__STRCAT_SRC_LEN)                                                                     \
      strcpy(__HLIB_STRCAT_DEST + __STRCAT_DEST_LEN, (char *)(src));                          \
    (dest) = (typeof(dest))__HLIB_STRCAT_DEST;                                                \
  })

#define HLIB_STRCAT_LEFT(dest, src)                                                           \
  ({                                                                                          \
    unsigned long __STRCAT_SRC_LEN = (src) == NULL ? 0 : strlen((char *)(src));               \
    unsigned long __STRCAT_DEST_LEN = (dest) == NULL ? 0 : strlen((char *)(dest));            \
    char *__HLIB_STRCAT_DEST = HLIB_CALLOC_N(char, __STRCAT_SRC_LEN + __STRCAT_DEST_LEN + 1); \
    if (__STRCAT_SRC_LEN)                                                                     \
      strcpy(__HLIB_STRCAT_DEST, (char *)(src));                                              \
    if (__STRCAT_DEST_LEN)                                                                    \
      strcpy(__HLIB_STRCAT_DEST + __STRCAT_SRC_LEN, (char *)(dest)), free((char *)(dest));    \
    (dest) = (typeof(dest))__HLIB_STRCAT_DEST;                                                \
  })

char *HLIB_STRREPEAT(const char *str, int n)
{
  char *result;
  if (n <= 0)
    return result;
  unsigned long len = strlen((char *)str);
  result = HLIB_CALLOC_N(char, len *n + 1);
  for (int i = 0; i < n; i++)
    strcpy(result + len * i, str);
  return result;
}

#endif /* __HLIB_UTILS_HELPERS_STRING */
