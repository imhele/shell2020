# shell2020

操作系统课程第一次实验

[![Build Status](https://travis-ci.com/imhele/shell2020.svg?branch=master)](https://travis-ci.com/imhele/shell2020)

## 🍕 Feature

- 👆 参照手势响应原理实现的键入响应，支持基础的快捷键操作 [`src/parser/pipeline`](https://github.com/imhele/shell2020/tree/master/src/parser/pipeline)。
- 🎨 Unicode 字符支持。
- 🌟 环境变量与输入历史记录支持。
- 💄 局部变量[参照 JS 闭包特性实现](https://github.com/imhele/blog/issues/7)，支持多层闭包内同名变量的跨函数引用。

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
