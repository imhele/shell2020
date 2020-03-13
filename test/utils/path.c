#include "../../main.h"

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

bool testPathStartsWithHome()
{
  bool flag = true;
  flag = flag && PathStartsWithHome("~/");
  flag = flag && PathStartsWithHome("~");
  flag = flag && !PathStartsWithHome("/");
  return flag;
}

int main()
{
  HLIB_ASSERT_TEST(testPathAbsolute);
  HLIB_ASSERT_TEST(testPathClean);
  HLIB_ASSERT_TEST(testPathJoin);
  HLIB_ASSERT_TEST(testPathStartsWithHome);
  return 0;
}
