#ifndef __HLIB_PARSER_TYPING_ESC
#define __HLIB_PARSER_TYPING_ESC

#include <stdio.h>
#include "_buffer.h"
#include "_enum.h"

PARSER_PIPELINE_STATUS ParserTypingESC(
    struct ParserTypingBuffer *prefix,
    struct ParserTypingBuffer *suffix,
    unsigned int hold_offset,
    char quoted_flag)
{
  if (*(prefix->tail - 1) == '\033')
    *(prefix->tail - 1) = '^';

  return PARSER_PIPELINE_STATUS_PASS;
}

#endif /* __HLIB_PARSER_TYPING_ESC */
