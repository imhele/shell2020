#ifndef __HLIB_UTILS_STRUCTS_LINKLIST
#define __HLIB_UTILS_STRUCTS_LINKLIST

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "../helpers/calloc.h"
#include "../helpers/endarg.h"

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
  for (prev = new_head; (value = va_arg(argv, void *)) != ENDARG; prev = curr)
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

void LinkListFreeN(struct LinkList **head, ...)
{
  va_list argv;
  LinkListFree(head);
  va_start(argv, head);
  while ((head = va_arg(argv, struct LinkList **)) != ENDARG)
    LinkListFree(head);
  va_end(argv);
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

  if (value == ENDARG)
    return head;

  if (head == NULL)
    curr = head = HLIB_CALLOC(struct LinkList);
  else
  {
    while (curr->next != NULL)
      curr = curr->next;
    curr = curr->next = HLIB_CALLOC(struct LinkList);
  }

  for (curr->value = value; (value = va_arg(argv, void *)) != ENDARG; curr->value = value)
    curr = curr->next = HLIB_CALLOC(struct LinkList);
  va_end(argv);

  return head;
}

int LinkListLength(struct LinkList *head)
{
  int length = 0;
  for (; head != NULL; length++)
    head = head->next;
  return length;
}

struct LinkList *LinkListSlice(struct LinkList *head, int start, int end)
{
  struct LinkList *curr;
  struct LinkList *new_head = NULL;

  if (start < 0 && end < 0 && start >= end)
    return new_head;

  if (start < 0 || end < 0)
  {
    int length = LinkListLength(head);
    start += start < 0 ? length : 0, end += end < 0 ? length : 0;
    start = start < 0 ? 0 : start, end = end < 0 ? 0 : end;
  }

  if (start >= end)
    return new_head;

  int count = end - start;

  while (start-- && head != NULL)
    head = head->next;

  for (curr = new_head = HLIB_CALLOC(struct LinkList); head != NULL && count--; head = head->next)
    (curr = curr->next = HLIB_CALLOC(struct LinkList))->value = head->value;

  head = new_head->next;
  free(new_head);

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

struct LinkList *LinkListCopyHead(struct LinkList *head)
{
  struct LinkList *new_head = HLIB_CALLOC(struct LinkList);
  *new_head = *head;
  return new_head;
}

struct LinkList *LinkListConcat(struct LinkList *head, ...)
{
  va_list argv;
  struct LinkList *curr = head;
  struct LinkList *new_head = head;

  va_start(argv, head);
  while (new_head == NULL && (curr = va_arg(argv, struct LinkList *)) != ENDARG)
    new_head = curr;

  if (new_head == NULL)
    return new_head;

  for (curr = new_head = LinkListCopyHead(curr); true;)
  {
    for (head = curr->next; head != NULL; head = head->next)
      (curr = curr->next = HLIB_CALLOC(struct LinkList))->value = head->value;

    head = va_arg(argv, struct LinkList *);
    if (head == ENDARG)
      break;
    if (head == NULL)
      continue;
    curr = curr->next = LinkListCopyHead(head);
  }
  va_end(argv);

  return new_head;
}

#endif /* __HLIB_UTILS_STRUCTS_LINKLIST */
