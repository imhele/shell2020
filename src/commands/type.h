#ifndef __HLIB_COMMANDS_TYPE
#define __HLIB_COMMANDS_TYPE

#include <assert.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include "../parser/variable.h"
#include "../utils/helpers/closure.h"
#include "../utils/helpers/string.h"
#include "../utils/path/join.h"

char *CommandTypeGetPath(char *name)
{
  char *PATH = NULL;
  struct dirent *curr_dirent;
  getShellVariable("PATH", PATH);

  if (PATH != NULL)
  {
    char **PATHS = HLIB_STRSPLIT(PATH, ':');
    for (char **curr_path = PATHS; *curr_path != NULL; curr_path++)
      for (DIR *directory = opendir(*curr_path); (curr_dirent = readdir(directory)) != NULL;)
        if (!strcmp(curr_dirent->d_name, name))
        {
          name = PathJoin(*curr_path, name, ENDARG);
          free(PATH), free(*PATHS), free(PATHS);
          return name;
        }
    free(PATH), free(*PATHS), free(PATHS), PATH = NULL;
  }

  return NULL;
}

int CommandType(char **argv)
{
  char *name = argv == NULL ? NULL : *argv;

  if (name == NULL)
    return putchar('\n');

  int (*internal_command)(char **argv) = NULL;
  useSpecClosureValue(name, internal_command);
  if (internal_command != NULL)
    return printf("%s is a shell builtin\n", name);

  char *path = CommandTypeGetPath(name);
  if (path == NULL)
    return printf("%s: not found\n", name);
  printf("%s is %s\n", name, path);
  free(path);
  return 0;
}

#endif /* __HLIB_COMMANDS_TYPE */
