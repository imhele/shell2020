#ifndef __HLIB_PARSER_TYPING_ENDOFTRANSBLOCK
#define __HLIB_PARSER_TYPING_ENDOFTRANSBLOCK

#include "../../utils/helpers/string.h"
#include "../../utils/pretty/terminal.h"
#include "_buffer.h"
#include "_enum.h"

char *ParserTypingEndOfTransBlockSeparator = " !\"#$\037&'()*+,-./:;<=>?@[\\]^_`{|}~";

PARSER_PIPELINE_STATUS ParserTypingEndOfTransBlock(
    struct ParserTypingBuffer *prefix,
    struct ParserTypingBuffer *suffix,
    unsigned int hold_offset,
    char quoted_flag)
{
  if (*(prefix->tail - 1) == 23)
  {
    *(--prefix->tail) = 0;
    if (prefix->tail - prefix->head <= 0)
      return PARSER_PIPELINE_STATUS_CATCH;

    char *rev_prefix = HLIB_STRREV(prefix->head);
    char *go_back = strpbrk(rev_prefix + 1, ParserTypingEndOfTransBlockSeparator);
    unsigned int go_back_size =
        go_back == NULL ? prefix->tail - prefix->head : go_back - rev_prefix;
    free(rev_prefix);
    prefix->tail -= go_back_size;
    memset(prefix->tail, 0, go_back_size * sizeof(char));
    return PARSER_PIPELINE_STATUS_RESET;
  }

  return PARSER_PIPELINE_STATUS_PASS;
}

#endif /* __HLIB_PARSER_TYPING_ENDOFTRANSBLOCK */
