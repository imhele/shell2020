#ifndef __HLIB_COMMANDS_VARIABLE
#define __HLIB_COMMANDS_VARIABLE

#include "../utils/structs/map.h"

struct LinkList *__SHELL_VARIABLE_MAPS = NULL;

#define SHELLCLOSURE \
  ({             \
    __SHELL_VARIABLE_MAPS = LinkListUnshift(__SHELL_VARIABLE_MAPS, MapCreate(NULL), ENDARG);

#define ENDSHELLCLOSURE                                                      \
  MapFree((struct Map **)&(__SHELL_VARIABLE_MAPS->value));                   \
  struct LinkList *__SHELL_VARIABLE_NEXT_MAPS = __SHELL_VARIABLE_MAPS->next; \
  free(__SHELL_VARIABLE_MAPS);                                               \
  __SHELL_VARIABLE_MAPS = __SHELL_VARIABLE_NEXT_MAPS;                        \
  })

#define setShellVariable(name, value) \
  (MapSet(__SHELL_VARIABLE_MAPS->value, (void *)name, (void *)value, MapIsStringKeyEqual))

#define getShellVariable(name, target)                                                    \
  ({                                                                                      \
    struct MapItem *__SHELL_VARIABLE_MAP_ITEM = NULL;                                     \
    struct LinkList *__SHELL_VARIABLE_UPPER_LEVEL_MAP = __SHELL_VARIABLE_MAPS;            \
    for (; __SHELL_VARIABLE_MAP_ITEM == NULL && __SHELL_VARIABLE_UPPER_LEVEL_MAP != NULL; \
         __SHELL_VARIABLE_UPPER_LEVEL_MAP = __SHELL_VARIABLE_UPPER_LEVEL_MAP->next)       \
      __SHELL_VARIABLE_MAP_ITEM = MapGet(                                                 \
          __SHELL_VARIABLE_UPPER_LEVEL_MAP->value, (void *)name, MapIsStringKeyEqual);    \
    if (__SHELL_VARIABLE_MAP_ITEM != NULL)                                                \
      target = (typeof(target))__SHELL_VARIABLE_MAP_ITEM->value;                          \
  })

#endif /* __HLIB_COMMANDS_VARIABLE */
