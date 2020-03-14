#ifndef __HLIB_PARSER_TYPING_SKIPWORD
#define __HLIB_PARSER_TYPING_SKIPWORD

#include "../../utils/helpers/string.h"
#include "../../utils/pretty/terminal.h"
#include "../../utils/structs/bool.h"
#include "_buffer.h"
#include "_enum.h"

char *ParserTypingSkipWordSeparator = " !\"#$\037&'()*+,-./:;<=>?@[\\]^_`{|}~";

PARSER_PIPELINE_STATUS ParserTypingSkipWord(
    struct ParserTypingBuffer *prefix,
    struct ParserTypingBuffer *suffix,
    unsigned int hold_offset,
    char quoted_flag)
{
  if (*(prefix->head + hold_offset - 1) == 27)
  {
    unsigned int cache_len = prefix->tail - prefix->head - hold_offset;
    if (cache_len == 0)
      return PARSER_PIPELINE_STATUS_HOLD;
    if (cache_len == 1)
    {
      bool is_left = *(prefix->tail - 1) == 'b';
      bool is_right = *(prefix->tail - 1) == 'f';

      if (!is_left && !is_right)
        return PARSER_PIPELINE_STATUS_PASS;

      memset(prefix->tail -= 2, 0, 2 * sizeof(char));

      if (is_right && suffix->tail - suffix->head)
      {
        char *go_back = strpbrk(suffix->head + 1, ParserTypingSkipWordSeparator);
        unsigned int go_back_size = (go_back == NULL ? suffix->tail : go_back) - suffix->head;
        unsigned int suffix_move_size = suffix->tail - suffix->head - go_back_size;

        suffix->tail -= go_back_size;
        ParserTypingBufferPush(prefix, suffix->head, go_back_size);
        memcpy(suffix->head, suffix->head + go_back_size, suffix_move_size * sizeof(char));
        memset(suffix->head + suffix_move_size, 0, go_back_size * sizeof(char));
        return PARSER_PIPELINE_STATUS_RESET;
      }

      if (is_left && prefix->tail - prefix->head)
      {
        char *rev_prefix = HLIB_STRREV(prefix->head);
        char *go_back = strpbrk(rev_prefix + 1, ParserTypingSkipWordSeparator);
        unsigned int go_back_size =
            go_back == NULL ? prefix->tail - prefix->head : go_back - rev_prefix;
        free(rev_prefix);
        prefix->tail -= go_back_size;
        ParserTypingBufferUnshift(suffix, prefix->tail, go_back_size);
        memset(prefix->tail, 0, go_back_size * sizeof(char));
        return PARSER_PIPELINE_STATUS_RESET;
      }

      return PARSER_PIPELINE_STATUS_CATCH;
    }
  }

  return PARSER_PIPELINE_STATUS_PASS;
}

#endif /* __HLIB_PARSER_TYPING_SKIPWORD */
