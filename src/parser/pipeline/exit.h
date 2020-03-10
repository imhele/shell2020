#ifndef __HLIB_PARSER_TYPING_EXIT
#define __HLIB_PARSER_TYPING_EXIT

#include "../../utils/pretty/terminal.h"
#include "_buffer.h"
#include "_enum.h"

PARSER_PIPELINE_STATUS ParserTypingExit(
    struct ParserTypingBuffer *prefix, struct ParserTypingBuffer *suffix)
{
  if (*(prefix->tail - 1) == 4)
    HLIB_TERMINAL_PRINTF_ENDL("\nexit", TERMINAL_HIGHLIGHT), exit(0);

  if (*(prefix->tail - 1) == '\n')
    return PARSER_PIPELINE_STATUS_EXIT;

  return PARSER_PIPELINE_STATUS_PASS;
}

#endif /* __HLIB_PARSER_TYPING_EXIT */
