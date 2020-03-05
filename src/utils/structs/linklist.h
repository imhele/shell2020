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
  for (prev = new_head; (value = va_arg(argv, void *)) != NULL; prev = curr)
    (prev->next = curr = HLIB_CALLOC(struct LinkList))->value = value;
  va_end(argv);

  prev->next = head;
  head = new_head->next;
  free(new_head);

  return head;
}

void LinkListFree(struct LinkList **head)
{
  if (head == NULL || *head == NULL)
    return;

  struct LinkList *next;
  struct LinkList *curr = *head;
  while (curr != NULL)
  {
    next = curr->next;
    free(curr);
    curr = next;
  }

  *head = NULL;
}

void LinkListFreeValue(struct LinkList **head)
{
  if (head == NULL || *head == NULL)
    return;

  struct LinkList *next;
  struct LinkList *curr = *head;
  while (curr != NULL)
  {
    next = curr->next;
    if (curr->value != NULL)
      free(curr->value);
    free(curr);
    curr = next;
  }

  *head = NULL;
}

struct LinkList *LinkListPush(struct LinkList *head, ...)
{
  va_list argv;
  va_start(argv, head);

  struct LinkList *curr;
  void *value = va_arg(argv, void *);

  if (value == NULL)
    return head;

  if (head == NULL)
    curr = head = HLIB_CALLOC(struct LinkList);
  else
  {
    while (curr->next != NULL)
      curr = curr->next;
    curr = curr->next = HLIB_CALLOC(struct LinkList);
  }

  for (curr->value = value; (value = va_arg(argv, void *)) != NULL; curr->value = value)
    curr = curr->next = HLIB_CALLOC(struct LinkList);
  va_end(argv);

  return head;
}

void *LinkListGetter(struct LinkList *head, int index)
{
  if (index < 0)
    return NULL;
  while (head != NULL && index--)
    head = head->next;
  return head ? head->value : NULL;
}

#endif /* __HLIB_UTILS_STRUCTS_LINKLIST */
