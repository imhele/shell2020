#ifndef __HLIB_COMMANDS__META_ACCESS
#define __HLIB_COMMANDS__META_ACCESS

#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include "../../utils/structs/bool.h"

char *__AccessModeTestFailedMessage[5] = {
    "target not exists",
    "file is not executable or directory is inaccessible",
    "target is not writable",
    "cannot access target",
    "target is not readable",
};

bool PrintAccessError(char *prefix, char *path, int mode)
{
  if (access(path, mode) == 0)
    return false;

  switch (errno)
  {
  case EINVAL:
    printf("%s: invalid access mode.\n", prefix);
    break;
  case EACCES:
    printf("%s: %s.\n", prefix, __AccessModeTestFailedMessage[mode]);
    break;
  case ELOOP:
    printf("%s: too many symbolic link.\n", prefix);
    break;
  case ENAMETOOLONG:
    printf("%s: name is too long.\n", prefix);
    break;
  case ENOENT:
    printf("%s: target not found.\n", prefix);
    break;
  case ENOTDIR:
    printf("%s: target is not a directory.\n", prefix);
    break;
  case EROFS:
    printf("%s: file system is readonly.\n", prefix);
    break;
  case EFAULT:
    printf("%s: target is out of reach.\n", prefix);
    break;
  case EIO:
    printf("%s: i/o failed.\n", prefix);
    break;
  case ENOMEM:
    printf("%s: cannot get enough kernel memory.\n", prefix);
    break;
  case ETXTBSY:
    printf("%s: write to program failed.\n", prefix);
    break;
  default:
    printf("%s: unknown error.\n", prefix);
    break;
  }

  return true;
}

#endif /* __HLIB_COMMANDS__META_ACCESS */
