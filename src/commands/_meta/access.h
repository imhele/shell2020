#ifndef __HLIB_COMMANDS__META_ACCESS
#define __HLIB_COMMANDS__META_ACCESS

#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include "../../utils/structs/bool.h"

bool PrintAccessError(int code)
{
  if (code == 0)
    return false;

  switch (errno)
  {
  case EINVAL:
    puts("access: invalid access mode.");
    break;
  case EACCES:
    puts("access: cannot access target.");
    break;
  case ELOOP:
    puts("access: too many symbolic link.");
    break;
  case ENAMETOOLONG:
    puts("access: name is too long.");
    break;
  case ENOENT:
    puts("access: target not found.");
    break;
  case ENOTDIR:
    puts("access: target is not a directory.");
    break;
  case EROFS:
    puts("access: file system is readonly.");
    break;
  case EFAULT:
    puts("access: target is out of reach.");
    break;
  case EIO:
    puts("access: i/o failed.");
    break;
  case ENOMEM:
    puts("access: cannot get enough kernel memory.");
    break;
  case ETXTBSY:
    puts("access: write to program failed.");
    break;
  default:
    puts("access: unknown error.");
    break;
  }

  return true;
}

#endif /* __HLIB_COMMANDS__META_ACCESS */
