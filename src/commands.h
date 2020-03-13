#ifndef __HLIB_COMMANDS
#define __HLIB_COMMANDS

#include "commands/_exec.h"
#include "commands/_meta.h"
#include "commands/cd.h"
#include "commands/pwd.h"
#include "commands/type.h"
#include "utils/helpers/closure.h"

void CommandsBootstrap()
{
  useSpecClosure("cd", CommandCD);
  useSpecClosure("pwd", CommandPWD);
  useSpecClosure("type", CommandType);

  CommandCDBootstrap();
  CommandPWDBootstrap();
  CommandTypeBootstrap();
}

void CommandsCleanup()
{
  CommandTypeCleanup();
  CommandPWDCleanup();
  CommandCDCleanup();
}

#endif /* __HLIB_COMMANDS */
