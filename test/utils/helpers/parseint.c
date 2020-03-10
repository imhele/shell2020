#include "../../../main.h"

bool testParseInt()
{
  int result;
  bool flag = true;

  result = ParseInt("abc");
  flag = flag && result == 0;

  result = ParseInt(" 123");
  flag = flag && result == 123;

  result = ParseInt("-123j ");
  flag = flag && result == -123;

  result = ParseInt("+123x133");
  flag = flag && result == 123;

  return flag;
}

int main()
{
  HLIB_ASSERT_TEST(testParseInt);
  return 0;
}
