#ifndef __HLIB_UTILS_HELPERS_FILE
#define __HLIB_UTILS_HELPERS_FILE

#include <stdio.h>
#include "calloc.h"
#include "string.h"

char *FileGetOneLine(FILE *fp)
{
  char *buf = NULL;
  char *endline = NULL;
  char *tmp = HLIB_CALLOC_N(char, 128);

  while (!feof(fp) && endline == NULL)
  {
    fgets(tmp, 128, fp);
    endline = strchr(tmp, '\n');
    if (endline != NULL)
      *endline = '\0';
    HLIB_STRCAT(buf, tmp);
  }

  free(tmp);
  return buf;
}

#endif /* __HLIB_UTILS_HELPERS_FILE */
