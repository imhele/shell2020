#ifndef __HLIB_COMMANDS_EXPORT
#define __HLIB_COMMANDS_EXPORT

#include <stdlib.h>
#include "../utils/helpers/string.h"
#include "_meta.h"

int CommandExport(char **argv)
{
  for (; *argv != NULL; argv++)
    putenv(HLIB_STRREPEAT(*argv, 1));
  return 0;
}

void CommandExportBootstrap()
{
  return;
}

void CommandExportCleanup()
{
  return;
}

#endif /* __HLIB_COMMANDS_EXPORT */
