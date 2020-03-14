#ifndef __HLIB_PARSER_TYPING_UPDOWN
#define __HLIB_PARSER_TYPING_UPDOWN

#include "../../utils/pretty/terminal.h"
#include "../../utils/structs/bool.h"
#include "../history.h"
#include "_buffer.h"
#include "_enum.h"

int __ParserTypingUpDownHistoryPointer = -1;

PARSER_PIPELINE_STATUS ParserTypingUpDown(
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
    if (cache_len == 1 && *(prefix->tail - 1) == '[')
      return PARSER_PIPELINE_STATUS_HOLD;
    if (cache_len == 2)
    {
      bool is_up = *(prefix->tail - 1) == 'A';
      bool is_down = *(prefix->tail - 1) == 'B';

      if (!is_up && !is_down)
        return PARSER_PIPELINE_STATUS_PASS;

      memset(prefix->tail -= 3, 0, 3 * sizeof(char));
      int next_pointer = __ParserTypingUpDownHistoryPointer;

      if (next_pointer < 0)
      {
        if (is_down)
          return PARSER_PIPELINE_STATUS_CATCH;
        next_pointer = __HLIB_PARSER_COMMAND_HISTORIES_TAIL;
      }

      next_pointer = ParserCommandHistoryGetNextIndex(next_pointer, is_up ? -1 : 1);
      if (next_pointer == __HLIB_PARSER_COMMAND_HISTORIES_TAIL)
        return PARSER_PIPELINE_STATUS_CATCH;
      if (__HLIB_PARSER_COMMAND_HISTORIES[next_pointer] == NULL)
        return PARSER_PIPELINE_STATUS_CATCH;

      unsigned int cmd_len = strlen(__HLIB_PARSER_COMMAND_HISTORIES[next_pointer]);

      free(prefix->head);
      free(suffix->head);
      memset(prefix, 0, sizeof(struct ParserTypingBuffer));
      memset(suffix, 0, sizeof(struct ParserTypingBuffer));
      ParserTypingBufferCalloc(suffix, 0);
      ParserTypingBufferCalloc(prefix, cmd_len + 1);
      prefix->tail = prefix->head + cmd_len;
      memcpy(prefix->head, __HLIB_PARSER_COMMAND_HISTORIES[next_pointer], cmd_len * sizeof(char));

      __ParserTypingUpDownHistoryPointer = next_pointer;
      return PARSER_PIPELINE_STATUS_RESET;
    }
  }

  __ParserTypingUpDownHistoryPointer = -1;
  return PARSER_PIPELINE_STATUS_PASS;
}

#endif /* __HLIB_PARSER_TYPING_UPDOWN */
