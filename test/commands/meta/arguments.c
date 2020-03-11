#include "../../../main.h"

bool testToNoWrapString()
{
  struct CommandMetaArgumentsMap *options;
  useClosureValue(options);
  struct LinkList *no_wrap = CommandMetaArgumentsMapToString(options, 0, false, DEFAULTARG);
  bool flag =
      !strcmp(no_wrap->value, "<command> [--version (-v)] [--help (-h) [--description (-d)]]");
  LinkListFreeValue(&no_wrap);
  return flag;
}

bool testToWrapString()
{
  bool flag = true;
  struct CommandMetaArgumentsMap *options;
  useClosureValue(options);
  struct LinkList *level_1 = CommandMetaArgumentsMapToString(options, 1, false, DEFAULTARG);
  struct LinkList *level_2 = CommandMetaArgumentsMapToString(options, 2, false, DEFAULTARG);
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
  struct CommandMetaArgumentsMap *options;
  useClosureValue(options);
  struct LinkList *strs = CommandMetaArgumentsMapToString(options, 2, true, "1;34");
  flag = flag && !strcmp(LinkListGetter(strs, 0), "]");
  flag = flag && !strcmp(LinkListGetter(strs, 2), "[\033[1;34m--help (-h)\033[0m: Show the usage of command.");
  flag = flag && !strcmp(LinkListGetter(strs, 3), "[\033[1;34m--version (-v)\033[0m: Show the version of command.]");
  flag = flag && !strcmp(LinkListGetter(strs, 4), "<\033[1;34mcommand\033[0m: Any command.>");
  LinkListFreeValue(&strs);
  return flag;
}

int main()
{
  struct CommandMetaArgumentsMap *options = NULL;
  struct CommandMetaArgument command = {1, NULL, "Any command.", NULL};
  struct CommandMetaArgument help = {0, "h", "Show the usage of command.", NULL};
  struct CommandMetaArgument version = {0, "v", "Show the version of command.", NULL};
  struct CommandMetaArgument help_desc = {0, "d", "Show the description of each usage.", NULL};
  help.sub_arguments = CommandMetaArgumentRegister(NULL, "description", &help_desc);
  options = CommandMetaArgumentRegister(options, "help", &help);
  options = CommandMetaArgumentRegister(options, "version", &version);
  options = CommandMetaArgumentRegister(options, "command", &command);

  CLOSURE
  {
    useClosure(options);
    HLIB_ASSERT_TEST(testToNoWrapString);
    HLIB_ASSERT_TEST(testToWrapString);
    HLIB_ASSERT_TEST(testToStringWithDesc);
  }
  ENDCLOSURE;

  CommandMetaArgumentsMapFree(&options);

  return 0;
}
