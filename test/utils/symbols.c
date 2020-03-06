#include "../../main.h"

const void *TEST = (void *)&"TEST";

bool testSymbolNotEqual()
{
  bool flag = true;
  flag = flag && ENDARG != TEST;
  flag = flag && ENDARG != DEFAULTARG;
  return flag;
}

int main()
{
  HLIB_ASSERT_TEST(testSymbolNotEqual);
}
