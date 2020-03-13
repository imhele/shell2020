#ifndef __HLIB_COMMANDS
#define __HLIB_COMMANDS

#include "commands/_exec.h"
#include "commands/_meta.h"
#include "commands/cd.h"
#include "commands/echo.h"
#include "commands/enable.h"
#include "commands/export.h"
#include "commands/pwd.h"
#include "commands/type.h"
#include "commands/unset.h"
#include "utils/helpers/closure.h"
#include "utils/structs/map.h"

void *BuiltinCommandsMap[10][2] = {
    {"cd", CommandCD},
    {"echo", CommandEcho},
    {"enable", CommandEnable},
    {"export", CommandExport},
    {"pwd", CommandPWD},
    {"type", CommandType},
    {"unset", CommandUnset},
    {NULL, NULL},
};

void CommandsBootstrap()
{
  struct Map *__cmd_map = MapCreate(NULL);

  for (int i = 0; BuiltinCommandsMap[i][0] != NULL; i++)
  {
    useSpecClosure(BuiltinCommandsMap[i][0], BuiltinCommandsMap[i][1]);
    MapSet(__cmd_map, BuiltinCommandsMap[i][0], BuiltinCommandsMap[i][1], MapIsStringKeyEqual);
  }

  useSpecClosure("__cmd_map", __cmd_map);

  CommandCDBootstrap();
  CommandEchoBootstrap();
  CommandEnableBootstrap();
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
  CommandEnableCleanup();
  CommandEchoCleanup();
  CommandCDCleanup();
}

#endif /* __HLIB_COMMANDS */
