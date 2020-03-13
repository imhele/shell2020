#ifndef __HLIB_PARSER_HISTORY
#define __HLIB_PARSER_HISTORY

#include <stdio.h>
#include "../utils/helpers/file.h"
#include "../utils/path/join.h"
#include "variable.h"

#define __HLIB_PARSER_COMMAND_HISTORIES_MAX_RECORDS (256)

int __HLIB_PARSER_COMMAND_HISTORIES_HEAD = 0;
char *__HLIB_PARSER_COMMAND_HISTORIES_FILE = NULL;
char *__HLIB_PARSER_COMMAND_HISTORIES[__HLIB_PARSER_COMMAND_HISTORIES_MAX_RECORDS] = {0};

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

void ParserCommandHistoryBootstrap()
{
  char *home = getenv("HOME");
  home = home == NULL ? "~/" : home;
  __HLIB_PARSER_COMMAND_HISTORIES_FILE = PathJoin(home, ".bash_history", ENDARG);
  FILE *fp = fopen(__HLIB_PARSER_COMMAND_HISTORIES_FILE, "r");
  if (fp != NULL)
  {
    while (!feof(fp))
      ParserCommandHistoryAdd(FileGetOneLine(fp));
    fclose(fp);
  }
}

void ParserCommandHistoryCleanup()
{
  for (int index = 0; index < __HLIB_PARSER_COMMAND_HISTORIES_MAX_RECORDS; index++)
    if (__HLIB_PARSER_COMMAND_HISTORIES[index] != NULL)
      free(__HLIB_PARSER_COMMAND_HISTORIES[index]);
}

#endif /* __HLIB_PARSER_HISTORY */
