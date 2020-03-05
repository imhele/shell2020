#ifndef __HLIB_UTILS_HELPERS_TRY
#define __HLIB_UTILS_HELPERS_TRY

#include <stdio.h>
#include <setjmp.h>

#define TRY                    \
  do                           \
  {                            \
    jmp_buf __jpm_buf;         \
    switch (setjmp(__jpm_buf)) \
    {                          \
    case 0:                    \
      while (1)                \
      {

#define CATCH(exception) \
  break;                 \
  case exception:

#define FINALLY \
  break;        \
  }             \
  default:      \
  {

#define ENDTRY \
  break;       \
  }            \
  }            \
  }            \
  while (0)

#define THROW(exception) longjmp(__jpm_buf, exception)

#endif /* __HLIB_UTILS_HELPERS_TRY */
