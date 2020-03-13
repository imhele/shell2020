#ifndef __HLIB_COMMANDS_ECHO
#define __HLIB_COMMANDS_ECHO

#include <stdlib.h>
#include "../utils/helpers/string.h"
#include "_meta.h"

int CommandEcho(char **argv)
{
  for (; *argv != NULL; argv++)
    printf("%s%s", *argv, *argv[0] == '\0' || argv[1] == NULL ? "" : " ");
  putchar('\n');
  return 0;
}

void CommandEchoBootstrap()
{
  return;
}

void CommandEchoCleanup()
{
  return;
}

#endif /* __HLIB_COMMANDS_ECHO */
