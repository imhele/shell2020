#ifndef __HLIB_UTILS_STRUCTS_MAP
#define __HLIB_UTILS_STRUCTS_MAP

#include "../helpers/endarg.h"
#include "./bool.h"
#include "./linklist.h"

struct MapItem
{
  void *key;
  void *value;
};

bool __MapDefaultIsKeyEqual(void *a, void *b)
{
  return a == b;
}

struct MapItem *MapGet(
    struct LinkList *head, void *key, bool (*isKeyEqual)(void *a, void *b))
{
  if (isKeyEqual == ENDARG)
    isKeyEqual = __MapDefaultIsKeyEqual;
  for (; head != NULL; head = head->next)
    if (isKeyEqual(((struct MapItem *)(head->value))->key, key))
      return head->value;
  return NULL;
}

bool MapHas(
    struct LinkList *head, void *key, bool (*isKeyEqual)(void *a, void *b))
{
  head = (void *)MapGet(head, key, isKeyEqual);
  return head != NULL;
}

struct LinkList *MapSet(
    struct LinkList *head, void *key, void *value, bool (*isKeyEqual)(void *a, void *b))
{
  struct MapItem *exists = MapGet(head, key, isKeyEqual);
  if (exists == NULL)
    head = LinkListUnshift(head);
  else
    exists->value = value;
  return head;
}

#endif /* __HLIB_UTILS_STRUCTS_MAP */
