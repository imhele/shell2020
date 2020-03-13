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
  if (*(prefix->tail - 1) == 3)
  {
    printf("%s\n%s", suffix->head,HLIB_TERMINAL_CONFIG(TERMINAL_SAVE_CURSOR));

    // memset(prefix->head, 0, prefix->size * sizeof(char));
    // memset(suffix->head, 0, suffix->size * sizeof(char));
    // prefix->tail = prefix->head;
    // suffix->tail = suffix->head;

    free(prefix->head);
    free(suffix->head);
    memset(prefix, 0, sizeof(struct ParserTypingBuffer));
    memset(suffix, 0, sizeof(struct ParserTypingBuffer));
    ParserTypingBufferCalloc(prefix, 0);
    ParserTypingBufferCalloc(suffix, 0);

    return PARSER_PIPELINE_STATUS_FLUSH;
  }

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
