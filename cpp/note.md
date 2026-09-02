# 基本数据类型

## 随机数的生成方法

```cpp
mt19937 gen(random_device{}());
uniform_int_distribution<int> dis(1, 10);
int target = dis(gen);
```

## 初始化

```cpp
int a {4};
int a {};
int a(4);
```

## 输入输出

```cpp
std::cout<<1<<endl;
std::cout<<1<<'\n';
std::cin>>x;
// endl会清空缓冲区
```

## 命名空间

```cpp
using namespace std;
```

## 预处理器

```cpp
#include <iostream>   // 引入头文件

#define MAX 100       // 宏定义，文本替换

#ifdef DEBUG
// DEBUG 被定义时编译
#endif

#ifndef USER_H
#define USER_H
// 防止头文件重复包含
#endif
```

## 头文件

```cpp
// add.h：声明
int add(int x, int y);

// add.cpp：实现
#include "add.h"

int add(int x, int y)
{
    return x + y;
}

// main.cpp：使用
#include "add.h"
#include <iostream>

int main()
{
    std::cout << add(1, 2);
}
```

.h    → 主要放声明
.cpp  → 主要放实现

#include "xxx.h" → 自己的头文件
#include <xxx>   → 标准库/第三方库

.cpp 应 include 自己对应的 .h
不要 #include ".cpp"
每个文件显式 include 自己需要的头文件

\#include 本质 ≈ 文本复制

## 头文件保护

```cpp
// user.h

#ifndef USER_H
#define USER_H

int getUser();

#endif
```

作用：

```cpp
防止同一个头文件
在同一个编译单元中被重复 include
```

原理：

```
第一次：
#ifndef USER_H  → 未定义
#define USER_H
→ 内容生效

第二次：
#ifndef USER_H  → 已定义
→ 跳过
```

现代写法：

```cpp
#pragma once

int getUser();
```

核心关系：

```
#include ≈ 文本复制
        ↓
可能重复复制
        ↓
Header Guard 防止重复复制
```

## sizeof

```
int x{10};

sizeof(int);   // int 类型大小
sizeof(x);     // x 对象大小
```

常见：

```
char        → 1 byte
short       → 2 bytes
int         → 4 bytes
long long   → 8 bytes
float       → 4 bytes
double      → 8 bytes
```

但：

```
具体大小由平台 / 编译器决定
不要认为 int 永远 = 4 bytes
```

核心：

```
sizeof 返回字节数

n bit
→ 2^n 个不同状态
```

不能：

```
sizeof(void); // ❌
```

> **类型决定对象占用多少内存，`sizeof` 用来查看这个大小。**

## signed integer

```
short s{-10};
int i{100};
long l{1000};
long long ll{10000000000LL};
整数默认 signed
无需写 signed int
```

范围：

```
n bit：

-2^(n-1)
~
2^(n-1)-1
```

常见：

```
8 bit  → -128 ~ 127
16 bit → -32768 ~ 32767
32 bit → -2147483648 ~ 2147483647
```

溢出：

```
int x{2147483647};
x = x + 1; // ❌ signed overflow → 未定义行为
```

整数除法：

```
8 / 5    // 1
-8 / 5   // -1
整数除法：
直接截掉小数部分，不四舍五入
```

这章你重点记 **三个东西**：

```
① int 默认 signed

② n 位 signed 范围：
   -2^(n-1) ~ 2^(n-1)-1

③ int / int 是整数除法
   小数直接丢掉
```

## unsigned integer

```
unsigned int x{10};
```

范围：

```
n bit unsigned：

0 ~ 2^n - 1
```

例如：

```
8 bit：

signed    → -128 ~ 127
unsigned  →    0 ~ 255
```

回绕：

```
// 假设 32-bit unsigned
unsigned int x{4294967295u};
++x; // 0
```

向下也会绕：

```
unsigned int x{0};
--x; // 4294967295（假设 32 bit）
```

最大坑：

```
unsigned int x{2};
unsigned int y{3};

x - y; // 4294967295，而不是 -1
```

避免：

```
signed + unsigned 混用
```

默认：

```
int count{10}; // ✅ 普通整数优先 signed
```

特殊场景再用：

```
unsigned
→ 位运算
→ 明确需要模回绕
→ 标准库接口 / size_t
```

最应该牢牢记住 **3 句话**：

```
① unsigned 不能表示负数

② unsigned 超出范围会按模 2^n 回绕

③ 不要随便混用 signed 和 unsigned
```

## 类型转换 / `static_cast`

隐式转换：

```
double x{5};  // int 5 → double 5.0
```

可能丢数据：

```
double x{5.5};

// int y{x};              // ❌ 列表初始化阻止窄化
int y{static_cast<int>(x)}; // ✅ 明确转换，结果 5
```

语法：

```
static_cast<目标类型>(表达式)
```

例如：

```
static_cast<double>(5);  // 5.0
static_cast<int>(5.9);   // 5
static_cast<int>('A');   // 65（ASCII环境）
```

核心：

```
类型转换不会修改原变量类型
而是生成目标类型的新值
```

```
① 隐式转换
   → 编译器自动做

② static_cast
   → 程序员明确要求转换

③ static_cast<int>(5.5)
   → 5，小数直接截断

④ 转换产生新值
   → 不改变原变量的类型
```

# 常量，字符串

## const

```
// 常量表达式：编译时就能计算
3 + 4

// 编译时常量
const int x{3};
const int y{x + 4};

// 运行时常量
int n{};
std::cin >> n;

const int z{n};

// const 只代表：初始化后不能修改
// 不代表：一定是编译时常量
```

## constexpr

```cpp
// constexpr：强制变量成为编译时常量

constexpr int x{10};
constexpr int y{3 + 4};
constexpr int z{x + y};

// ❌ 运行时值不能初始化 constexpr
int age{};
std::cin >> age;
// constexpr int userAge{age};

// ✅ 运行时常量使用 const
const int userAge{age};

// 选择规则：
// 编译时能确定 + 不修改 → constexpr
// 运行时才确定 + 不修改 → const
```

## 字面值常量

```cpp
// 字面值：直接写在代码里的值

5          // int
true       // bool
3.14       // double
'A'        // char
"hello"    // C 风格字符串

// 后缀
5L         // long
5LL        // long long
5u         // unsigned int

3.14       // double
3.14f      // float
3.14L      // long double

// 字符 vs 字符串
'A'        // char
"hello"    // const char[]，结尾隐藏 '\0'

// 避免魔数
constexpr int maxStudentsPerClass{ 30 };
```

## 进制

```cpp
// C++ 整数字面值进制

int a{ 10 };       // 十进制
int b{ 0b1010 };   // 二进制
int c{ 012 };      // 八进制
int d{ 0xA };      // 十六进制

// 四个值完全相同

// 前缀
// 无前缀 → 十进制
// 0b     → 二进制
// 0      → 八进制
// 0x     → 十六进制

// 数字分隔符
int x{ 1'000'000 };
int y{ 0b1011'0010 };

// 输出进制
std::cout << std::dec; // 十进制
std::cout << std::hex; // 十六进制
std::cout << std::oct; // 八进制
```

## inline

定义：

```cpp
inline 返回类型 函数名()
{
}
```

作用：

```cpp
建议编译器将函数调用展开
减少函数调用开销
```

特点：

```cpp
1. 只是建议，不保证展开
2. 小函数适合
3. 类内定义函数默认 inline
4. 头文件函数定义常使用 inline
```

示例：

```cpp
inline int add(int a,int b)
{
    return a+b;
}
```

## constexpr 和consteval函数

```
constexpr int add(int a, int b)
{
    return a + b;
}
constexpr 函数：
可以编译期执行
也可以运行期执行

返回值用于常量表达式
→ 必须编译期执行

传入运行时变量
→ 运行期执行
```

```
consteval int add(int a, int b)
{
    return a + b;
}
consteval（C++20）
→ 必须编译期执行
→ 无法编译期执行就直接编译错误
```

```
constexpr int f(int x)
{
    return x * 2;
}

consteval int g(int x)
{
    return x * 2;
}
int x = 10;

f(x);    // ✅ 运行期
g(x);    // ❌ 编译错误
```

先牢牢记住一句就够：

> **`constexpr` = 能编译期算就可以编译期算，但也允许运行期算；`consteval` = 强制编译期算。**

## string

```
#include <string>

std::string name{"Marc"};

name = "Alex";

std::cout << name;
```

### 字符串输入

```
std::string name{};

std::cin >> name; 
// 遇到空白停止
```

整行输入：

```
std::getline(std::cin >> std::ws, name);
cin >>
→ 读一个“单词”

getline()
→ 读一整行
```

### 获取长度

```
std::string name{"Marc"};

name.length(); // 4
不包含结尾的 '\0'
```

### 性能

```
void print(std::string str); // 可能复制
std::string 按值传参
→ 会有复制成本
→ 尽量避免
```

### stringview

```cpp
// std::string_view
// 只读字符串视图，不拥有字符串，不复制数据
#include <string_view>

std::string_view sv{"Hello"};

// 最常见用途：只读字符串参数
void print(std::string_view str)
{
    std::cout << str;
}
```

记住这三个词：

```cpp
std::string_view

不拥有
不拷贝
只读访问
```

以及最重要的对比：

```cpp
std::string       // 我要“拥有/保存”这个字符串
std::string_view  // 我只是“看一下/读一下”这个字符串
```

```cpp
// string_view 不拥有字符串，注意生命周期

std::string s{"Hello"};
std::string_view sv{s}; // ✅

// s 被销毁 / 修改后
// sv 可能失效，继续使用 = 未定义行为
```

再记三个典型情况：

```cpp
std::string_view a{"Hello"};    // ✅ 字符串字面量长期存在

std::string s{"Hello"};
std::string_view b{s};          // ✅ s 活着期间有效

std::string_view c{"Hello"s};   // ❌ 临时 string 被销毁
```

最后把这一条刻住：

```
string_view 自己不管理生命周期

被查看的字符串：
生命周期 > string_view 的使用时间
```

也就是：

```
std::string      → 我拥有这段字符串
std::string_view → 我借来看一下
```

# 运算符

## 算数运算符

```cpp
// 算术运算符
+  -  *  /  %

// 整数除法：丢弃小数部分
7 / 4;      // 1
-7 / 4;     // -1

// 浮点除法：至少一个操作数是浮点数
7.0 / 4;    // 1.75

// int / int 想保留小数
int x{7};
int y{4};

static_cast<double>(x) / y; // 1.75
```

# 作用域与编译链接

## 作用域与编译链接

```cpp
// namespace：防止命名冲突
namespace Math
{
    int add(int x, int y);
}

// :: 作用域解析操作符
Math::add(1, 2);

// 全局作用域
::print();

// 嵌套命名空间
namespace Foo::Goo
{
    int add(int x, int y);
}

Foo::Goo::add(1, 2);
```

一句话记住：

> **`namespace` 给名字划分区域，`::` 指定去哪个区域找这个名字。**

## 全局变量

```cpp
#include <iostream>

int global = 10;  // 全局变量

int main()
{
    std::cout << global;
}

// a.cpp
int num = 10;

// b.cpp
extern int num;  // 声明其他文件中的变量

static int num = 10;

// static全局变量
// 只能当前cpp文件访问

int a = 10;

void test()
{
    int a = 20;

    std::cout << ::a; 
}
// :: 访问全局变量
```

## 变量名遮挡

内层作用域里如果定义了一个和外层同名的变量，内层变量会暂时“遮住”外层变量

```cpp
int a = 1;

{
    int a = 2; // 新定义一个同名变量
               // → 遮挡外层 a
}

int a = 1;

{
    a = 2;     // 没有定义新变量
               // → 修改外层 a
}
```

## 内部链接

```cpp
// 内部链接（internal linkage）
// 名字只能在当前 .cpp / 翻译单元中使用，其他 .cpp 无法访问

static int g_num = 10;  // 全局变量：内部链接
static void foo() {}    // 函数：内部链接

const int g_a = 10;     // 全局 const 默认内部链接
constexpr int g_b = 20; // 全局 constexpr 默认内部链接

int g_x = 10;           // 普通全局变量：默认外部链接
static int g_y = 20;    // static 全局变量：内部链接

// 现代 C++ 常用匿名命名空间实现同样效果
namespace
{
    int value = 100;
    void helper() {}
}
```

## 外部链接

```cpp
// 外部链接（external linkage）
// 标识符可以被其他 .cpp / 翻译单元使用

int g_x = 10;        // 普通全局变量：默认外部链接
void foo() {}        // 普通函数：默认外部链接

// ---------- 变量前向声明 ----------

// a.cpp
int g_value = 100;   // 定义：真正创建变量

// main.cpp
extern int g_value;  // 声明：变量定义在其他地方

// extern 无初始化值 → 通常是前向声明
extern int g_a;

// extern 有初始化值 → 是定义
extern int g_b = 20;

// ---------- const ----------

const int g_c = 10;          // 全局 const：默认内部链接
extern const int g_d = 20;   // 定义 + 外部链接
extern const int g_d;        // 前向声明

// ---------- 对比 ----------

int g_m = 1;         // 外部链接：其他 cpp 可 extern 使用
static int g_n = 2;  // 内部链接：只能当前 cpp 使用

// 核心：
// extern int x;   -> “x 定义在别处，我这里只声明”
// static int x;   -> “x 只给当前 cpp 使用”
```

