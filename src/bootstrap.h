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

      for (char *buf; (buf = ParserTyping()) != NULL;)
      {
        ParserCommandHistoryAdd(buf);
        CommandExec(ParserParseCommand(buf));
      }

      CommandsCleanup();
      ParserCommandHistoryCleanup();
      ParserVariableCleanup();

      HLIB_TERMINAL_PRINTF_ENDL("\nexit", TERMINAL_HIGHLIGHT);
    }
    ENDSHELLCLOSURE;
  }
  ENDCLOSURE;
}

#endif /* __HLIB_BOOTSTRAP */
