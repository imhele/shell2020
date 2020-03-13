#ifndef __HLIB_COMMANDS_TYPE
#define __HLIB_COMMANDS_TYPE

#include <assert.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../utils/helpers/closure.h"
#include "../utils/helpers/string.h"
#include "../utils/path/join.h"
#include "../utils/structs/bool.h"
#include "_meta.h"

char *CommandTypeGetPath(char *name)
{
  char *PATH = getenv("PATH");
  struct dirent *curr_dirent;

  if (PATH != NULL)
  {
    char **PATHS = HLIB_STRSPLIT(PATH, ':');
    for (char **curr_path = PATHS; *curr_path != NULL; curr_path++)
      for (DIR *directory = opendir(*curr_path); (curr_dirent = readdir(directory)) != NULL;)
        if (!strcmp(curr_dirent->d_name, name))
        {
          name = PathJoin(*curr_path, name, ENDARG);
          free(*PATHS);
          free(PATHS);
          return name;
        }

    free(*PATHS);
    free(PATHS);
  }

  return NULL;
}

ShellBuiltinCommand CommandTypeGetBuiltin(char *name)
{
  ShellBuiltinCommand builtin_command = NULL;
  useSpecClosureValue(name, builtin_command);
  return builtin_command;
}

bool CommandTypeMaybeFile(char *name)
{
  return name[0] == '/' || (name[0] == '.' && name[1] != '\0');
}

int CommandType(char **argv)
{
  char *name = argv == NULL ? NULL : *argv;

  if (name == NULL || !strcmp(name, "--help") || !strcmp(name, "-h"))
  {
    struct CommandMetaArgumentsMap *type_meta = NULL;
    useSpecClosureValue("__type_meta", type_meta);
    struct LinkList *usage = CommandMetaArgumentsMapToString(type_meta, 0, true, DEFAULTARG);
    assert(usage != NULL);
    printf("type: %s\n", (char *)usage->value);
    LinkListFreeValue(&usage);
    return 0;
  }

  if (CommandTypeMaybeFile(name))
  {
    if (PrintAccessError("type", name, X_OK))
      return -1;
    printf("%s is %s\n", name, name);
    return 0;
  }

  if (CommandTypeGetBuiltin(name) != NULL)
    return printf("%s is a shell builtin\n", name);

  char *path = CommandTypeGetPath(name);
  if (path == NULL)
    return printf("%s: not found\n", name);
  printf("%s is %s\n", name, path);
  free(path);
  return 0;
}

struct CommandMetaArgument __COMMAND_TYPE_META_ARG_HELP = {0, "h", "Show the usage of command.", NULL};
struct CommandMetaArgument __COMMAND_TYPE_META_ARG_PATH = {1, NULL, "Any path or global command.", NULL};

void CommandTypeBootstrap()
{
  struct CommandMetaArgumentsMap *type_meta = NULL;
  type_meta = CommandMetaArgumentRegister(type_meta, "help", &__COMMAND_TYPE_META_ARG_HELP);
  type_meta = CommandMetaArgumentRegister(type_meta, "path", &__COMMAND_TYPE_META_ARG_PATH);

  useSpecClosure("__type_meta", type_meta);
}

void CommandTypeCleanup()
{
  struct CommandMetaArgumentsMap *type_meta = NULL;
  useSpecClosureValue("__type_meta", type_meta);
  if (type_meta != NULL)
    CommandMetaArgumentsMapFree(&type_meta);
}

#endif /* __HLIB_COMMANDS_TYPE */
