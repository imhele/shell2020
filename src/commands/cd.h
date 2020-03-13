#ifndef __HLIB_COMMANDS_CD
#define __HLIB_COMMANDS_CD

#include <assert.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "../parser/variable.h"
#include "../utils/path/join.h"
#include "../utils/path/startswithhome.h"
#include "_meta.h"

int CommandCD(char **argv)
{
  char *home = NULL;
  struct stat path_stat;
  char *path = argv == NULL ? NULL : *argv;

  if (path == NULL || path[0] == '\0')
  {
    getShellVariable("HOME", home);
    if (home != NULL)
    {
      if (PrintAccessError(access(home, R_OK)))
      {
        free(home);
        return -1;
      }

      chdir(home);
      free(home);
      return 0;
    }

    path = "--help";
  }

  if (!strcmp(path, "--help") || !strcmp(path, "-h"))
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

  if (PathStartsWithHome(path))
  {
    getShellVariable("HOME", home);
    if (home == NULL)
    {
      printf("cd: environment variable 'HOME' does not exist, unable to locate.");
      return -1;
    }

    path = PathJoin(home, path + 1, ENDARG);

    if (PrintAccessError(access(path, R_OK)))
    {
      free(path);
      free(home);
      return -1;
    }

    chdir(path);
    free(path);
    free(home);
    return 0;
  }

  if (PrintAccessError(access(path, R_OK)))
    return -1;

  return chdir(path);
}

#endif /* __HLIB_COMMANDS_CD */
