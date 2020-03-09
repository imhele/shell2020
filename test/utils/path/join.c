#include "../../../main.h"

bool testPathJoin()
{
  char *result;
  bool flag = true;

  result = PathJoin("/Users/", "../", "Users/", "./imhele///Desktop", ENDARG);
  flag = flag && !strcmp(result, "/Users/imhele/Desktop");
  free(result);

  result = PathJoin("../", "./imhele///Desktop/", ENDARG);
  flag = flag && !strcmp(result, "../imhele/Desktop/");
  free(result);

  return flag;
}

int main()
{
  HLIB_ASSERT_TEST(testPathJoin);
  return 0;
}
