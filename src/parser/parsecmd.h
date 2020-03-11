#ifndef __HLIB_PARSER_PARSECMD
#define __HLIB_PARSER_PARSECMD

#include "../utils/structs/map.h"
#include "typing.h"

struct ParsedCommand
{
  char *name;
  char **argv;
  char **envp;
};

#endif /* __HLIB_PARSER_PARSECMD */
