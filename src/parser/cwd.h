#ifndef __HLIB_PARSER_CWD
#define __HLIB_PARSER_CWD

#include <string.h>
#include <unistd.h>
#include "../utils/helpers/calloc.h"

char *ParserCWD()
{
  char *cwd = HLIB_CALLOC_N(char, 128);
  getcwd(cwd, 128);
  for (int size = 256; cwd[0] == '\0'; size += 128)
  {
    free(cwd);
    cwd = HLIB_CALLOC_N(char, size);
    getcwd(cwd, size);
  }
  return cwd;
}

#endif /* __HLIB_PARSER_CWD */
