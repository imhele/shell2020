#ifndef __HLIB_COMMANDS_META_OPTIONS
#define __HLIB_COMMANDS_META_OPTIONS

#include <string.h>
#include "../../utils/structs/map.h"

struct CommandMetaOption
{
  char *name;
  char *alias;
  char *description;
  struct Map *sub_options;
};

struct CommandMetaOptions
{
  struct Map *name;
  struct Map *alias;
};

bool isCommandMetaOptionNameOrAliasEqual(void *a, void *b)
{
  return !strcmp((char *)a, (char *)b);
}

struct CommandMetaOptions *CommandMetaOptionsRegister(
    struct CommandMetaOptions *options, struct CommandMetaOption *option)
{
  if (options == NULL)
    options = HLIB_CALLOC(struct CommandMetaOptions);

  MapSet(options->name, option->name, option, isCommandMetaOptionNameOrAliasEqual);
  MapSet(options->alias, option->alias, option, isCommandMetaOptionNameOrAliasEqual);

  return options;
}

#endif /* __HLIB_COMMANDS_META_OPTIONS */
