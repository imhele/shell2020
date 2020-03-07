#ifndef __HLIB_UTILS_HELPERS_ASSERT
#define __HLIB_UTILS_HELPERS_ASSERT

#include <assert.h>
#include "../exceptions.h"
#include "../pretty/color.h"
#include "try.h"

#ifdef NASSERT_THROW
#define HLIB_ASSERT_THROW(ignore, message) ((void)0)
#else
#define HLIB_ASSERT_THROW(expression, message)                  \
  ({                                                            \
    if (!(expression))                                          \
    {                                                           \
      printf_color_str_endl(message, BGColorDefault, ColorRed); \
      THROW(EXCEPTION_ASSERT);                                  \
    }                                                           \
  })
#endif /* NASSERT_THROW */

#ifdef NASSERT_TEST
#define HLIB_ASSERT_TEST(ignore) ((void)0)
#else
#define HLIB_ASSERT_TEST(function)                        \
  TRY                                                     \
  {                                                       \
    assert(function());                                   \
    printf_color_str(" PASS ", BGColorGreen, ColorBlack); \
    printf(" " #function "\n");                           \
  }                                                       \
  ENDTRY;
#endif /* NASSERT_TEST */

#endif /* __HLIB_UTILS_HELPERS_ASSERT */
