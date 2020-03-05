#ifndef __HLIB_UTILS_STRUCTS_LINKLIST
#define __HLIB_UTILS_STRUCTS_LINKLIST

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "../helpers/calloc.h"

struct LinkList
{
  void *value;
  struct LinkList *next;
};

struct LinkList *LinkListUnshift(struct LinkList *head, ...)
{
  void *value;
  va_list argv;
  struct LinkList *curr;
  struct LinkList *prev;
  struct LinkList *new_head = HLIB_CALLOC(struct LinkList);

  va_start(argv, head);
  for (prev = new_head; value = va_arg(argv, void *); prev = curr)
    (prev->next = curr = HLIB_CALLOC(struct LinkList))->value = value;
  va_end(argv);

  prev->next = head;
  head = new_head->next;
  free(new_head);

  return head;
}

void *LinkListGetter(struct LinkList *head, int index)
{
  if (index < 0)
    return NULL;
  while (head && index--)
    head = head->next;
  return head ? head->value : NULL;
}

#endif /* __HLIB_UTILS_STRUCTS_LINKLIST */
