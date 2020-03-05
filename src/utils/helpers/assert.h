#ifndef __HLIB_UTILS_HELPERS_ASSERT
#define __HLIB_UTILS_HELPERS_ASSERT

#include "../exceptions.h"
#include "../pretty/color.h"
#include "./try.h"

#ifdef NASSERT
#define HLIB_ASSERT_MSG(ignore) ((void)0)
#else
#define HLIB_ASSERT_MSG(expression, message)               \
  ({                                                       \
    if (!(expression))                                     \
    {                                                      \
      printf_color_str(message, BGColorDefault, ColorRed); \
      THROW(EXCEPTION_ASSERT);                             \
    }                                                      \
  })
#endif /* NASSERT */

#endif /* __HLIB_UTILS_HELPERS_ASSERT */
