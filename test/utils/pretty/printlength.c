#include "../../../main.h"

bool testGetUnicodePrintLength()
{
  bool flag = true;
  flag = flag && GetUnicodePrintLength("") == 0;
  flag = flag && GetUnicodePrintLength("abc") == 3;
  flag = flag && GetUnicodePrintLength("何乐def") == 7;
  flag = flag && GetUnicodePrintLength("ghi😂") == 5;
  return flag;
}

int main()
{
  HLIB_ASSERT_TEST(testGetUnicodePrintLength);
  return 0;
}
