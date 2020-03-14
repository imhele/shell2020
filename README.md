# shell2020

操作系统课程第一次实验

[![Build Status](https://travis-ci.com/imhele/shell2020.svg?branch=master)](https://travis-ci.com/imhele/shell2020)

## 🍕 Feature

- 👆 参照手势响应原理实现的键入响应，支持基础的快捷键操作 [`src/parser/pipeline`](https://github.com/imhele/shell2020/tree/master/src/parser/pipeline)。
- 🎨 POSIX 与 Unicode 支持。
- 🌟 环境变量与输入历史记录支持。
- 💄 局部变量[参照 JS 闭包特性实现](https://github.com/imhele/blog/issues/7)，支持多层闭包内同名变量的跨函数引用。

### Hot Keys

| 按键 / 按键组合 | 原始字符 | 功能                                                       | 处理此功能的 Pipeline 文件                                                                                                     |
| --------------- | -------- | ---------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------ |
| Control + C     | `\003`   | 忽略已输入的内容，直接换行                                 | [src/parser/pipeline/exit.h ](https://github.com/imhele/shell2020/tree/master/src/parser/pipeline/exit.h)                      |
| Control + D     | `\004`   | 退出 Shell                                                 | [src/parser/pipeline/exit.h ](https://github.com/imhele/shell2020/tree/master/src/parser/pipeline/exit.h)                      |
| Enter           | `\015`   | 执行已输入的内容并换行                                     | [src/parser/pipeline/exit.h ](https://github.com/imhele/shell2020/tree/master/src/parser/pipeline/exit.h)                      |
| Left            | `\033[D` | 将光标向左移动一位                                         | [src/parser/pipeline/leftright.h](https://github.com/imhele/shell2020/tree/master/src/parser/pipeline/leftright.h)             |
| Right           | `\033[C` | 将光标向右移动一位                                         | [src/parser/pipeline/leftright.h](https://github.com/imhele/shell2020/tree/master/src/parser/pipeline/leftright.h)             |
| Command + Left  | `\001`   | 将光标移到行首                                             | [src/parser/pipeline/startofheading.h](https://github.com/imhele/shell2020/tree/master/src/parser/pipeline/startofheading.h)   |
| Command + Right | `\005`   | 将光标移到行尾                                             | [src/parser/pipeline/enquiry.h](https://github.com/imhele/shell2020/tree/master/src/parser/pipeline/enquiry.h)                 |
| Delete          | `\177`   | 删除一位光标前的字符                                       | [src/parser/pipeline/del.h ](https://github.com/imhele/shell2020/tree/master/src/parser/pipeline/del.h)                        |
| Option + Left   | `\033b`  | 将光标移到从光标左侧第二个字符开始的第一个分隔符右侧       | [src/parser/pipeline/skipword.h](https://github.com/imhele/shell2020/tree/master/src/parser/pipeline/skipword.h)               |
| Option + Right  | `\033f`  | 将光标移到从光标右侧第二个字符开始的第一个分隔符左侧       | [src/parser/pipeline/skipword.h](https://github.com/imhele/shell2020/tree/master/src/parser/pipeline/skipword.h)               |
| Option + Delete | `\027`   | 删除从光标左侧第二个字符开始，向左直到第一个分隔符内的字符 | [src/parser/pipeline/endoftransblock.h](https://github.com/imhele/shell2020/tree/master/src/parser/pipeline/endoftransblock.h) |
| Up              | `\033[A` | 恢复上一条执行过的命令                                     | [src/parser/pipeline/updown.h](https://github.com/imhele/shell2020/tree/master/src/parser/pipeline/updown.h)                   |
| Down            | `\033[B` | 恢复下一条执行过的命令                                     | [src/parser/pipeline/updown.h](https://github.com/imhele/shell2020/tree/master/src/parser/pipeline/updown.h)                   |

## 💡 Build

```bash
$ gcc -Wall -o path/to/your/output main.c
```

## 💻 Develop

### Test

测试文件在 [`test`](https://github.com/imhele/shell2020/tree/master/test) 目录下，执行以下命令会自动递归扫描目录里的所有 `*.c` 文件进行编译并执行：

```bash
$ sh scripts/test.sh
```

或者指定测试目录 / 文件：

```bash
$ sh scripts/test.sh test/utils
$ sh scripts/test.sh test/utils/helpers/closure.c
```

### Build Index

约定 `src` 内的所有目录都有一个对应的同名头文件，作为目录内的文件与子目录的索引。可选择执行 [NodeJS](https://nodejs.org/) 脚本自动构建：

```bash
$ node scripts/buildindex.js
```

可在 `.indexconfig.json` 文件中配置 `excludes` 忽略条件，每项条件将被转为正则表达式进行匹配：

```json
{
  "root": "src",
  "extname": ".h",
  "entry": "main",
  "macroprefix": "__HLIB",
  "excludes": ["^src/commands.h$"]
}
```
