#ifndef __HLIB_COMMANDS_ENABLE
#define __HLIB_COMMANDS_ENABLE

#include <assert.h>
#include <stdlib.h>
#include "../utils/helpers/closure.h"
#include "../utils/pretty/terminal.h"
#include "../utils/structs/bool.h"
#include "../utils/structs/map.h"
#include "_meta.h"

int CommandEnable(char **argv)
{
  void *builtin_cmd;
  bool all_flag = false;
  bool list_flag = true;
  bool help_flag = false;
  bool disable_flag = false;
  struct Map *__cmd_map = NULL;
  struct MapItem *__cmd_map_item;
  useSpecClosureValue("__cmd_map", __cmd_map);
  assert(__cmd_map != NULL);

  if (argv != NULL)
    for (char **curr_argv = argv; *curr_argv != NULL; curr_argv++)
    {
      if (*curr_argv[0] == '\0')
        continue;

      if (*curr_argv[0] != '-')
      {
        list_flag = false;
        continue;
      }

      if (!strcmp(*curr_argv, "--disable") || !strcmp(*curr_argv, "-n"))
      {
        disable_flag = true;
        continue;
      }

      if (!strcmp(*curr_argv, "--list") || !strcmp(*curr_argv, "-a"))
      {
        all_flag = list_flag = true;
        break;
      }

      if (!strcmp(*curr_argv, "--help") || !strcmp(*curr_argv, "-h"))
      {
        help_flag = true;
        break;
      }

      list_flag = false;
    }

  if (help_flag)
  {
    struct CommandMetaArgumentsMap *enable_meta = NULL;
    useSpecClosureValue("__enable_meta", enable_meta);
    struct LinkList *usage = CommandMetaArgumentsMapToString(enable_meta, 1, true, DEFAULTARG);
    assert(usage != NULL);
    printf("usage of %s:\n", HLIB_TERMINAL_STRING("enable", TERMINAL_HIGHLIGHT));
    for (int index = LinkListLength(usage); index--;)
      printf("\t%s\n", (char *)LinkListGetter(usage, index));
    LinkListFreeValue(&usage);
    return 0;
  }

  if (list_flag || argv == NULL)
  {
    while ((__cmd_map = __cmd_map->next) != NULL)
    {
      builtin_cmd = NULL;
      __cmd_map_item = (struct MapItem *)__cmd_map->value;
      useSpecClosureValue(__cmd_map_item->key, builtin_cmd);
      if (builtin_cmd != NULL)
        printf("enable %s\n", (char *)__cmd_map_item->key);
      else if (all_flag)
        printf("enable -n %s\n", (char *)__cmd_map_item->key);
    }
    return 0;
  }

  for (char **curr_argv = argv; *curr_argv != NULL; curr_argv++)
  {
    struct MapItem *cmd_record = MapGet(__cmd_map, *curr_argv, MapIsStringKeyEqual);

    if (cmd_record == NULL || cmd_record->value == NULL)
      continue;

    builtin_cmd = NULL;
    useSpecClosureValue(*curr_argv, builtin_cmd);

    if (builtin_cmd != NULL)
    {
      if (disable_flag)
        useSpecClosure(*curr_argv, NULL);
    }
    else
    {
      if (!disable_flag)
        useSpecClosure(*curr_argv, cmd_record->value);
    }
  }

  return 0;
}

struct CommandMetaArgument __COMMAND_ENABLE_META_ARG_HELP =
    {0, "h", "Show the usage of command.", NULL};
struct CommandMetaArgument __COMMAND_ENABLE_META_ARG_ALL =
    {0, "a", "List enabled and disabled builtin commands.", NULL};
struct CommandMetaArgument __COMMAND_ENABLE_META_ARG_DISABLE =
    {0, "n", "Disable specific builtin commands.", NULL};
struct CommandMetaArgument __COMMAND_ENABLE_META_ARG_CMDS =
    {2, NULL, "Any builtin commands.", NULL};

void CommandEnableBootstrap()
{
  struct CommandMetaArgumentsMap *enable_meta = NULL;
  enable_meta = CommandMetaArgumentRegister(enable_meta, "help", &__COMMAND_ENABLE_META_ARG_HELP);
  enable_meta = CommandMetaArgumentRegister(enable_meta, "all", &__COMMAND_ENABLE_META_ARG_ALL);
  enable_meta = CommandMetaArgumentRegister(enable_meta, "disable", &__COMMAND_ENABLE_META_ARG_DISABLE);
  enable_meta = CommandMetaArgumentRegister(enable_meta, "commands", &__COMMAND_ENABLE_META_ARG_CMDS);

  useSpecClosure("__enable_meta", enable_meta);
}

void CommandEnableCleanup()
{
  struct CommandMetaArgumentsMap *enable_meta = NULL;
  useSpecClosureValue("__enable_meta", enable_meta);
  if (enable_meta != NULL)
    CommandMetaArgumentsMapFree(&enable_meta);
}

#endif /* __HLIB_COMMANDS_ENABLE */
