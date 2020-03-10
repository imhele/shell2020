#ifndef __HLIB_PARSER_TYPING_STARTOFHEADING
#define __HLIB_PARSER_TYPING_STARTOFHEADING

#include "../../utils/pretty/terminal.h"
#include "_buffer.h"
#include "_enum.h"

PARSER_PIPELINE_STATUS ParserTypingStartOfHeading(
    struct ParserTypingBuffer **prefix, struct ParserTypingBuffer **suffix)
{
  if (*((*prefix)->cursor) == 1)
  {
    *((*prefix)->cursor) = 0;
    return PARSER_PIPELINE_STATUS_CATCH;
  }

  return PARSER_PIPELINE_STATUS_PASS;
}

#endif /* __HLIB_PARSER_TYPING_STARTOFHEADING */
