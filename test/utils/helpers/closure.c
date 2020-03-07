#include <math.h>
#include "../../../main.h"

long __testClosureGetValueA()
{
  long a = -1;
  useClosureValue(a);
  return a;
}

long __testClosureGetValueB()
{
  long b = -1;
  useClosureValue(b);
  return b;
}

bool testClosure()
{
  bool flag;
  long a = random();

  CLOSURE
  {
    useClosure(a);
    flag = __testClosureGetValueA() == a;
  }
  ENDCLOSURE;

  return flag;
}

bool testMultiClosure()
{
  bool flag = true;
  long a = random();

  CLOSURE
  {
    useClosure(a);
    CLOSURE
    {
      long b = random();
      useClosure(b);
      flag = flag && __testClosureGetValueA() == a;
      flag = flag && __testClosureGetValueB() == b;
    }
    ENDCLOSURE;
    flag = flag && __testClosureGetValueB() == -1;
  }
  ENDCLOSURE;

  return flag;
}

int main()
{
  HLIB_ASSERT_TEST(testClosure);
  HLIB_ASSERT_TEST(testMultiClosure);
  return 0;
}
