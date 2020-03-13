#ifndef __HLIB_COMMANDS_UNSET
#define __HLIB_COMMANDS_UNSET

#include <stdlib.h>
#include "../utils/helpers/string.h"
#include "_meta.h"

int CommandUnset(char **argv)
{
  for (; *argv != NULL; argv++)
    unsetenv(*argv);
  return 0;
}

void CommandUnsetBootstrap()
{
  return;
}

void CommandUnsetCleanup()
{
  return;
}

#endif /* __HLIB_COMMANDS_UNSET */
