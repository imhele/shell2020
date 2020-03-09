#ifndef __HLIB_PARSER_CWD
#define __HLIB_PARSER_CWD

#include <string.h>
#include <unistd.h>
#include "../utils/helpers/calloc.h"

char *ParserCWD()
{
  char *cwd;
  for (int size = 0; !size || cwd[0] == '\0';)
  {
    size += 128;
    cwd = HLIB_CALLOC_N(char, size);
    getcwd(cwd, size);
  }
  return cwd;
}

#endif /* __HLIB_PARSER_CWD */
