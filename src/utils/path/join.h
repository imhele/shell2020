#ifndef __HLIB_UTILS_PATH_JOIN
#define __HLIB_UTILS_PATH_JOIN

#include <stdarg.h>
#include "../helpers/string.h"
#include "../symbols.h"
#include "clean.h"

char *PathJoin(char *path, ...)
{
  va_list argv;
  char *curr = path;
  char *result = HLIB_CALLOC(char);
  for (va_start(argv, path); curr != ENDARG; curr = va_arg(argv, char *))
  {
    if (curr != path)
      HLIB_STRCAT(result, "/");
    if (curr != NULL)
      HLIB_STRCAT(result, curr);
  }
  va_end(argv);
  char *cleaned = PathClean(result);
  free(result);
  return cleaned;
}

#endif /* __HLIB_UTILS_PATH_JOIN */
