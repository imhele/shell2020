#ifndef __HLIB_UTILS_HELPERS_ASSERT
#define __HLIB_UTILS_HELPERS_ASSERT

#include <assert.h>
#include "../exceptions.h"
#include "../pretty/terminal.h"
#include "try.h"

#ifdef NASSERT_THROW
#define HLIB_ASSERT_THROW(ignore, message) ((void)0)
#else
#define HLIB_ASSERT_THROW(expression, message)                                  \
  ({                                                                            \
    if (!(expression))                                                          \
    {                                                                           \
      HLIB_TERMINAL_PRINTF_ENDL(message, TERMINAL_HIGHLIGHT ";" TERMINAL_CRED); \
      THROW(EXCEPTION_ASSERT);                                                  \
    }                                                                           \
  })
#endif /* NASSERT_THROW */

#ifdef NASSERT_TEST
#define HLIB_ASSERT_TEST(ignore) ((void)0)
#else
#define HLIB_ASSERT_TEST(function)                                        \
  TRY                                                                     \
  {                                                                       \
    assert(function());                                                   \
    HLIB_TERMINAL_PRINTF(" PASS ", TERMINAL_REVERSE ";" TERMINAL_CGREEN); \
    printf(" " #function "\n");                                           \
  }                                                                       \
  ENDTRY;
#endif /* NASSERT_TEST */

#endif /* __HLIB_UTILS_HELPERS_ASSERT */
