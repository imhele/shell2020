#ifndef __HLIB_UTILS_PRETTY_TABLE
#define __HLIB_UTILS_PRETTY_TABLE

#include <sys/ioctl.h>
#include <unistd.h>
#include "../helpers/string.h"
#include "../structs/linklist.h"
#include "printlength.h"

void *__FormatLinkListStringsAsTableMapLength(
  void *value, int index, struct LinkList *head)
{
  void **string_and_length = HLIB_CALLOC_N(void *, 2);
  string_and_length[0] = (void *)GetUnicodePrintLength((char *)value);
  string_and_length[1] = value;
  return string_and_length;
}

void *__FormatLinkListStringsAsTableFindMaxLength(
    void *memo, void *value, int index, struct LinkList *head)
{
  if (*(unsigned long *)memo < *(unsigned long *)value)
    *(unsigned long *)memo = *(unsigned long *)value;
  return memo;
}

void PrintLinkListStringsAsTable(struct LinkList *strings, unsigned long min_space)
{
  if (strings == NULL)
    return;

  struct winsize window;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &window);

  unsigned long *max_len = HLIB_CALLOC(unsigned long);
  struct LinkList *mapped = LinkListMap(strings, __FormatLinkListStringsAsTableMapLength);
  LinkListReduce(mapped, __FormatLinkListStringsAsTableFindMaxLength, max_len);

  unsigned short columns = window.ws_col / (*max_len + min_space);
  unsigned short curr_col = columns = columns < 1 ? 1 : columns;
  unsigned short col_len = window.ws_col / columns;

  do
  {
    if (curr_col-- <= 0)
    {
      putchar('\n');
      curr_col = columns;
    }

    printf("%s", ((char **)mapped->value)[1]);

    if (*(unsigned long *)mapped->value < col_len)
    {
      char *space_str = HLIB_STRREPEAT(" ", col_len - *(unsigned long *)mapped->value);
      printf("%s", space_str);
      free(space_str);
    }
  } while ((mapped = mapped->next) != NULL);

  free(max_len);
  LinkListFreeValue(&mapped);
}

#endif /* __HLIB_UTILS_PRETTY_TABLE */
