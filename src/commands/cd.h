#ifndef __HLIB_COMMANDS_CD
#define __HLIB_COMMANDS_CD

#include <assert.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "../parser/variable.h"
#include "../utils/helpers/closure.h"
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
      if (PrintAccessError("cd", home, X_OK))
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
    struct CommandMetaArgumentsMap *cd_meta = NULL;
    useSpecClosureValue("__cd_meta", cd_meta);
    struct LinkList *usage = CommandMetaArgumentsMapToString(cd_meta, 0, true, DEFAULTARG);
    assert(usage != NULL);
    printf("cd: %s\n", (char *)usage->value);
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

    if (PrintAccessError("cd", path, X_OK))
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

  if (PrintAccessError("cd", path, X_OK))
    return -1;

  return chdir(path);
}

struct CommandMetaArgument __COMMAND_CD_META_ARG_HELP = {0, "h", "Show the usage of command.", NULL};
struct CommandMetaArgument __COMMAND_CD_META_ARG_PATH = {1, NULL, "Absolute or relative path.", NULL};

void CommandCDBootstrap()
{
  struct CommandMetaArgumentsMap *cd_meta = NULL;
  cd_meta = CommandMetaArgumentRegister(cd_meta, "help", &__COMMAND_CD_META_ARG_HELP);
  cd_meta = CommandMetaArgumentRegister(cd_meta, "path", &__COMMAND_CD_META_ARG_PATH);

  useSpecClosure("__cd_meta", cd_meta);
}

void CommandCDCleanup()
{
  struct CommandMetaArgumentsMap *cd_meta = NULL;
  useSpecClosureValue("__cd_meta", cd_meta);
  if (cd_meta != NULL)
    CommandMetaArgumentsMapFree(&cd_meta);
}

#endif /* __HLIB_COMMANDS_CD */
