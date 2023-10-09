### 汇总

本章节部分内容参考自[网络文章1](https://blog.csdn.net/weixin_43717839/article/details/129382657)、[网络文章2](https://blog.csdn.net/sirkang/article/details/105988953)。

LLVM是一个代码格式化工具，修改一些默认参数使之更好的符合你的代码风格，以下是我个人的调整内容。

```LLVM
BasedOnStyle: LLVM
IndentWidth: 4

AllowShortIfStatementsOnASingleLine: true
AllowShortLoopsOnASingleLine: true
AllowShortFunctionsOnASingleLine: Empty

NamespaceIndentation: All
ColumnLimit: 70
IndentPPDirectives: BeforeHash
SpaceAfterTemplateKeyword: false
ReflowComments: true
AlignTrailingComments: false
MaxEmptyLinesToKeep: 2
```

***

### 参数调节细节

`AllowShortLoopsOnASingleLine: true` 允许合并短的循环到单行上：可以让**没有括号**单独一行的短语句合并到上一行的结尾。

```c++
// 格式化前
void solve() {
    while (1)
        continue;
}

// 格式化后
void solve() {
    while (1) continue;
}
```

`AllowShortIfStatementsOnASingleLine : true` 允许合并短的if语句到单行上：同上，注意带 `else` 或 `else if` 后不生效。

`AllowShortFunctionsOnASingleLine: Empty` 仅允许合并短的空函数到单行上。

`NamespaceIndentation : All` 缩进全部的命名空间。

`ColumnLimit : 100` 列数限制，列数超过这个值的行会被自动换行。

`IndentPPDirectives : BeforeHash` 对 `define` 语句缩进。

```c++
// 设置为None时
#ifndef ONLINE_JUDGE
#define tout cout
#include <bits/wida.h>
#endif

// 设置为AfterHash时
#ifndef ONLINE_JUDGE
#    define tout cout
#    include <bits/wida.h>
#endif

// 设置为BeforeHash时
#ifndef ONLINE_JUDGE
    #define tout cout
    #include <bits/wida.h>
#endif
```

`SpaceAfterTemplateKeyword: false` 不在可变模板关键字 `template` 后插入空格。

```c++
// 不设置时
template <class T> void chk(T x) {}

// 设置为false时
template<class T> void chk(T x) {}
```

`MaxEmptyLinesToKeep: 2` 设置最大持续空行：如果有非常多空行，会被自动删除到剩两行。

`ReflowComments : true` 会对列数超过 `ColumnLimit` 设置的注释进行自动换行。

```c++
// 格式化前
// veryVeryVeryVeryVeryVeryVeryVeryVeryVeryVeryLongComment with plenty of information
/* second veryVeryVeryVeryVeryVeryVeryVeryVeryVeryVeryLongComment with plenty of information */

// 格式化后
// veryVeryVeryVeryVeryVeryVeryVeryVeryVeryVeryLongComment with plenty of
// information
/* second veryVeryVeryVeryVeryVeryVeryVeryVeryVeryVeryLongComment with plenty of
 * information */
```

`AlignTrailingComments : false` 不对齐尾部注释。

```c++
// 设置为true时
int a = 0;    // 初始化a
int cnt = 20; // 初始化cnt

// 设置为false时
int a = 0; // 初始化a
int cnt = 20; // 初始化cnt
```