#ifndef __HLIB_PARSER_TYPING_STARTOFHEADING
#define __HLIB_PARSER_TYPING_STARTOFHEADING

#include "../../utils/pretty/terminal.h"
#include "_buffer.h"
#include "_enum.h"

PARSER_PIPELINE_STATUS ParserTypingStartOfHeading(
    struct ParserTypingBuffer *prefix, struct ParserTypingBuffer *suffix, long hold_offset)
{
  if (*(prefix->tail - 1) == 1)
  {
    ParserTypingBufferUnshift(suffix, prefix->head, prefix->tail - prefix->head);
    memset(prefix->tail = prefix->head, 0, prefix->size * sizeof(char));
    return PARSER_PIPELINE_STATUS_RESET;
  }

  return PARSER_PIPELINE_STATUS_PASS;
}

#endif /* __HLIB_PARSER_TYPING_STARTOFHEADING */
