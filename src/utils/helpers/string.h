#ifndef __HLIB_UTILS_HELPERS_STRING
#define __HLIB_UTILS_HELPERS_STRING

#include <string.h>
#include "calloc.h"

#define HLIB_STRCAT(dest, src)                                                        \
  ({                                                                                  \
    unsigned long __HLIB_STRCAT_LEN = ((dest) == NULL ? 0 : strlen((char *)(dest))) + \
                                      ((src) == NULL ? 0 : strlen((char *)(src)));    \
    char *__HLIB_STRCAT_DEST = HLIB_CALLOC_N(char, __HLIB_STRCAT_LEN);                \
    if ((dest) != NULL)                                                               \
      strcpy(__HLIB_STRCAT_DEST, (char *)(dest)), free((char *)(dest));               \
    if ((src) != NULL)                                                                \
      strcat(__HLIB_STRCAT_DEST, (char *)(src));                                      \
    (dest) = (typeof(dest))__HLIB_STRCAT_DEST;                                        \
  })

char *HLIB_STRREPEAT(const char *str, int n)
{
  char *result;
  if (n <= 0)
    return result;
  result = HLIB_CALLOC_N(char, strlen((char *)str) * (n));
  while (n--)
    strcat(result, str);
  return result;
}

#endif /* __HLIB_UTILS_HELPERS_STRING */
