#ifndef __HLIB_PARSER_PS1
#define __HLIB_PARSER_PS1

#include <libgen.h>
#include <unistd.h>
#include "../utils/helpers/string.h"
#include "../utils/path/cwd.h"
#include "variable.h"

char *ParserPS1()
{
  char *cwd = PathCWD();
  char *ps1 = getenv("PS1");
  char *home = getenv("HOME");
  char *user = getenv("USER");
  // char *host = getenv("HOSTNAME");

  ps1 = ps1 == NULL ? "[\\u \\W]$ " : ps1;
  user = user == NULL ? "UNKNOWN" : user;
  // host = host == NULL ? "UNKNOWN" : host;
  char *dir = home != NULL && !strcmp(home, cwd) ? "~" : basename(cwd);

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
  return result;
}

#endif /* __HLIB_PARSER_PS1 */
