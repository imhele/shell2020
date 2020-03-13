#ifndef __HLIB_COMMANDS
#define __HLIB_COMMANDS

#include "commands/_exec.h"
#include "commands/cd.h"
#include "commands/_meta.h"
#include "commands/type.h"
#include "utils/helpers/closure.h"

void CommandsBootstrap()
{
  useSpecClosure("cd", CommandCD);
  useSpecClosure("type", CommandType);
}

void CommandsCleanup()
{
  return;
}

#endif /* __HLIB_COMMANDS */
