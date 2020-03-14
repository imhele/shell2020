#ifndef __HLIB_PARSER_TYPING
#define __HLIB_PARSER_TYPING

#include <stdio.h>
#include <stdlib.h>
#include "../utils/helpers/calloc.h"
#include "../utils/pretty/terminal.h"
#include "echo.h"
#include "getch.h"
#include "pipeline.h"
#include "ps1.h"

typedef PARSER_PIPELINE_STATUS (*PARSER_PIPELINE)(
    struct ParserTypingBuffer *prefix,
    struct ParserTypingBuffer *suffix,
    unsigned int hold_offset,
    char quoted_flag);

PARSER_PIPELINE __PARSER_PIPELINES[10] = {
    ParserTypingExit,
    ParserTypingLeftRight,
    ParserTypingStartOfHeading,
    ParserTypingEnquiry,
    ParserTypingDel,
    ParserTypingSkipWord,
    ParserTypingEndOfTransBlock,
    ParserTypingUpDown,
    ParserTypingESC,
    NULL,
};

void __ParserTypingSetQuotedFlag(struct ParserTypingBuffer *prefix, char *quoted_flag);

char *ParserTyping()
{
  char quoted_flag = 0;
  char *ps1 = ParserPS1();
  unsigned int hold_offset = -1;
  unsigned int current_pipeline = -1;
  PARSER_PIPELINE_STATUS status = PARSER_PIPELINE_STATUS_RESET;
  struct ParserTypingBuffer *prefix = HLIB_CALLOC(struct ParserTypingBuffer);
  struct ParserTypingBuffer *suffix = HLIB_CALLOC(struct ParserTypingBuffer);
  struct ParserTypingEchoMeta *echo_meta = HLIB_CALLOC(struct ParserTypingEchoMeta);
  ParserTypingBufferCalloc(prefix, 0);
  ParserTypingBufferCalloc(suffix, 0);

  ParserGetCharPreset();

  while (status != PARSER_PIPELINE_STATUS_EXIT && status != PARSER_PIPELINE_STATUS_ENDL)
  {
    if (status == PARSER_PIPELINE_STATUS_RESET || status == PARSER_PIPELINE_STATUS_FLUSH)
    {
      if (status != PARSER_PIPELINE_STATUS_FLUSH)
        ParserEchoCleanFromHead(echo_meta);
      ParserEchoUpdateMeta(ps1, prefix->head, prefix->tail, suffix->head, suffix->tail, echo_meta);
      if (status == PARSER_PIPELINE_STATUS_FLUSH)
        ParserEchoCleanFromHead(echo_meta);
      ParserEcho(ps1, prefix->head, prefix->tail, suffix->head, suffix->tail);

      current_pipeline = hold_offset = -1;
      status = PARSER_PIPELINE_STATUS_PASS;
    }

    if (status == PARSER_PIPELINE_STATUS_PASS)
    {
      if (current_pipeline >= 0)
      {
        if (__PARSER_PIPELINES[++current_pipeline] == NULL)
          current_pipeline = hold_offset = -1;
        else if (prefix->tail - prefix->head > hold_offset)
          prefix->tail = prefix->head + hold_offset;
      }

      if (!*prefix->tail)
      {
        ParserTypingBufferPushOne(prefix, ParserGetChar());
        __ParserTypingSetQuotedFlag(prefix, &quoted_flag);
      }
      else if (prefix->tail != prefix->head + hold_offset)
        prefix->tail++;

      for (
          unsigned int index = current_pipeline >= 0 ? current_pipeline : 0;
          status == PARSER_PIPELINE_STATUS_PASS && __PARSER_PIPELINES[index] != NULL;
          index++)
      {
        status =
            __PARSER_PIPELINES[index](prefix, suffix, prefix->tail - prefix->head, quoted_flag);
        if (status == PARSER_PIPELINE_STATUS_HOLD)
          hold_offset = prefix->tail - prefix->head, current_pipeline = index;
        else
          current_pipeline = hold_offset = -1;
      }

      if (status == PARSER_PIPELINE_STATUS_PASS)
      {
        ParserEchoCleanFromHead(echo_meta);
        ParserEchoUpdateMeta(ps1, prefix->head, prefix->tail, suffix->head, suffix->tail, echo_meta);
        ParserEcho(ps1, prefix->head, prefix->tail, suffix->head, suffix->tail);
      }
    }
    else if (status == PARSER_PIPELINE_STATUS_HOLD)
    {
      if (!*prefix->tail)
        ParserTypingBufferPushOne(prefix, ParserGetChar());
      else
        prefix->tail++;
      status = __PARSER_PIPELINES[current_pipeline](prefix, suffix, hold_offset, quoted_flag);
    }
    else if (status == PARSER_PIPELINE_STATUS_CATCH)
    {
      current_pipeline = hold_offset = -1;
      status = PARSER_PIPELINE_STATUS_PASS;
    }
  }

  ParserGetCharClean();

  char *command = NULL;

  if (status == PARSER_PIPELINE_STATUS_ENDL)
  {
    unsigned int prefix_len = prefix->tail - prefix->head;
    unsigned int suffix_len = suffix->tail - suffix->head;
    command = HLIB_CALLOC_N(char, prefix_len + suffix_len + 1);
    if (prefix_len)
      memcpy(command, prefix->head, prefix_len * sizeof(char));
    if (suffix_len)
      memcpy(command + prefix_len, suffix->head, suffix_len * sizeof(char));
  }

  free(prefix->head);
  free(suffix->head);
  free(ps1);
  free(prefix);
  free(suffix);
  free(echo_meta);

  return command;
}

void __ParserTypingSetQuotedFlag(struct ParserTypingBuffer *prefix, char *quoted_flag)
{
  if (*(prefix->tail - 1) == 39 || *(prefix->tail - 1) == 34)
    *quoted_flag = *quoted_flag == *(prefix->tail - 1) ? 0 : *(prefix->tail - 1);
}

#endif /* __HLIB_PARSER_TYPING */
