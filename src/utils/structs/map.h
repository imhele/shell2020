#ifndef __HLIB_UTILS_STRUCTS_MAP
#define __HLIB_UTILS_STRUCTS_MAP

#include "../symbols.h"
#include "./bool.h"
#include "./linklist.h"

#define Map LinkList

struct MapItem
{
  void *key;
  void *value;
};

/**
 * @return the head of map is always an empty node, or stores meta data.
 **/
struct Map *MapCreate(void *meta)
{
  struct Map *map = HLIB_CALLOC(struct Map);
  map->value = meta, map->next = NULL;
  return map;
}

bool __MapDefaultIsKeyEqual(void *a, void *b)
{
  return a == b;
}

struct MapItem *MapGet(struct Map *head, void *key, bool (*isKeyEqual)(void *a, void *b))
{
  if (isKeyEqual == DEFAULTARG)
    isKeyEqual = __MapDefaultIsKeyEqual;
  while ((head = head->next) != NULL)
    if (isKeyEqual(((struct MapItem *)(head->value))->key, key))
      return head->value;
  return NULL;
}

bool MapHas(struct Map *head, void *key, bool (*isKeyEqual)(void *a, void *b))
{
  head = (void *)MapGet(head, key, isKeyEqual);
  return head != NULL;
}

/**
 * @return overrided value.
 **/
void *MapSet(struct Map *head, void *key, void *value, bool (*isKeyEqual)(void *a, void *b))
{
  struct MapItem *exists = MapGet(head, key, isKeyEqual);
  if (exists != NULL)
  {
    void *old_value = exists->value;
    exists->value = value;
    return old_value;
  }

  exists = HLIB_CALLOC(struct MapItem);
  exists->key = key, exists->value = value;
  head->next = LinkListUnshift(head->next, exists, ENDARG);

  return NULL;
}

void MapFree(struct Map **map)
{
  if (map == NULL || *map == NULL)
    return;

  struct Map *next;
  struct Map *curr = *map;
  while (curr != NULL)
  {
    next = curr->next;
    if (curr->value != NULL)
      free(curr->value);
    free(curr);
    curr = next;
  }

  *map = NULL;
}

void MapFreeN(struct Map **map, ...)
{
  va_list argv;
  LinkListFree(map);
  va_start(argv, map);
  while ((map = va_arg(argv, struct Map **)) != ENDARG)
    MapFree(map);
  va_end(argv);
}

void MapFreeEach(struct Map **map, void (*callback)(void *value, void *key, struct Map *curr))
{
  if (map == NULL || *map == NULL)
    return;

  struct Map *next;
  struct Map *curr = *map;

  while (curr != NULL)
  {
    next = curr->next;
    if (curr->value != NULL)
    {
      callback(((struct MapItem *)curr->value)->value, ((struct MapItem *)curr->value)->key, curr);
      free(curr->value);
    }
    free(curr);
    curr = next;
  }

  *map = NULL;
}

#endif /* __HLIB_UTILS_STRUCTS_MAP */
