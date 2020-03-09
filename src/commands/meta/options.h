#ifndef __HLIB_COMMANDS_META_OPTIONS
#define __HLIB_COMMANDS_META_OPTIONS

#include "../../utils/helpers/closure.h"
#include "../../utils/helpers/string.h"
#include "../../utils/structs/map.h"

enum CommandMetaOptionType
{
  CommandMetaOptionNormal,
  CommandMetaOptionRequired,
  CommandMetaOptionMultiple,
};

struct CommandMetaOptions
{
  struct Map *name;
  struct Map *alias;
};

struct CommandMetaOption
{
  short type;
  char *alias;
  char *description;
  struct CommandMetaOptions *sub_options;
};

char *__CommandMetaOptionToStringPrefix[3] = {"--", "", "..."};
char *__CommandMetaOptionToStringBracket[3][2] = {{"[", "]"}, {"<", ">"}, {"<", ">"}};

struct CommandMetaOptions *CommandMetaOptionsRegister(
    struct CommandMetaOptions *options, char *name, struct CommandMetaOption *detail)
{
  if (options == NULL)
  {
    options = HLIB_CALLOC(struct CommandMetaOptions);
    options->name = MapCreate(NULL);
    options->alias = MapCreate(NULL);
  }

  MapSet(options->name, name, detail, MapIsStringKeyEqual);
  if (detail->alias != NULL)
    MapSet(options->alias, detail->alias, detail, MapIsStringKeyEqual);

  return options;
}

void CommandMetaOptionsFree(struct CommandMetaOptions **options);

void __CommandMetaOptionFreeEach(void *value, void *key, struct Map *curr)
{
  struct CommandMetaOption *option = (struct CommandMetaOption *)value;
  if (option != NULL && option->sub_options != NULL)
    CommandMetaOptionsFree(&(option->sub_options));
}

void CommandMetaOptionsFree(struct CommandMetaOptions **options)
{
  if (options == NULL || *options == NULL)
    return;

  MapFreeEach(&((*options)->name), __CommandMetaOptionFreeEach);
  MapFreeEach(&((*options)->alias), __CommandMetaOptionFreeEach);

  *options = NULL;
}

struct LinkList *CommandMetaOptionsToString(
    struct CommandMetaOptions *options, int wrap_level, bool show_desc, const void *display_config);

void *__CommandMetaOptionsReduceToString(void *memo, void *curr, int index, struct Map *head)
{
  if (curr == NULL)
    return memo;

  int wrap_level;
  bool show_desc;
  char *str = NULL;
  char *display_config;
  struct LinkList *strings = (struct LinkList *)memo;
  struct CommandMetaOption *option = (struct CommandMetaOption *)((struct MapItem *)curr)->value;
  char *prefix = __CommandMetaOptionToStringPrefix[option->type];
  char **bracket = __CommandMetaOptionToStringBracket[option->type];

  useClosureValue(show_desc);
  useClosureValue(wrap_level);
  useClosureValue(display_config);
  struct LinkList *sub_strings =
      CommandMetaOptionsToString(
          option->sub_options, wrap_level > 0 ? wrap_level - 1 : 0, show_desc, display_config);

  if (((struct MapItem *)curr)->key != NULL)
  {
    HLIB_STRCAT(str, prefix);
    HLIB_STRCAT(str, ((struct MapItem *)curr)->key);
  }

  if (option->alias != NULL)
  {
    HLIB_STRCAT(str, " (-");
    HLIB_STRCAT(str, option->alias);
    HLIB_STRCAT(str, ")");
  }

  if (show_desc)
  {
    HLIB_STRCAT_LEFT(str, "m");
    HLIB_STRCAT_LEFT(str, display_config);
    HLIB_STRCAT_LEFT(str, "\033[");
    HLIB_STRCAT(str, "\033[0m: ");
    HLIB_STRCAT(str, option->description);
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

struct LinkList *CommandMetaOptionsToString(
    struct CommandMetaOptions *options, int wrap_level, bool show_desc, const void *display_config)
{
  if (options == NULL)
    return NULL;
  if (display_config == DEFAULTARG)
    display_config = "1;36";
  struct LinkList *result;
  CLOSURE
  useClosure(show_desc);
  useClosure(wrap_level);
  useClosure(display_config);
  result = LinkListReduce(options->name->next, __CommandMetaOptionsReduceToString, NULL);
  ENDCLOSURE;
  return result;
}

#endif /* __HLIB_COMMANDS_META_OPTIONS */
