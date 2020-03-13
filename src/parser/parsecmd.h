#ifndef __HLIB_PARSER_PARSECMD
#define __HLIB_PARSER_PARSECMD

#include "../utils/helpers/string.h"
#include "../utils/structs/bool.h"
#include "../utils/structs/linklist.h"
#include "typing.h"

struct ParsedCommand
{
  char *name;
  char **argv;
  // char **envp;
};

char **ParserParseCommandSplit(char *str)
{
  unsigned int count = 2;
  unsigned int len = strlen(str);
  char *quoted_flag = NULL;
  char *copied_str = HLIB_CALLOC_N(char, len + 1);
  char *copied_char = copied_str;

  for (char *curr_char = str; *curr_char != '\0'; curr_char++)
    if (*curr_char == 39 || *curr_char == 34)
    {
      if (quoted_flag == NULL)
        quoted_flag = curr_char;
      else if (*quoted_flag == *curr_char)
        quoted_flag = NULL;
      else
        *(copied_char++) = *curr_char;
    }
    else if (quoted_flag == NULL && *curr_char == ' ')
      count++, *(copied_char++) = '\0';
    else
      *(copied_char++) = *curr_char;

  char **result = HLIB_CALLOC_N(char *, count);
  for (unsigned int i = 0, j = 0; j < count - 1; i++, j++)
  {
    result[j] = copied_str + i;
    while (copied_str[i] != '\0')
      i++;
  }
  return result;
}

struct LinkList *ParserParseCommand(char *command)
{
  // bool env_flag = true;
  struct ParsedCommand *single_command = NULL;
  char **splited = ParserParseCommandSplit(command);
  struct LinkList *parsed_commands = LinkListPush(NULL, splited, ENDARG);

  for (char **segment = splited; *segment != NULL; segment++)
  {
    // if (env_flag) {}
    if (**segment == '\0')
      continue;

    if (!strcmp(*segment, "&&"))
    {
      if (single_command != NULL)
        parsed_commands = LinkListPush(parsed_commands, single_command, ENDARG);
      *segment = NULL;
      single_command = NULL;
      continue;
    }

    if (single_command == NULL)
      single_command = HLIB_CALLOC(struct ParsedCommand);

    if (!single_command->name)
      HLIB_STRCAT(single_command->name, *segment);
    else if (single_command->argv == NULL)
      single_command->argv = segment;
  }

  if (single_command != NULL)
    parsed_commands = LinkListPush(parsed_commands, single_command, ENDARG);

  return parsed_commands;
}

#endif /* __HLIB_PARSER_PARSECMD */
