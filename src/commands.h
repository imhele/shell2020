#ifndef __HLIB_COMMANDS
#define __HLIB_COMMANDS

#include "commands/_exec.h"
#include "commands/cd.h"
#include "commands/meta.h"
#include "commands/type.h"
#include "utils/helpers/closure.h"

void CommandsBootstrap()
{
  useSpecClosure("cd", CommandCD);
  useSpecClosure("type", CommandType);
}

#endif /* __HLIB_COMMANDS */
