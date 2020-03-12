#ifndef __HLIB_COMMANDS_EXEC
#define __HLIB_COMMANDS_EXEC

#include <unistd.h>
#include "../parser/parsecmd.h"
#include "type.h"

int __CommandExecSingle(struct ParsedCommand *parsed_command)
{
  int exit_code = 0;
  char *command_path = NULL;
  if (!CommandTypeMaybeFile(parsed_command->name))
  {
    ShellBuiltinCommand builtin = CommandTypeGetBuiltin(parsed_command->name);
    if (builtin != NULL)
      return builtin(parsed_command->argv);
    command_path = CommandTypeGetPath(parsed_command->name);
  }

  if (command_path == NULL)
    command_path = parsed_command->name;

  if (fork())
    wait(&exit_code), exit_code = WEXITSTATUS(exit_code);
  else
    exit(execvp(command_path, parsed_command->argv));

  if (exit_code > 1)
    printf("%s: exit with code %d.\n", parsed_command->name, exit_code);

  return exit_code;
}

void CommandExec(struct LinkList *parsed_commands)
{
  if (parsed_commands == NULL)
    return;

  int exit_code = 0;
  char **splited = (char **)parsed_commands->value;
  struct LinkList *curr_command = (struct LinkList *)parsed_commands;

  while (!exit_code && (curr_command = curr_command->next) != NULL)
    exit_code = __CommandExecSingle((struct ParsedCommand *)curr_command->value);

  free(*splited);
  LinkListFreeValue(&parsed_commands);
}

#endif /* __HLIB_COMMANDS_EXEC */
