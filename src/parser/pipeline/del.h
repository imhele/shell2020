#ifndef __HLIB_PARSER_TYPING_DEL
#define __HLIB_PARSER_TYPING_DEL

#include "../../utils/pretty/terminal.h"
#include "_buffer.h"
#include "_enum.h"

PARSER_PIPELINE_STATUS ParserTypingDel(
    struct ParserTypingBuffer *prefix,
    struct ParserTypingBuffer *suffix,
    unsigned int hold_offset,
    char quoted_flag)
{
  if (*(prefix->tail - 1) == 127)
  {
    *(--prefix->tail) = 0;
    unsigned int unicode_size = ParserTypingGetLastUnicodeSize(prefix);
    prefix->tail -= unicode_size;
    memset(prefix->tail, 0, unicode_size * sizeof(char));
    return PARSER_PIPELINE_STATUS_RESET;
  }

  return PARSER_PIPELINE_STATUS_PASS;
}

#endif /* __HLIB_PARSER_TYPING_DEL */
