#include "../../../main.h"

bool testToNoWrapString()
{
  struct CommandMetaOptions *options;
  useClosureValue(options);
  struct LinkList *no_wrap = CommandMetaOptionsToString(options, 0, false);
  bool flag = !strcmp(no_wrap->value, "[--version (-v)] [--help (-h) [--description (-d)]]");
  LinkListFreeValue(&no_wrap);
  return flag;
}

bool testToWrapString()
{
  bool flag = true;
  struct CommandMetaOptions *options;
  useClosureValue(options);
  struct LinkList *level_1 = CommandMetaOptionsToString(options, 1, false);
  struct LinkList *level_2 = CommandMetaOptionsToString(options, 2, false);
  flag = flag && !strcmp(LinkListGetter(level_1, 0), "[--help (-h) [--description (-d)]]");
  flag = flag && !strcmp(LinkListGetter(level_1, 1), "[--version (-v)]");
  flag = flag && !strcmp(LinkListGetter(level_2, 0), "]");
  flag = flag && !strcmp(LinkListGetter(level_2, 1), "\t[--description (-d)]");
  flag = flag && !strcmp(LinkListGetter(level_2, 2), "[--help (-h)");
  flag = flag && !strcmp(LinkListGetter(level_2, 3), "[--version (-v)]");
  LinkListFreeValue(&level_1);
  LinkListFreeValue(&level_2);
  return flag;
}

bool testToStringWithDesc()
{
  bool flag = true;
  struct CommandMetaOptions *options;
  useClosureValue(options);
  struct LinkList *strs = CommandMetaOptionsToString(options, 2, true);
  flag = flag && !strcmp(LinkListGetter(strs, 0), "]");
  flag = flag && !strcmp(LinkListGetter(strs, 1), "\t[--description (-d): Show the description of each usage.]");
  flag = flag && !strcmp(LinkListGetter(strs, 2), "[--help (-h): Show the usage of command.");
  flag = flag && !strcmp(LinkListGetter(strs, 3), "[--version (-v): Show the version of command.]");
  LinkListFreeValue(&strs);
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
    HLIB_ASSERT_TEST(testToStringWithDesc);
  }
  ENDCLOSURE;

  return 0;
}
