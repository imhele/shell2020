#ifndef __HLIB_PARSER_ECHO
#define __HLIB_PARSER_ECHO

#include <sys/ioctl.h>
#include <unistd.h>
#include "../utils/helpers/calloc.h"
#include "../utils/pretty/printlength.h"
#include "../utils/pretty/terminal.h"

struct ParserTypingEchoMeta
{
  char *prev_ps1;
  char *prev_prefix_head;
  char *prev_prefix_tail;
  char *prev_suffix_head;
  char *prev_suffix_tail;
  unsigned long ps1_length;
  unsigned long prefix_length;
  unsigned long suffix_length;
};

void ParserEcho(
    char *ps1,
    char *prefix_head,
    char *prefix_tail,
    char *suffix_head,
    char *suffix_tail,
    struct ParserTypingEchoMeta *echo_meta)
{
  if (ps1 != NULL && ps1 != echo_meta->prev_ps1)
    echo_meta->ps1_length = GetUnicodePrintLength(ps1);
  if (prefix_head != echo_meta->prev_prefix_head || prefix_tail != echo_meta->prev_prefix_tail)
    echo_meta->prefix_length = GetUnicodePrintLength(prefix_head);
  if (suffix_head != echo_meta->prev_suffix_head || suffix_tail != echo_meta->prev_suffix_tail)
    echo_meta->suffix_length = GetUnicodePrintLength(suffix_head);

  echo_meta->prev_ps1 = ps1;
  echo_meta->prev_prefix_head = prefix_head;
  echo_meta->prev_prefix_tail = prefix_tail;
  echo_meta->prev_suffix_head = suffix_head;
  echo_meta->prev_suffix_tail = suffix_tail;

  if (ps1 != NULL)
    printf("\r%s%s%s%s%s",
           ps1,
           prefix_head,
           HLIB_TERMINAL_CONFIG(TERMINAL_SAVE_CURSOR),
           suffix_head,
           HLIB_TERMINAL_CONFIG(TERMINAL_RECOVER_CURSOR));
  else
    printf("%s%s%s%s",
           prefix_head,
           HLIB_TERMINAL_CONFIG(TERMINAL_SAVE_CURSOR),
           suffix_head,
           HLIB_TERMINAL_CONFIG(TERMINAL_RECOVER_CURSOR));
}

unsigned long *ParserEchoGetCursorOffset(unsigned long length, struct winsize window)
{
  unsigned long *offset = HLIB_CALLOC_N(unsigned long, 2);
  *(offset + 1) = window.ws_col > 0 ? length % window.ws_col : 0;
  *offset = window.ws_col > 0 ? (unsigned long)(length / window.ws_col) : 0;
  if (!*(offset + 1) && *offset)
    (*offset)--;
  if (*offset > window.ws_row)
    *offset = window.ws_row;
  return offset;
}

void ParserEchoCleanFromHead(struct ParserTypingEchoMeta *echo_meta)
{
  unsigned long curr_length = echo_meta->ps1_length + echo_meta->prefix_length;
  unsigned long tail_length = curr_length + echo_meta->suffix_length;

  if (!tail_length)
    return;

  struct winsize window;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &window);
  unsigned long *curr_offset = ParserEchoGetCursorOffset(curr_length, window);
  unsigned long *tail_offset = ParserEchoGetCursorOffset(tail_length, window);

  for (int down_line = *tail_offset - *curr_offset; down_line > 0; down_line--)
    printf("%s", HLIB_TERMINAL_CONFIG(TERMINAL_CURSOR_DOWN));

  for (printf("\r%s", HLIB_TERMINAL_CONFIG(TERMINAL_CLEAN)); (*tail_offset)--;)
    printf("%s%s", HLIB_TERMINAL_CONFIG(TERMINAL_CLEAN), HLIB_TERMINAL_CONFIG(TERMINAL_CURSOR_UP));

  free(curr_offset);
  free(tail_offset);
}

#endif /* __HLIB_PARSER_ECHO */
