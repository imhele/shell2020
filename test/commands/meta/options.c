#include "../../../main.h"

void __freeEachString(void *value, int index, struct LinkList *curr)
{
  free(value);
}

bool testToNoWrapString()
{
  struct CommandMetaOptions *options;
  useClosureValue(options);
  struct LinkList *no_wrap = CommandMetaOptionToString(options, 0);
  bool flag = !strcmp(no_wrap->value, "[--version | -v] [--help | -h [--description | -d]]");
  LinkListFreeEach(&no_wrap, __freeEachString);
  return flag;
}

int main()
{
  struct CommandMetaOptions *options = NULL;
  struct CommandMetaOption help = {"h", "Show the usage of command.", NULL};
  struct CommandMetaOption version = {"v", "Show the version of command.", NULL};
  struct CommandMetaOption help_desc = {"d", "Show the description of each usage.", NULL};
  help.sub_options = CommandMetaOptionsRegister(NULL, "description", &help_desc);
  options = CommandMetaOptionsRegister(options, "help", &help);
  options = CommandMetaOptionsRegister(options, "version", &version);

  CLOSURE
  {
    useClosure(options);
    HLIB_ASSERT_TEST(testToNoWrapString);
  }
  ENDCLOSURE;

  return 0;
}
