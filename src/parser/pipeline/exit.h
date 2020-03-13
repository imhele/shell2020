#ifndef __HLIB_PARSER_TYPING_EXIT
#define __HLIB_PARSER_TYPING_EXIT

#include "../../utils/pretty/terminal.h"
#include "_buffer.h"
#include "_enum.h"

PARSER_PIPELINE_STATUS ParserTypingExit(
    struct ParserTypingBuffer *prefix,
    struct ParserTypingBuffer *suffix,
    unsigned int hold_offset,
    char quoted_flag)
{
  if (*(prefix->tail - 1) == 4)
    return PARSER_PIPELINE_STATUS_EXIT;

  if (*(prefix->tail - 1) == '\r')
  {
    *(prefix->tail - 1) = 0;
    putchar('\n');
    return PARSER_PIPELINE_STATUS_ENDL;
  }

  return PARSER_PIPELINE_STATUS_PASS;
}

#endif /* __HLIB_PARSER_TYPING_EXIT */
