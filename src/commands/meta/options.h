#ifndef __HLIB_COMMANDS_META_OPTIONS
#define __HLIB_COMMANDS_META_OPTIONS

#include "../../utils/helpers/closure.h"
#include "../../utils/helpers/string.h"
#include "../../utils/structs/map.h"

struct CommandMetaOptions
{
  struct Map *name;
  struct Map *alias;
};

struct CommandMetaOption
{
  char *alias;
  char *description;
  struct CommandMetaOptions *sub_options;
};

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

#endif /* __HLIB_COMMANDS_META_OPTIONS */
