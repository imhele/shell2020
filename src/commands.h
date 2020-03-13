#ifndef __HLIB_COMMANDS
#define __HLIB_COMMANDS

#include "commands/_exec.h"
#include "commands/_meta.h"
#include "commands/cd.h"
#include "commands/echo.h"
#include "commands/export.h"
#include "commands/pwd.h"
#include "commands/type.h"
#include "commands/unset.h"
#include "utils/helpers/closure.h"

void CommandsBootstrap()
{
  useSpecClosure("cd", CommandCD);
  useSpecClosure("echo", CommandEcho);
  useSpecClosure("export", CommandExport);
  useSpecClosure("pwd", CommandPWD);
  useSpecClosure("type", CommandType);
  useSpecClosure("unset", CommandUnset);

  CommandCDBootstrap();
  CommandEchoBootstrap();
  CommandExportBootstrap();
  CommandPWDBootstrap();
  CommandTypeBootstrap();
  CommandUnsetBootstrap();
}

void CommandsCleanup()
{
  CommandUnsetCleanup();
  CommandTypeCleanup();
  CommandPWDCleanup();
  CommandExportCleanup();
  CommandEchoCleanup();
  CommandCDCleanup();
}

#endif /* __HLIB_COMMANDS */
