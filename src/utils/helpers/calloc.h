#ifndef __HLIB_UTILS_HELPERS_CALLOC
#define __HLIB_UTILS_HELPERS_CALLOC
#include <stdlib.h>

#define HLIB_MALLOC(type) ((type *)malloc(sizeof(type)))
#define HLIB_CALLOC(type) ((type *)calloc(1, sizeof(type)))
#define HLIB_CALLOC_N(type, n) ((type *)calloc(n, sizeof(type)))

#endif /* __HLIB_UTILS_HELPERS_CALLOC */
