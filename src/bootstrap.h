#ifndef __HLIB_BOOTSTRAP
#define __HLIB_BOOTSTRAP

#include "commands.h"
#include "parser.h"
#include "utils.h"

void ShellBootstrap()
{
  CLOSURE
  {
    SHELLCLOSURE
    {
      ParserVariableBootstrap();
      ParserCommandHistoryBootstrap();
      CommandsBootstrap();
    }
    ENDSHELLCLOSURE;
  }
  ENDCLOSURE;
}

#endif /* __HLIB_BOOTSTRAP */
