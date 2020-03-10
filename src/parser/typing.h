#ifndef __HLIB_PARSER_TYPING
#define __HLIB_PARSER_TYPING

#include <stdio.h>
#include <stdlib.h>
#include "../utils/helpers/calloc.h"
#include "../utils/pretty/terminal.h"
#include "getch.h"
#include "pipeline.h"
#include "ps1.h"

typedef PARSER_PIPELINE_STATUS (*PARSER_PIPELINE)(
    struct ParserTypingBuffer *prefix, struct ParserTypingBuffer *suffix);

PARSER_PIPELINE __PARSER_PIPELINES[3] = {
    ParserTypingExit,
    ParserTypingStartOfHeading,
    NULL,
};

void ParserTyping()
{
  int *cursor_coord;
  int hold_offset = 0;
  int quoted_flag = 0;
  char *ps1 = ParserPS1();
  PARSER_PIPELINE current_pipeline = NULL;
  PARSER_PIPELINE_STATUS status = PARSER_PIPELINE_STATUS_RESET;
  struct ParserTypingBuffer *prefix = HLIB_CALLOC(struct ParserTypingBuffer);
  struct ParserTypingBuffer *suffix = HLIB_CALLOC(struct ParserTypingBuffer);

  while (status != PARSER_PIPELINE_STATUS_EXIT)
  {
    if (status == PARSER_PIPELINE_STATUS_RESET)
    {
      current_pipeline = NULL;
      status = PARSER_PIPELINE_STATUS_PASS;
      printf(
          "\r%s%s%s%s%s%s",
          HLIB_TERMINAL_CONFIG(TERMINAL_CLEAN),
          ps1,
          !prefix->head ? "" : (char *)prefix->head,
          HLIB_TERMINAL_CONFIG(TERMINAL_SAVE_CURSOR),
          !suffix->head ? "" : (char *)suffix->head,
          HLIB_TERMINAL_CONFIG(TERMINAL_RECOVER_CURSOR));
    }

    if (!prefix->size || !*prefix->tail)
      ParserTypingBufferPushOne(prefix, ParserGetChar());
    else
      prefix->tail++;

    if (*(prefix->tail - 1) == 39 || *(prefix->tail - 1) == 34)
      quoted_flag = quoted_flag == *(prefix->tail - 1) ? 0 : *(prefix->tail - 1);

    if (status == PARSER_PIPELINE_STATUS_HOLD)
    {
      status = current_pipeline(prefix, suffix);
      if (status == PARSER_PIPELINE_STATUS_PASS)
      {
        current_pipeline = NULL;
        if (prefix->tail - prefix->head > hold_offset)
          prefix->tail = prefix->head + hold_offset;
      }
    }
    else if (!quoted_flag)
    {
      for (
          int index = 0;
          status == PARSER_PIPELINE_STATUS_PASS && __PARSER_PIPELINES[index] != NULL;
          index++)
      {
        status = __PARSER_PIPELINES[index](prefix, suffix);
        if (status == PARSER_PIPELINE_STATUS_HOLD)
        {
          hold_offset = prefix->tail - prefix->head;
          current_pipeline = __PARSER_PIPELINES[index];
        }
      }
    }

    if (status == PARSER_PIPELINE_STATUS_PASS)
      printf("%c%s%s%s",
             *(prefix->tail - 1),
             HLIB_TERMINAL_CONFIG(TERMINAL_SAVE_CURSOR),
             !suffix->head ? "" : (char *)suffix->head,
             HLIB_TERMINAL_CONFIG(TERMINAL_RECOVER_CURSOR));
  }
}

#endif /* __HLIB_PARSER_TYPING */
