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
        unsigned int unicode_size = ParserTypingGetFirstUnicodeSize(suffix);
        unsigned int suffix_move_size = suffix->tail - suffix->head - unicode_size;

        suffix->tail -= unicode_size;
        ParserTypingBufferPush(prefix, suffix->head, unicode_size);
        memcpy(suffix->head, suffix->head + unicode_size, suffix_move_size * sizeof(char));
        memset(suffix->head + suffix_move_size, 0, unicode_size * sizeof(char));
        return PARSER_PIPELINE_STATUS_RESET;
      }

      if (is_left && prefix->tail - prefix->head)
      {
        unsigned int unicode_size = ParserTypingGetLastUnicodeSize(prefix);
        prefix->tail -= unicode_size;
        ParserTypingBufferUnshift(suffix, prefix->tail, unicode_size);
        memset(prefix->tail, 0, unicode_size * sizeof(char));
        return PARSER_PIPELINE_STATUS_RESET;
      }

      return PARSER_PIPELINE_STATUS_CATCH;
    }
  }

  return PARSER_PIPELINE_STATUS_PASS;
}

#endif /* __HLIB_PARSER_TYPING_LEFTRIGHT */
