#ifndef __HLIB_PARSER_HISTORY
#define __HLIB_PARSER_HISTORY

#include <stdio.h>
#include "../utils/helpers/file.h"
#include "../utils/path/join.h"
#include "variable.h"

int __HLIB_PARSER_COMMAND_HISTORIES_HEAD = 0;
char *__HLIB_PARSER_COMMAND_HISTORIES_FILE = NULL;
char *__HLIB_PARSER_COMMAND_HISTORIES[256] = {0};

void ParserCommandHistoryAdd(char *command)
{
  if (command == NULL)
    return;
  if (__HLIB_PARSER_COMMAND_HISTORIES_HEAD > 255)
    __HLIB_PARSER_COMMAND_HISTORIES_HEAD = 0;

  if (__HLIB_PARSER_COMMAND_HISTORIES[__HLIB_PARSER_COMMAND_HISTORIES_HEAD] != NULL)
    free(__HLIB_PARSER_COMMAND_HISTORIES[__HLIB_PARSER_COMMAND_HISTORIES_HEAD]);

  __HLIB_PARSER_COMMAND_HISTORIES[__HLIB_PARSER_COMMAND_HISTORIES_HEAD] =
      HLIB_CALLOC_N(char, strlen(command));
  strcpy(__HLIB_PARSER_COMMAND_HISTORIES[__HLIB_PARSER_COMMAND_HISTORIES_HEAD], command);

  __HLIB_PARSER_COMMAND_HISTORIES_HEAD++;
}

void __HLIB_PARSER_COMMAND_HISTORY_BOOTSTRAP()
{
  char *home = "~/";
  getShellVariable("HOME", home);
  __HLIB_PARSER_COMMAND_HISTORIES_FILE = PathJoin(home, ".bash_history", ENDARG);
  FILE *fp = fopen(__HLIB_PARSER_COMMAND_HISTORIES_FILE, "r");
  if (fp != NULL)
  {
    while (!feof(fp))
      ParserCommandHistoryAdd(FileGetOneLine(fp));
    fclose(fp);
  }
}

#endif /* __HLIB_PARSER_HISTORY */
