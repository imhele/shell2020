#ifndef __HLIB_UTILS_PATH_ABSOLUTE
#define __HLIB_UTILS_PATH_ABSOLUTE

#include "clean.h"
#include "cwd.h"
#include "join.h"

char *PathAbsolute(char *path, char *home)
{
  if (path == NULL)
    return PathCWD();
  if (path[0] == '/')
    return PathClean(path);
  if (path[0] == '~')
    return PathJoin(home, path + 1, ENDARG);
  return PathJoin(PathCWD(), path, ENDARG);
}

#endif /* __HLIB_UTILS_PATH_ABSOLUTE */
