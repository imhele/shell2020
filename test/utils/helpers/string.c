#include "../../../main.h"

bool testStrCat()
{
  bool flag = true;
  char *a = NULL;
  char *b = " world";
  HLIB_STRCAT(a, "Hello");
  flag = flag && !strcmp(a, "Hello");
  HLIB_STRCAT(a, b);
  flag = flag && !strcmp(a, "Hello world");
  flag = flag && !strcmp(b, " world");
  return flag;
}

bool testStrCatLeft()
{
  bool flag = true;
  char *a = NULL;
  char *b = "Hello";
  HLIB_STRCAT_LEFT(a, " world");
  flag = flag && !strcmp(a, " world");
  HLIB_STRCAT_LEFT(a, b);
  flag = flag && !strcmp(a, "Hello world");
  flag = flag && !strcmp(b, "Hello");
  free(a);
  return flag;
}

bool testStrRepeat()
{
  char *str = HLIB_STRREPEAT("abc", 2);
  bool flag = !strcmp(str, "abcabc");
  free(str);
  return flag;
}


bool testStrRev()
{
  char *str = HLIB_STRREV("abcdef");
  bool flag = !strcmp(str, "fedcba");
  free(str);
  return flag;
}

bool testStrSplit()
{
  bool flag = true;
  char **array = HLIB_STRSPLIT("abc def ghi ", ' ');
  flag = flag && !strcmp(*array, "abc");
  flag = flag && !strcmp(*(array + 1), "def");
  flag = flag && !strcmp(*(array + 2), "ghi");
  flag = flag && !strcmp(*(array + 3), "");
  flag = flag && *(array + 4) == NULL;
  free(*array), free(array);
  return flag;
}

int main()
{
  HLIB_ASSERT_TEST(testStrCat);
  HLIB_ASSERT_TEST(testStrCatLeft);
  HLIB_ASSERT_TEST(testStrRepeat);
  HLIB_ASSERT_TEST(testStrRev);
  HLIB_ASSERT_TEST(testStrSplit);
  return 0;
}
