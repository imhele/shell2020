#ifndef __HLIB_UTILS_PATH_CLEAN
#define __HLIB_UTILS_PATH_CLEAN

#include "../helpers/string.h"

char *PathClean(char *path)
{
  char *str;
  char *result;
  char **array = HLIB_STRSPLIT(path, '/');

  if (path[0] != '/')
    result = HLIB_CALLOC(char);
  else
    result = HLIB_CALLOC_N(char, 2), result[0] = '/';

  for (char **item = array; *item != NULL; item++)
  {
    str = *item;

    if (str[0] != '.')
      continue;

    if (str[1] == '\0')
    {
      str[0] = '\0';
      continue;
    }

    if (str[1] == '.' && str[2] == '\0')
      for (char **prev = item - 1; prev >= array; prev--)
        if ((*prev)[0] != '\0')
        {
          str[0] = '\0';
          (*prev)[0] = '\0';
          break;
        }
  }

  for (char **item = array; *item != NULL; item++)
    if ((*item)[0] != '\0')
      HLIB_STRCAT(result, *item), HLIB_STRCAT(result, "/");

  free(*array), free(array);
  return result;
}

#endif /* __HLIB_UTILS_PATH_CLEAN */
