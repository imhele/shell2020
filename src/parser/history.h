#ifndef __HLIB_PARSER_HISTORY
#define __HLIB_PARSER_HISTORY

#include <stdio.h>
#include "../utils/helpers/file.h"
#include "../utils/path/join.h"
#include "variable.h"

#define __HLIB_PARSER_COMMAND_HISTORIES_MAX_RECORDS (256)

int __HLIB_PARSER_COMMAND_HISTORIES_TAIL = 0;
char *__HLIB_PARSER_COMMAND_HISTORIES_FILE = NULL;
char *__HLIB_PARSER_COMMAND_HISTORIES[__HLIB_PARSER_COMMAND_HISTORIES_MAX_RECORDS] = {0};

int ParserCommandHistoryGetNextIndex(int current, int offset)
{
  current += offset % __HLIB_PARSER_COMMAND_HISTORIES_MAX_RECORDS;
  if (current >= __HLIB_PARSER_COMMAND_HISTORIES_MAX_RECORDS)
    current -= __HLIB_PARSER_COMMAND_HISTORIES_MAX_RECORDS;
  else if (current < 0)
    current += __HLIB_PARSER_COMMAND_HISTORIES_MAX_RECORDS;
  return current;
}

void ParserCommandHistoryAdd(char *command)
{
  if (command == NULL)
    return;

  if (__HLIB_PARSER_COMMAND_HISTORIES[__HLIB_PARSER_COMMAND_HISTORIES_TAIL] != NULL)
    free(__HLIB_PARSER_COMMAND_HISTORIES[__HLIB_PARSER_COMMAND_HISTORIES_TAIL]);

  __HLIB_PARSER_COMMAND_HISTORIES[__HLIB_PARSER_COMMAND_HISTORIES_TAIL] =
      HLIB_CALLOC_N(char, strlen(command));
  strcpy(__HLIB_PARSER_COMMAND_HISTORIES[__HLIB_PARSER_COMMAND_HISTORIES_TAIL], command);

  __HLIB_PARSER_COMMAND_HISTORIES_TAIL =
      ParserCommandHistoryGetNextIndex(__HLIB_PARSER_COMMAND_HISTORIES_TAIL, 1);
}

void ParserCommandHistoryBootstrap()
{
  char *home = getenv("HOME");
  home = home == NULL ? "~/" : home;
  __HLIB_PARSER_COMMAND_HISTORIES_FILE = PathJoin(home, ".bash_history", ENDARG);
  FILE *fp = fopen(__HLIB_PARSER_COMMAND_HISTORIES_FILE, "r");
  if (fp != NULL)
  {
    for (char *cmd = FileGetOneLine(fp); !feof(fp); cmd = FileGetOneLine(fp))
      if (cmd[0] != '\0' && (cmd[0] != '\n' || cmd[1] != '\0'))
        ParserCommandHistoryAdd(cmd);
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
