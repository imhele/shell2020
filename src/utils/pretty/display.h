#ifndef __HLIB_UTILS_PRETTY_DISPLAY
#define __HLIB_UTILS_PRETTY_DISPLAY

#include <stdio.h>

#define DColorDefault "0"
#define DColorBlack "30"
#define DColorRed "31"
#define DColorGreen "32"
#define DColorBrown "33"
#define DColorBlue "34"
#define DColorPurple "35"
#define DColorCyan "36"
#define DColorWhite "37"

#define DBColorDefault "0"
#define DBColorBlack "40"
#define DBColorRed "41"
#define DBColorGreen "42"
#define DBColorBrown "43"
#define DBColorBlue "44"
#define DBColorPurple "45"
#define DBColorCyan "46"
#define DBColorWhite "47"

#define DModeDefault "0"
#define DModeHighlight "1"
#define DModeUnderline "4"
#define DModeFlash "5"
#define DModeReverse "7"
#define DModeHidden "8"

#define HLIB_DISPLAY(str, config) "\033[" config "m" str "\033[0m"

#define HLIB_DISPLAY_PRINTF(str, config) printf(HLIB_DISPLAY(str, config))

#define HLIB_DISPLAY_PRINTF_ENDL(str, config) printf(HLIB_DISPLAY(str, config) "\n")

#endif /* __HLIB_UTILS_PRETTY_DISPLAY */
