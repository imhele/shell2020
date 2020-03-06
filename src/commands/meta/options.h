#ifndef __HLIB_COMMANDS_META_OPTIONS
#define __HLIB_COMMANDS_META_OPTIONS

#include <string.h>
#include "../../utils/structs/map.h"

struct CommandMetaOptions
{
  struct Map *name;
  struct Map *alias;
};

struct CommandMetaOption
{
  char *name;
  char *alias;
  char *description;
  struct CommandMetaOptions *sub_options;
};

bool __CommandMetaOptionIsNameOrAliasEqual(void *a, void *b)
{
  return !strcmp((char *)a, (char *)b);
}

struct CommandMetaOptions *CommandMetaOptionsRegister(
    struct CommandMetaOptions *options, struct CommandMetaOption *option)
{
  if (options == NULL)
    options = HLIB_CALLOC(struct CommandMetaOptions);

  MapSet(options->name, option->name, option, __CommandMetaOptionIsNameOrAliasEqual);
  MapSet(options->alias, option->alias, option, __CommandMetaOptionIsNameOrAliasEqual);

  return options;
}

void CommandMetaOptionsFree(struct CommandMetaOptions **options);

void __CommandMetaOptionFreeEach(void *value, int index, struct Map *curr)
{
  struct CommandMetaOption *option = (struct CommandMetaOption *)value;
  if (option != NULL && option->sub_options != NULL)
    CommandMetaOptionsFree(&(option->sub_options));
}

void CommandMetaOptionsFree(struct CommandMetaOptions **options)
{
  if (options == NULL || *options == NULL)
    return;

  LinkListFreeEach(&((*options)->name), __CommandMetaOptionFreeEach);
  LinkListFreeEach(&((*options)->alias), __CommandMetaOptionFreeEach);

  *options = NULL;
}

#endif /* __HLIB_COMMANDS_META_OPTIONS */
