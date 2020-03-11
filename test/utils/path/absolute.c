#include "../../../main.h"

bool testPathAbsolute()
{
  char *result;
  bool flag = true;

  result = PathAbsolute("~/Desktop", "/Users/imhele");
  flag = flag && !strcmp(result, "/Users/imhele/Desktop");
  free(result);

  result = PathAbsolute("/dev/null", "/Users/imhele");
  flag = flag && !strcmp(result, "/dev/null");
  free(result);

  return flag;
}

int main()
{
  HLIB_ASSERT_TEST(testPathAbsolute);
  return 0;
}
