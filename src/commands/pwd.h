#ifndef __HLIB_COMMANDS_PWD
#define __HLIB_COMMANDS_PWD

#include "../utils/path/cwd.h"
#include "_meta.h"

int CommandPWD(char **argv)
{
  char *cwd = PathCWD();
  puts(cwd);
  free(cwd);
  return 0;
}

void CommandPWDBootstrap()
{
  return;
}

void CommandPWDCleanup()
{
  return;
}

#endif /* __HLIB_COMMANDS_PWD */
