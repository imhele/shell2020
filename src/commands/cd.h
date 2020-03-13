#ifndef __HLIB_COMMANDS_CD
#define __HLIB_COMMANDS_CD

#include <assert.h>
#include <string.h>
#include <unistd.h>
#include "../parser/variable.h"
#include "../utils/path/absolute.h"
#include "../utils/path/cwd.h"
#include "_meta.h"

int CommandCD(char **argv)
{
  char *path = argv == NULL ? NULL : *argv;

  if (path == NULL)
    path = PathCWD();
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
    return 0;
  }
  else
  {
    char *home = "~/";
    getShellVariable("HOME", home);
    path = PathAbsolute(path, home);
  }

  return chdir(path);
}

#endif /* __HLIB_COMMANDS_CD */
