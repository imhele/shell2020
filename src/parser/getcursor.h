#ifndef __HLIB_PARSER_GETCURSOR
#define __HLIB_PARSER_GETCURSOR

#include <stdio.h>
#include <stdlib.h>
#include "../utils/helpers/parseint.h"
#include "../utils/pretty/terminal.h"
#include "getch.h"

int *ParserGetCursor()
{
  char buf[11];
  int *coord = HLIB_CALLOC_N(int, 2);
  printf(HLIB_TERMINAL_CONFIG(TERMINAL_GET_CURSOR));
  assert(ParserGetChar() == '\033');
  assert(ParserGetChar() == '[');
  for (int index = 0; index < 10; index++)
    if ((buf[index] = ParserGetChar()) == ';')
      break;
  *coord = ParseInt(buf);
  for (int index = 0; index < 10; index++)
    if ((buf[index] = ParserGetChar()) == 'R')
      break;
  *(coord + 1) = ParseInt(buf);
  return coord;
}

#endif /* __HLIB_PARSER_GETCURSOR */
