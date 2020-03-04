#ifndef __HLIB_UTILS_STRUCTS_LINKLIST
#define __HLIB_UTILS_STRUCTS_LINKLIST
#include <stdio.h>
#include "../helpers/calloc.h"

struct LinkList
{
  void *value;
  struct LinkList *prev;
};

struct LinkList *createLinkList(struct LinkList *current, void *value)
{
  struct LinkList *list = HLIB_CALLOC(struct LinkList);
  list->value = value;
  list->prev = current;
  return list;
}

#endif /* __HLIB_UTILS_STRUCTS_LINKLIST */
