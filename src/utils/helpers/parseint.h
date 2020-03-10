#ifndef __HLIB_UTILS_HELPERS_PARSEINT
#define __HLIB_UTILS_HELPERS_PARSEINT

#include <ctype.h>

int ParseInt(char *str)
{
  int n = 0;
  int sign = 1;
  int index = 0;

  while (isspace(str[index]))
    index++;

  sign = str[index] == '-' ? -1 : 1;

  if (str[index] == '+' || str[index] == '-')
    index++;

  while (isdigit(str[index]))
    n = 10 * n + (str[index++] - '0');

  return sign * n;
}

#endif /* __HLIB_UTILS_HELPERS_PARSEINT */
