#ifndef __HLIB_BOOTSTRAP
#define __HLIB_BOOTSTRAP

#include "commands.h"
#include "parser.h"
#include "utils.h"

void ShellBootstrap()
{
  SHELLCLOSURE
  {
    __HLIB_PARSER_VARIABLE_BOOTSTRAP();
    __HLIB_PARSER_COMMAND_HISTORY_BOOTSTRAP();
  }
  ENDSHELLCLOSURE;
}

#endif /* __HLIB_BOOTSTRAP */
