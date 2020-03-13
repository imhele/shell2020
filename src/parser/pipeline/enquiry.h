#ifndef __HLIB_PARSER_TYPING_ENQUIRY
#define __HLIB_PARSER_TYPING_ENQUIRY

#include "../../utils/pretty/terminal.h"
#include "_buffer.h"
#include "_enum.h"

PARSER_PIPELINE_STATUS ParserTypingEnquiry(
    struct ParserTypingBuffer *prefix,
    struct ParserTypingBuffer *suffix,
    unsigned int hold_offset,
    char quoted_flag)
{
  if (*(prefix->tail - 1) == 5)
  {
    *(--prefix->tail) = 0;
    if (suffix->tail - suffix->head)
      ParserTypingBufferPush(prefix, suffix->head, suffix->tail - suffix->head);
    memset(suffix->tail = suffix->head, 0, suffix->size * sizeof(char));
    return PARSER_PIPELINE_STATUS_RESET;
  }

  return PARSER_PIPELINE_STATUS_PASS;
}

#endif /* __HLIB_PARSER_TYPING_ENQUIRY */
