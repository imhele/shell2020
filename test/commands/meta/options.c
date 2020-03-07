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

bool testToWrapString()
{
  bool flag = true;
  struct CommandMetaOptions *options;
  useClosureValue(options);
  struct LinkList *level_1 = CommandMetaOptionToString(options, 1);
  struct LinkList *level_2 = CommandMetaOptionToString(options, 2);
  flag = flag && !strcmp(LinkListGetter(level_1, 0), "[--help | -h [--description | -d]]");
  flag = flag && !strcmp(LinkListGetter(level_1, 1), "[--version | -v]");
  flag = flag && !strcmp(LinkListGetter(level_2, 0), "]");
  flag = flag && !strcmp(LinkListGetter(level_2, 1), "             [--description | -d]");
  flag = flag && !strcmp(LinkListGetter(level_2, 2), "[--help | -h");
  flag = flag && !strcmp(LinkListGetter(level_2, 3), "[--version | -v]");
  LinkListFreeEach(&level_1, __freeEachString);
  LinkListFreeEach(&level_2, __freeEachString);
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
    HLIB_ASSERT_TEST(testToWrapString);
  }
  ENDCLOSURE;

  return 0;
}
