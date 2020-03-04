#ifndef __HLIB_COMMANDS_META_OPTIONS
#define __HLIB_COMMANDS_META_OPTIONS

struct CommandMetaOption {
  char *name;
  char *alias;
  CommandMetaOption *sub_options;
};

#endif /* __HLIB_COMMANDS_META_OPTIONS */
