#include "../../../main.h"

bool testToNoWrapString()
{
  struct CommandMetaOptions *options;
  useClosureValue(options);
  struct LinkList *no_wrap = CommandMetaOptionsToString(options, 0, false, DEFAULTARG);
  bool flag =
      !strcmp(no_wrap->value, "<command> [--version (-v)] [--help (-h) [--description (-d)]]");
  LinkListFreeValue(&no_wrap);
  return flag;
}

bool testToWrapString()
{
  bool flag = true;
  struct CommandMetaOptions *options;
  useClosureValue(options);
  struct LinkList *level_1 = CommandMetaOptionsToString(options, 1, false, DEFAULTARG);
  struct LinkList *level_2 = CommandMetaOptionsToString(options, 2, false, DEFAULTARG);
  flag = flag && !strcmp(LinkListGetter(level_1, 0), "[--help (-h) [--description (-d)]]");
  flag = flag && !strcmp(LinkListGetter(level_1, 1), "[--version (-v)]");
  flag = flag && !strcmp(LinkListGetter(level_1, 2), "<command>");
  flag = flag && !strcmp(LinkListGetter(level_2, 0), "]");
  flag = flag && !strcmp(LinkListGetter(level_2, 1), "\t[--description (-d)]");
  flag = flag && !strcmp(LinkListGetter(level_2, 2), "[--help (-h)");
  flag = flag && !strcmp(LinkListGetter(level_2, 3), "[--version (-v)]");
  flag = flag && !strcmp(LinkListGetter(level_2, 4), "<command>");
  LinkListFreeValue(&level_1);
  LinkListFreeValue(&level_2);
  return flag;
}

bool testToStringWithDesc()
{
  bool flag = true;
  struct CommandMetaOptions *options;
  useClosureValue(options);
  struct LinkList *strs = CommandMetaOptionsToString(options, 2, true, "1;34");
  flag = flag && !strcmp(LinkListGetter(strs, 0), "]");
  flag = flag && !strcmp(LinkListGetter(strs, 2), "[\033[1;34m--help (-h)\033[0m: Show the usage of command.");
  flag = flag && !strcmp(LinkListGetter(strs, 3), "[\033[1;34m--version (-v)\033[0m: Show the version of command.]");
  flag = flag && !strcmp(LinkListGetter(strs, 4), "<\033[1;34mcommand\033[0m: Any command.>");
  LinkListFreeValue(&strs);
  return flag;
}

int main()
{
  struct CommandMetaOptions *options = NULL;
  struct CommandMetaOption command = {1, NULL, "Any command.", NULL};
  struct CommandMetaOption help = {0, "h", "Show the usage of command.", NULL};
  struct CommandMetaOption version = {0, "v", "Show the version of command.", NULL};
  struct CommandMetaOption help_desc = {0, "d", "Show the description of each usage.", NULL};
  help.sub_options = CommandMetaOptionsRegister(NULL, "description", &help_desc);
  options = CommandMetaOptionsRegister(options, "help", &help);
  options = CommandMetaOptionsRegister(options, "version", &version);
  options = CommandMetaOptionsRegister(options, "command", &command);

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
