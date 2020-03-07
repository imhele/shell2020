#ifndef __HLIB_UTILS_HELPERS_STRING
#define __HLIB_UTILS_HELPERS_STRING

#include <string.h>
#include "calloc.h"

#define HLIB_STRCAT(dest, src)                                                                  \
  ({                                                                                            \
    char *__HLIB_STRCAT_DEST = HLIB_CALLOC_N(char, strlen((char *)dest) + strlen((char *)src)); \
    strcpy(__HLIB_STRCAT_DEST, (char *)dest);                                                   \
    if (dest != NULL && ((char *)dest)[0] != '\0')                                              \
      free((char *)dest);                                                                       \
    dest = (typeof(dest))strcat(__HLIB_STRCAT_DEST, (char *)src);                               \
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
