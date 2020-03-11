#ifndef __HLIB_UTILS_PRETTY_PRINTLENGTH
#define __HLIB_UTILS_PRETTY_PRINTLENGTH

unsigned long GetUnicodePrintLength(char *str)
{
  unsigned char bit;
  unsigned long length = 0;
  for (unsigned long index = 0; str[index]; index++)
  {
    for (bit = 0; bit < 7 && ((unsigned char)str[index] & (1 << (7 - bit)));)
      if (!((unsigned char)str[index + bit++] & 0x80))
      {
        bit = 0;
        break;
      }
    if (bit > 1)
      index += bit - 1, length += 2;
    else
      length++;
  }

  return length;
}

#endif /* __HLIB_UTILS_PRETTY_WINDOWSIZE */
