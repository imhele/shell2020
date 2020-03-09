#ifndef __HLIB_COMMANDS_META_ARGUMENTS
#define __HLIB_COMMANDS_META_ARGUMENTS

#include "../../utils/helpers/closure.h"
#include "../../utils/helpers/string.h"
#include "../../utils/structs/map.h"

enum CommandArgumentType
{
  CommandArgumentOptional,
  CommandArgumentRequired,
  CommandArgumentMultiple,
};

struct CommandMetaArgumentsMap
{
  struct Map *name;
  struct Map *alias;
};

struct CommandMetaArgument
{
  short type;
  char *alias;
  char *description;
  struct CommandMetaArgumentsMap *sub_arguments;
};

char *__CommandMetaArgumentToStringPrefix[3] = {"--", "", "..."};
char *__CommandMetaArgumentToStringBracket[3][2] = {{"[", "]"}, {"<", ">"}, {"<", ">"}};

struct CommandMetaArgumentsMap *CommandMetaArgumentRegister(
    struct CommandMetaArgumentsMap *meta_map, char *name, struct CommandMetaArgument *meta)
{
  if (meta_map == NULL)
  {
    meta_map = HLIB_CALLOC(struct CommandMetaArgumentsMap);
    meta_map->name = MapCreate(NULL);
    meta_map->alias = MapCreate(NULL);
  }

  MapSet(meta_map->name, name, meta, MapIsStringKeyEqual);
  if (meta->alias != NULL)
    MapSet(meta_map->alias, meta->alias, meta, MapIsStringKeyEqual);

  return meta_map;
}

void CommandMetaArgumentsMapFree(struct CommandMetaArgumentsMap **meta_map);

void __CommandMetaArgumentFreeEach(void *value, void *key, struct Map *curr)
{
  struct CommandMetaArgument *meta = (struct CommandMetaArgument *)value;
  if (meta != NULL && meta->sub_arguments != NULL)
    CommandMetaArgumentsMapFree(&(meta->sub_arguments));
}

void CommandMetaArgumentsMapFree(struct CommandMetaArgumentsMap **meta_map)
{
  if (meta_map == NULL || *meta_map == NULL)
    return;

  MapFreeEach(&((*meta_map)->name), __CommandMetaArgumentFreeEach);
  MapFreeEach(&((*meta_map)->alias), __CommandMetaArgumentFreeEach);

  *meta_map = NULL;
}

struct LinkList *CommandMetaArgumentsMapToString(
    struct CommandMetaArgumentsMap *meta_map,
    int wrap_level,
    bool show_desc,
    const void *display_config);

void *__CommandMetaArgumentReduceToString(void *memo, void *curr, int index, struct Map *head)
{
  if (curr == NULL)
    return memo;

  int wrap_level;
  bool show_desc;
  char *str = NULL;
  char *display_config;
  struct LinkList *strings = (struct LinkList *)memo;
  struct CommandMetaArgument *meta = (struct CommandMetaArgument *)((struct MapItem *)curr)->value;
  char *prefix = __CommandMetaArgumentToStringPrefix[meta->type];
  char **bracket = __CommandMetaArgumentToStringBracket[meta->type];

  useClosureValue(show_desc);
  useClosureValue(wrap_level);
  useClosureValue(display_config);
  struct LinkList *sub_strings =
      CommandMetaArgumentsMapToString(
          meta->sub_arguments, wrap_level > 0 ? wrap_level - 1 : 0, show_desc, display_config);

  if (((struct MapItem *)curr)->key != NULL)
  {
    HLIB_STRCAT(str, prefix);
    HLIB_STRCAT(str, ((struct MapItem *)curr)->key);
  }

  if (meta->alias != NULL)
  {
    HLIB_STRCAT(str, " (-");
    HLIB_STRCAT(str, meta->alias);
    HLIB_STRCAT(str, ")");
  }

  if (show_desc)
  {
    HLIB_STRCAT_LEFT(str, "m");
    HLIB_STRCAT_LEFT(str, display_config);
    HLIB_STRCAT_LEFT(str, "\033[");
    HLIB_STRCAT(str, "\033[0m: ");
    HLIB_STRCAT(str, meta->description);
  }

  HLIB_STRCAT_LEFT(str, bracket[0]);

  if (wrap_level <= 0)
  {
    if (strings == NULL)
      strings = HLIB_CALLOC(struct LinkList);
    else
      HLIB_STRCAT(strings->value, " ");
    HLIB_STRCAT(strings->value, str), free(str);
    if (sub_strings != NULL)
    {
      HLIB_STRCAT(strings->value, " ");
      HLIB_STRCAT(strings->value, sub_strings->value);
      free(sub_strings->value), LinkListFree(&sub_strings);
    }
    HLIB_STRCAT(strings->value, bracket[1]);
    return strings;
  }

  if (sub_strings == NULL)
  {
    HLIB_STRCAT(str, bracket[1]);
    return LinkListUnshift(strings, str, ENDARG);
  }

  if (wrap_level == 1)
  {
    HLIB_STRCAT(str, " ");
    HLIB_STRCAT(str, sub_strings->value);
    HLIB_STRCAT(str, bracket[1]);
    free(sub_strings->value), LinkListFree(&sub_strings);
    return LinkListUnshift(strings, str, ENDARG);
  }

  for (struct LinkList *curr = sub_strings; true; curr = curr->next)
  {
    HLIB_STRCAT_LEFT(curr->value, "\t");
    if (curr->next == NULL)
    {
      curr->next = LinkListUnshift(strings, str, ENDARG);
      return LinkListUnshift(sub_strings, HLIB_STRREPEAT(bracket[1], 1), ENDARG);
    }
  }
}

struct LinkList *CommandMetaArgumentsMapToString(
    struct CommandMetaArgumentsMap *meta_map,
    int wrap_level,
    bool show_desc,
    const void *display_config)
{
  if (meta_map == NULL)
    return NULL;
  if (display_config == DEFAULTARG)
    display_config = "1;36";
  struct LinkList *result;
  CLOSURE
  useClosure(show_desc);
  useClosure(wrap_level);
  useClosure(display_config);
  result = LinkListReduce(meta_map->name->next, __CommandMetaArgumentReduceToString, NULL);
  ENDCLOSURE;
  return result;
}

#endif /* __HLIB_COMMANDS_META_ARGUMENTS */
