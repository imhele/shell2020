#ifndef __HLIB_PARSER_GETCH
#define __HLIB_PARSER_GETCH

#include <assert.h>
#include <stdlib.h>
#include <termios.h>
#include "../utils/structs/bool.h"

struct termios __HLIB_OLD_TERMIOS;
struct termios __HLIB_RAW_TERMIOS;
bool __HLIB_OLD_TERMIOS_FLAG = false;

void ParserGetCharPreset()
{
  if (!__HLIB_OLD_TERMIOS_FLAG)
  {
    assert(tcgetattr(0, &__HLIB_OLD_TERMIOS) >= 0);
    __HLIB_RAW_TERMIOS = __HLIB_OLD_TERMIOS;
    cfmakeraw(&__HLIB_RAW_TERMIOS);
    assert(tcsetattr(0, TCSANOW, &__HLIB_RAW_TERMIOS) >= 0);
    __HLIB_OLD_TERMIOS_FLAG = true;
  }
}

void ParserGetCharClean()
{
  if (__HLIB_OLD_TERMIOS_FLAG)
  {
    assert(tcsetattr(0, TCSANOW, &__HLIB_OLD_TERMIOS) >= 0);
    __HLIB_OLD_TERMIOS_FLAG = false;
  }
}

int ParserGetChar(void)
{
  ParserGetCharPreset();
  int ch = getchar();
  ParserGetCharClean();
  return ch;
}

#endif /* __HLIB_PARSER_GETCH */
