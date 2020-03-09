#include "../../../main.h"

bool testPathClean()
{
  char *result;
  bool flag = true;

  result = PathClean("/Users/../Users/./imhele///Desktop");
  flag = flag && !strcmp(result, "/Users/imhele/Desktop");
  free(result);

  result = PathClean("Users/../Users/./imhele///Desktop/");
  flag = flag && !strcmp(result, "Users/imhele/Desktop/");
  free(result);

  return flag;
}

int main()
{
  HLIB_ASSERT_TEST(testPathClean);
  return 0;
}
