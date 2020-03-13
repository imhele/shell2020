#ifndef __HLIB_PARSER_VARIABLE
#define __HLIB_PARSER_VARIABLE

#include <stdlib.h>
#include <unistd.h>
#include "../utils/helpers/string.h"
#include "../utils/structs/map.h"

extern char **environ;
struct LinkList *__SHELL_VARIABLE_MAPS = NULL;

void __SHELL_VARIABLE_MAP_FREE_EACH(void *value, void *key, struct Map *curr)
{
  if (value != NULL)
    free(value);
  if (key != NULL)
    free(key);
}

#define SHELLCLOSURE \
  ({             \
    __SHELL_VARIABLE_MAPS = LinkListUnshift(__SHELL_VARIABLE_MAPS, MapCreate(NULL), ENDARG);

#define ENDSHELLCLOSURE                                                                        \
  MapFreeEach((struct Map **)&(__SHELL_VARIABLE_MAPS->value), __SHELL_VARIABLE_MAP_FREE_EACH); \
  struct LinkList *__SHELL_VARIABLE_NEXT_MAPS = __SHELL_VARIABLE_MAPS->next;                   \
  free(__SHELL_VARIABLE_MAPS);                                                                 \
  __SHELL_VARIABLE_MAPS = __SHELL_VARIABLE_NEXT_MAPS;                                          \
  })

#define setShellVariable(name, value)                                                           \
  ({                                                                                            \
    void *__SHELL_VARIABLE_OVERRIDED =                                                          \
        MapSet(__SHELL_VARIABLE_MAPS->value, (void *)name, (void *)value, MapIsStringKeyEqual); \
    if (__SHELL_VARIABLE_OVERRIDED != NULL)                                                     \
      free(__SHELL_VARIABLE_OVERRIDED);                                                         \
  })

#define getShellVariable(name, target)                                                    \
  ({                                                                                      \
    struct MapItem *__SHELL_VARIABLE_MAP_ITEM = NULL;                                     \
    struct LinkList *__SHELL_VARIABLE_UPPER_LEVEL_MAP = __SHELL_VARIABLE_MAPS;            \
    for (; __SHELL_VARIABLE_MAP_ITEM == NULL && __SHELL_VARIABLE_UPPER_LEVEL_MAP != NULL; \
         __SHELL_VARIABLE_UPPER_LEVEL_MAP = __SHELL_VARIABLE_UPPER_LEVEL_MAP->next)       \
      __SHELL_VARIABLE_MAP_ITEM = MapGet(                                                 \
          __SHELL_VARIABLE_UPPER_LEVEL_MAP->value, (void *)name, MapIsStringKeyEqual);    \
    if (__SHELL_VARIABLE_MAP_ITEM != NULL)                                                \
      target = NULL, HLIB_STRCAT(target, __SHELL_VARIABLE_MAP_ITEM->value);               \
  })

void ParserVariableUnsafeExec(char *command)
{
  char *name = NULL;
  char *value = NULL;
  char *copied_command = NULL;
  HLIB_STRCAT(copied_command, command);
  char *split_at = strchr(copied_command, '=');
  if (split_at != NULL)
  {
    *split_at = '\0';
    HLIB_STRCAT(name, copied_command);
    HLIB_STRCAT(value, split_at + 1);
    setShellVariable(name, value);
  }
  free(copied_command);
}

void ParserVariableBootstrap()
{
  for (char **var = environ; *var != NULL; var++)
    ParserVariableUnsafeExec(*var);
}

void ParserVariableCleanup()
{
  return;
}

#endif /* __HLIB_PARSER_VARIABLE */
