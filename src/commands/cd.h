#ifndef __HLIB_COMMANDS_CD
#define __HLIB_COMMANDS_CD

#include <assert.h>
#include <string.h>
#include "../parser/cwd.h"
#include "../utils/path/clean.h"
#include "../utils/path/join.h"
#include "meta.h"

void CommandCD(char **argv, char **envp)
{
  char *path = argv == NULL ? NULL : (char *)*argv;

  if (path == NULL)
    path = ParserCWD();
  else if (!strcmp(path, "--help") || !strcmp(path, "-h"))
  {
    struct CommandMetaArgumentsMap *options = NULL;
    struct CommandMetaArgument argv_help = {0, "h", "Show the usage of command.", NULL};
    struct CommandMetaArgument argv_paths = {1, NULL, "Absolute or relative path.", NULL};
    options = CommandMetaArgumentRegister(options, "help", &argv_help);
    options = CommandMetaArgumentRegister(options, "path", &argv_paths);
    struct LinkList *usage = CommandMetaArgumentsMapToString(options, 0, true, DEFAULTARG);
    assert(usage != NULL);
    printf("cd: %s\n", (char *)usage->value);
    CommandMetaArgumentsMapFree(&options);
    LinkListFreeValue(&usage);
    return;
  }
  else if (path[0] == '~')
    path = PathJoin(ParserCWD(), path + 1, ENDARG);
  else
    path = PathClean(path);
  assert(chdir(path) == 0);
}

#endif /* __HLIB_COMMANDS_CD */
