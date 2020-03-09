#ifndef __HLIB_PARSER_PS1
#define __HLIB_PARSER_PS1

#include <libgen.h>
#include <unistd.h>
#include "../utils/helpers/string.h"
#include "cwd.h"
#include "variable.h"

char *ParserPS1()
{
  char *ps1_var = NULL;
  char *user_var = NULL;
  // char *host_var = NULL;
  char *cwd = ParserCWD();
  char *dir = basename(cwd);
  getShellVariable("PS1", ps1_var);
  getShellVariable("USER", user_var);
  // getShellVariable("HOSTNAME", host_var);
  char *user = user_var == NULL ? "UNKNOWN" : user_var;
  // char *host = host_var == NULL ? "UNKNOWN" : host_var;
  char *ps1 = ps1_var == NULL ? "[\\u \\W]$ " : ps1_var;
  unsigned long dir_len = strlen(dir);
  unsigned long user_len = strlen(user);
  // unsigned long host_len = strlen(host);
  char *result = HLIB_CALLOC_N(char, dir_len + user_len + strlen(ps1));
  for (char *i = ps1, *j = result; *i != '\0'; i++, j++)
  {
    if (*i == '\\')
      switch (*(i + 1))
      {
      // case 'h':
      //   strcpy(j, host);
      //   j += host_len - 1, i++;
      //   break;
      case 'W':
        strcpy(j, dir);
        j += dir_len - 1, i++;
        break;
      case 'u':
        strcpy(j, user);
        j += user_len - 1, i++;
        break;
      default:
        j--;
        break;
      }
    else
      *j = *i;
  }
  free(cwd);
  if (user_var != NULL)
    free(user_var);
  // if (host_var != NULL)
  //   free(host_var);
  if (ps1_var != NULL)
    free(ps1_var);
  return result;
}

#endif /* __HLIB_PARSER_PS1 */