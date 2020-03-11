#ifndef __HLIB_PARSER_TYPING_LEFTRIGHT
#define __HLIB_PARSER_TYPING_LEFTRIGHT

#include "../../utils/pretty/terminal.h"
#include "../../utils/structs/bool.h"
#include "_buffer.h"
#include "_enum.h"

PARSER_PIPELINE_STATUS ParserTypingLeftRight(
    struct ParserTypingBuffer *prefix,
    struct ParserTypingBuffer *suffix,
    unsigned int hold_offset,
    char quoted_flag)
{
  if (*(prefix->head + hold_offset - 1) == '\033')
  {
    unsigned int cache_len = prefix->tail - prefix->head - hold_offset;
    if (cache_len == 0)
      return PARSER_PIPELINE_STATUS_HOLD;
    if (cache_len == 1 && *(prefix->tail - 1) == '[')
      return PARSER_PIPELINE_STATUS_HOLD;
    if (cache_len == 2)
    {
      bool is_left = *(prefix->tail - 1) == 'D';
      bool is_right = *(prefix->tail - 1) == 'C';

      if (!is_left && !is_right)
        return PARSER_PIPELINE_STATUS_PASS;

      memset(prefix->tail -= 3, 0, 3 * sizeof(char));

      if (is_right && suffix->tail - suffix->head)
      {
        ParserTypingBufferPush(prefix, suffix->head, 1);
        memcpy(suffix->head, suffix->head + 1, suffix->size * sizeof(char));
        suffix->tail--;
        return PARSER_PIPELINE_STATUS_RESET;
      }

      if (is_left && prefix->tail - prefix->head)
      {
        ParserTypingBufferUnshift(suffix, prefix->tail - 1, 1);
        *(--prefix->tail) = 0;
        return PARSER_PIPELINE_STATUS_RESET;
      }

      return PARSER_PIPELINE_STATUS_CATCH;
    }
  }

  return PARSER_PIPELINE_STATUS_PASS;
}

#endif /* __HLIB_PARSER_TYPING_LEFTRIGHT */
