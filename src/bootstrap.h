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

      char *buf;
      while (true)
      {
        buf = ParserTyping();
        ParserCommandHistoryAdd(buf);
        CommandExec(ParserParseCommand(buf));
      }
    }
    ENDSHELLCLOSURE;
  }
  ENDCLOSURE;
}

#endif /* __HLIB_BOOTSTRAP */
