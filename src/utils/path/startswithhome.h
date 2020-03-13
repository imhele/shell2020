#ifndef __HLIB_UTILS_PATH_STARTSWITHHOME
#define __HLIB_UTILS_PATH_STARTSWITHHOME

#include "clean.h"
#include "cwd.h"
#include "join.h"
#include "../structs/bool.h"

bool PathStartsWithHome(char *path)
{
  return path[0] == '~' && (path[1] == '/' || path[1] == '\0');
}

#endif /* __HLIB_UTILS_PATH_STARTSWITHHOME */
