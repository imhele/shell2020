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
          "%s%s%s%s%s%s%s",
          HLIB_TERMINAL_CONFIG(TERMINAL_CURSOR("0", "0")),
          HLIB_TERMINAL_CONFIG(TERMINAL_CLEAN_ALL),
          ps1,
          !prefix->head ? "" : (char *)prefix->head,
          HLIB_TERMINAL_CONFIG(TERMINAL_SAVE_CURSOR),
          !suffix->head ? "" : (char *)suffix->head,
          HLIB_TERMINAL_CONFIG(TERMINAL_RECOVER_CURSOR));
    }

    if (!prefix->tail || !*prefix->tail)
      ParserTypingBufferPushOne(prefix, ParserGetChar());

    if (status == PARSER_PIPELINE_STATUS_HOLD && current_pipeline != NULL)
    {
      status = current_pipeline(prefix, suffix);
    }

    else if (status == PARSER_PIPELINE_STATUS_CATCH)
    {
      current_pipeline = NULL;
      status = PARSER_PIPELINE_STATUS_PASS;
    }

    else
      for (int index = 0; __PARSER_PIPELINES[index] != NULL; index++)
      {
        status = __PARSER_PIPELINES[index](prefix, suffix);
        if (status == PARSER_PIPELINE_STATUS_PASS)
          continue;
        if (status == PARSER_PIPELINE_STATUS_HOLD)
          current_pipeline = __PARSER_PIPELINES[index];
        break;
      }
  }
}

#endif /* __HLIB_PARSER_TYPING */
