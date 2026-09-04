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

# 控制流与错误处理

## 控制流简介

```cpp
#include <iostream>
#include <vector>
#include <cstdlib>   // std::exit()

// ── 1. 条件语句 ──────────────────────────────────────────────
//    根据条件表达式的真假，决定执行哪段代码

// if / else if / else
void demo_if(int score) {
    if (score >= 90) {
        std::cout << "优秀\n";
    } else if (score >= 60) {
        std::cout << "及格\n";
    } else {
        std::cout << "不及格\n";
    }
}

// switch / case / default
//   每个 case 后通常以 break 结尾，防止 fallthrough
void demo_switch(int day) {
    switch (day) {
        case 1: std::cout << "周一\n"; break;
        case 2: std::cout << "周二\n"; break;
        case 3: std::cout << "周三\n"; break;
        default: std::cout << "其他\n"; break;
    }
}

// ── 2. 循环语句 ──────────────────────────────────────────────
//    满足条件时，重复执行一段代码 0 次或多次

// while —— 先判断条件，再执行循环体（可能 0 次）
void demo_while() {
    int i = 0;
    while (i < 5) {
        std::cout << i << " ";
        ++i;
    }
    std::cout << "\n";
}

// do-while —— 先执行一次循环体，再判断条件（至少 1 次）
//   注意末尾有分号
void demo_do_while() {
    int n{};
    do {
        std::cout << "请输入正数: ";
        std::cin >> n;
    } while (n <= 0);
}

// for —— 初始化; 条件; 更新 三段式
void demo_for() {
    for (int i = 0; i < 5; ++i) {
        std::cout << i << " ";
    }
    std::cout << "\n";
}

// range-for (C++11) —— 遍历容器/数组中的每个元素
void demo_range_for() {
    std::vector<int> nums{10, 20, 30, 40};
    for (int n : nums) {
        std::cout << n << " ";
    }
    std::cout << "\n";
}

// ── 3. 跳转语句 ──────────────────────────────────────────────
//    改变当前循环或 switch 的执行流程

void demo_jump() {
    for (int i = 0; i < 10; ++i) {
        if (i == 3) continue;   // 跳过本次迭代，进入下一次
        if (i == 7) break;      // 立即退出整个循环
        std::cout << i << " ";  // 输出: 0 1 2 4 5 6
    }
    std::cout << "\n";
}

// goto —— 无条件跳转到标签位置（不推荐，了解即可）
void demo_goto() {
    int i = 0;
loop:
    if (i < 3) {
        std::cout << i++ << " ";
        goto loop;
    }
    std::cout << "\n";
}

// ── 4. 函数调用与 return ─────────────────────────────────────
//    跳到函数体执行，完成后通过 return 返回调用处

int add(int a, int b) {
    return a + b;   // 返回值并退出函数
}

// ── 5. 停止程序执行 ──────────────────────────────────────────
//    立即终止整个程序

void demo_exit() {
    // std::exit(0);   // 正常退出，参数为退出码
    // std::abort();   // 异常终止
}

// ── 6. 异常处理 ──────────────────────────────────────────────
//    错误处理的一种特殊形式（详见后续章节）

void demo_exception() {
    try {
        throw std::runtime_error("出错了!");
    } catch (const std::exception& e) {
        std::cout << "捕获异常: " << e.what() << "\n";
    }
}
```

## 随机数

~~~cpp
#include <iostream>
#include <random>
#include <chrono>

// ── 1. 基础用法：生成 32 位随机整数 ─────────────────────────
//    mt19937 重载了 operator()，调用方式类似函数

void demo_basic() {
    std::mt19937 mt{};   // 值初始化，种子默认为 0
    std::cout << mt() << "\n";   // 产出下一个随机数
    std::cout << mt() << "\n";
}

// ── 2. 掷骰子：均匀分布器 ───────────────────────────────────
//    PRNG 产出大范围整数，用 distribution 映射到指定区间

void demo_dice() {
    std::mt19937 mt{ std::random_device{}() };
    std::uniform_int_distribution<int> die6{1, 6};

    for (int i = 0; i < 10; ++i) {
        std::cout << die6(mt) << " ";
    }
    std::cout << "\n";
}

// ── 3. 推荐播种方式：random_device ──────────────────────────
//    向操作系统请求真随机数作为种子，每次运行都不同

void demo_random_device_seed() {
    std::random_device rd{};
    std::mt19937 mt{ rd() };   // 用 random_device 产出的随机值播种

    std::uniform_int_distribution<int> dist{1, 100};
    std::cout << "随机数: " << dist(mt) << "\n";
}

// ── 6. 调试技巧：固定种子 ───────────────────────────────────
//    调试时用固定种子，保证每次运行行为一致，方便定位 bug

void demo_debug() {
    constexpr unsigned int fixed_seed{ 5 };   // 固定种子
    std::mt19937 mt{ fixed_seed };

    std::uniform_int_distribution<int> dist{1, 100};
    // 每次运行输出完全相同，便于调试
    for (int i = 0; i < 5; ++i) {
        std::cout << dist(mt) << " ";
    }
    std::cout << "\n";
}
```
~~~

## 错误检查和处理

```cpp
#include <iostream>
#include <cstdlib>   // std::exit()

// ── 1. 错误来源 ──────────────────────────────────────────────
//    大多数错误来自程序员的错误假设，常发生在三个关键位置：
//    ① 假设被调用函数成功返回，实际失败了
//    ② 假设输入格式正确，实际并非如此
//    ③ 假设传入参数语义有效，实际无效
//    策略：不要只测"正确路径"，也要测试容易出错的边界路径

// ── 2. 策略一：在函数内部处理错误 ────────────────────────────
//    最佳策略：在出错的同一函数中恢复，不影响外部代码
//    方式 A：重试直到成功（如断网后循环检查）
//    方式 B：忽略错误或取消操作

// 忽略错误（静默处理）—— 调用方无法感知问题
void printDivision_silent(int x, int y)
{
    if (y != 0)
        std::cout << static_cast<double>(x) / y;
    // y == 0 时什么都不做，调用方不知道发生了什么
}

// 打印错误提示 —— 至少让运行者知道出错了
void printDivision_warn(int x, int y)
{
    if (y != 0)
        std::cout << static_cast<double>(x) / y;
    else
        std::cout << "Error: Could not divide by zero\n";
}

// ── 3. 策略二：将错误传回调用方 ──────────────────────────────
//    当错误无法在函数内部合理处理时，让调用方决定下一步
//    方式 A：void 函数改为返回 bool 表示成败

bool printDivision_bool(int x, int y)
{
    if (y == 0)
    {
        std::cout << "Error: could not divide by zero\n";
        return false;   // 失败
    }
    std::cout << static_cast<double>(x) / y;
    return true;        // 成功
}

// 方式 B：利用返回值中"不可能出现"的值表示错误
//   倒数 1/x 永远不会是 0.0，因此可用 0.0 表示错误
double reciprocal(double x)
{
    if (x == 0.0)
        return 0.0;     // 错误标记
    return 1.0 / x;
}

// ⚠️ 如果函数需要用到返回值的全部范围，则无法用返回值区分"有效值"和"错误值"

// ── 4. 策略三：致命错误（Fatal Error）────────────────────────
//    错误严重到程序无法继续正常运行 → 不可恢复错误
//    在 main() 中：return 非零值
//    在深层嵌套子函数中：std::exit() 直接终止

double doDivision_fatal(int x, int y)
{
    if (y == 0)
    {
        std::cout << "Error: Could not divide by zero\n";
        std::exit(1);   // 立即终止整个程序，参数为非零退出码
    }
    return static_cast<double>(x) / y;
}

// ── 5. 策略四：抛出异常（Exceptions）────────────────────────
//    当返回值不足以清晰传递错误时，C++ 提供了异常机制
//    错误沿调用栈向上传播，直到被 catch 捕获，或到达 main() 仍未处理则终止
//    异常处理将在后续章节详细介绍，此处仅作概念铺垫

// ── 6. 输出流选择：cout / cerr / 日志 ────────────────────────
//    经验法则：
//    • std::cout  → 面向用户的正常输出结果
//    • std::cerr  → 交互式程序的技术诊断/状态信息；
//                   非交互式程序（工具/服务）的错误输出
//    • 日志文件   → 事务性应用的事件记录（时间戳、进度、警告、错误）

void demo_streams()
{
    std::cout  << "[正常输出] 处理完成 75%\n";
    std::cerr  << "[诊断信息] 警告：配置文件使用了默认值\n";
    // 日志文件通常通过第三方库或手动文件流写入，此处略
}

// ── main ─────────────────────────────────────────────────────
int main()
{
    std::cout << "=== 2. 内部处理 ===\n";
    printDivision_silent(10, 0);
    printDivision_warn(10, 0);

    std::cout << "\n=== 3. 传回调用方 ===\n";
    if (!printDivision_bool(10, 0))
        std::cout << "调用方得知：除法失败\n";

    double r = reciprocal(0.0);
    if (r == 0.0)
        std::cout << "调用方得知：倒数计算失败\n";

    std::cout << "\n=== 6. 输出流 ===\n";
    demo_streams();

    // 致命错误演示（取消注释将终止程序）：
    // doDivision_fatal(10, 0);

    return 0;
}
```

## cin和处理无效输入

```cpp
#include <iostream>
#include <limits>    // std::numeric_limits
#include <cstdint>   // std::int16_t
#include <cstdlib>   // std::exit()

// ── 1. std::cin 提取原理 ───────────────────────────────────
//    使用 operator>> 将数据从缓冲区提取到变量中，称为"提取"
//    流程：① 缓冲区有数据则直接用；② 无数据则等待用户输入，按 Enter 后数据入缓冲区
//         ③ >> 跳过前导空白，尽可能多提取；④ 未提取的留在缓冲区供下次使用

void demo_buffer() {
    // 用户输入 "5a" 后按 Enter → 缓冲区为 "5a\n"
    int x{};
    std::cin >> x;   // 提取 '5' 转为 int 赋给 x，缓冲区剩余 "a\n"
    // 下一次提取会直接用 "a\n"，不会等待用户新输入
}

// ── 2. 三种输入验证方法 ─────────────────────────────────────
//    ① 边输入边校验（GUI 支持，std::cin 不支持）
//    ② 先提取到字符串，再解析验证（灵活但较复杂）
//    ③ 让 std::cin 尝试提取，失败后处理后果 ← 最常用，下面重点讲

// ── 3. 清空剩余输入的辅助函数 ─────────────────────────────
//    丢弃缓冲区中从当前位置到 '\n' 的所有字符（包括 '\n'）
//    用于处理"提取成功但有多余输入"的情况

void ignoreLine() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// ── 4. 错误类型 1：提取成功，但输入无意义 ───────────────────
//    例：要求输入 + - * /，用户却输入 'k'
//    解决：提取后用 switch / if 验证语义，无效则提示重试

char getOperator() {
    while (true) {
        std::cout << "Enter one of the following: +, -, *, or /: ";
        char op{};
        std::cin >> op;

        // 先处理可能的提取失败或 EOF
        if (!std::cin) {
            if (std::cin.eof()) std::exit(0);
            std::cin.clear();
            ignoreLine();
            std::cout << "Oops, that input is invalid. Please try again.\n";
            continue;
        }
        ignoreLine();  // 清掉多余输入

        switch (op) {
            case '+': case '-': case '*': case '/':
                return op;
            default:
                std::cout << "Oops, that input is invalid. Please try again.\n";
        }
    }
}

// ── 5. 错误类型 2：提取成功，但有多余输入 ───────────────────
//    例：要求输入 double，用户输入 "5*7" → 5 被提取，"*7\n" 留在缓冲区
//    后果：下一次提取会直接把 '*' 或 '7' 读走，跳过用户输入提示，输出混乱
//    解决：每次提取成功后调用 ignoreLine() 清掉剩余字符

double getDouble() {
    while (true) {
        std::cout << "Enter a decimal number: ";
        double x{};
        std::cin >> x;

        if (!std::cin) {           // 提取失败
            if (std::cin.eof()) std::exit(0);
            std::cin.clear();      // 将 cin 调回正常模式
            ignoreLine();          // 移除错误数据
            std::cout << "Oops, that input is invalid. Please try again.\n";
        } else {
            ignoreLine();          // ✅ 成功也清掉多余输入，防止污染下次提取
            return x;
        }
    }
}

// ── 6. 错误类型 3：提取失败 ──────────────────────────────────
//    例：要求输入 int，用户输入 "a" → 'a' 无法转为 int，提取失败
//    后果：① 变量被赋值为 0；② 错误字符留在缓冲区；③ cin 进入"故障模式"
//         故障模式下后续所有 >> 自动失败，程序陷入无限循环
//    解决：!std::cin 检测 → clear() 恢复 → ignoreLine() 清缓冲

// 已整合在 getDouble() 的 if (!std::cin) 分支中

// ── 7. 错误类型 4：提取成功但数值溢出 ───────────────────────
//    例：int16_t 范围 [-32768, 32767]，用户输入 40000
//    行为：cin 进入故障模式，变量被设为范围内最接近的值（如 32767）
//    处理：与提取失败相同，用 !std::cin 检测即可

void demo_overflow() {
    std::int16_t x{};  // 范围 -32768 ~ 32767
    std::cout << "Enter a number between -32768 and 32767: ";
    std::cin >> x;
    if (!std::cin) {
        std::cout << "Overflow or invalid input detected!\n";
        std::cin.clear();
        ignoreLine();
    }
}

// ── 8. EOF 处理 ─────────────────────────────────────────────
//    Unix 下 Ctrl+D 会关闭输入流，cin 进入故障模式且 clear() 无法修复
//    检测：std::cin.eof()，通常选择优雅退出程序

// 已整合在 getDouble() / getOperator() 的 eof() 分支中

// ── 9. 检测是否有额外输入（换行除外）────────────────────────
//    std::cin.peek() 查看缓冲区下一个字符但不提取
//    用于更精细的控制：提取成功后检查是否还有非换行残留

bool hasExtraneousInput() {
    return !std::cin.eof() && std::cin.peek() != '\n';
}

// ── 10. 完整计算器示例 ─────────────────────────────────────
void printResult(double x, char operation, double y) {
    switch (operation) {
        case '+': std::cout << x << " + " << y << " is " << x + y << '\n'; break;
        case '-': std::cout << x << " - " << y << " is " << x - y << '\n'; break;
        case '*': std::cout << x << " * " << y << " is " << x * y << '\n'; break;
        case '/': std::cout << x << " / " << y << " is " << x / y << '\n'; break;
        default:  std::cout << "Something went wrong: invalid operator.\n"; break;
    }
}

int main() {
    double x{ getDouble() };
    char op{ getOperator() };
    double y{ getDouble() };
    printResult(x, op, y);
    return 0;
}

std::cin >> x;          // 提取，跳过前导空白，遇空白停止
!std::cin               // 等价于 std::cin.fail()，检测上次提取是否失败
std::cin.clear();       // 清除错误标志，恢复 cin 正常模式
std::cin.eof();         // 检测是否到达文件尾（输入流被关闭）
std::cin.peek();        // 查看下一个字符但不提取
std::cin.ignore(n, '\n');  // 忽略最多 n 个字符，直到遇到 '\n'
std::numeric_limits<std::streamsize>::max()  // 配合 ignore 清空整行
```

## 断言

```cpp
#include <iostream>
#include <cassert>   // assert() 宏
#include <cmath>     // std::sqrt

// ── 1. 前置条件、不变量、后置条件 ────────────────────────────
//    前置条件：执行某段代码前必须为 true 的条件
//    不变量：  执行过程中必须保持为 true 的条件
//    后置条件：执行完成后必须为 true 的条件

// 传统做法：手动校验前置条件，失败则打印错误并返回
void printDivision_manual(int x, int y)
{
    if (y == 0) {                    // 校验前置条件
        std::cerr << "Error: Could not divide by zero\n";
        return;                      // 静默失败，可能掩盖真正问题
    }
    std::cout << static_cast<double>(x) / y;
}

// ── 2. assert 运行时断言 ───────────────────────────────────
//    头文件：<cassert>
//    行为：条件为 true → 什么都不做；条件为 false → 打印错误信息并 std::abort()
//    信息包含：表达式文本、文件名、行号 —— 极大方便定位 bug
//    assert 是少数被推荐使用的预处理器宏

double calculateTimeUntilObjectHitsGround(double initialHeight, double gravity)
{
    assert(gravity > 0.0);          // 前置条件：重力必须为正

    if (initialHeight <= 0.0)
        return 0.0;                  // 已经落地

    return std::sqrt((2.0 * initialHeight) / gravity);
}

// 触发断言时的典型输出（因编译器而异）：
// dropsimulator: src/main.cpp:6: double calculateTimeUntilObjectHitsGround(double, double):
// Assertion 'gravity > 0.0' failed.

// ── 3. 让断言更具描述性 ─────────────────────────────────────
//    技巧：用 && 连接字符串字面量
//    原理：字符串字面量恒为 true，不影响断言结果
//    效果：触发时字符串会出现在错误信息中，提供上下文

void demo_descriptive_assert()
{
    bool found{ false };
    // assert(found);                          // 信息太少
    assert(found && "Car could not be found in database");  // 更有描述性
}

// 也可用于标记"尚未实现"的功能点：
// assert(moved && "Need to handle case where student was just moved");

// ── 4. 断言 vs 错误处理 ─────────────────────────────────────
//    ┌──────────┬─────────────────────────────┬─────────────────────────────┐
//    │          │  assert（断言）             │  错误处理                   │
//    ├──────────┼─────────────────────────────┼─────────────────────────────┤
//    │ 目的     │ 捕获"不应该发生"的编程错误   │ 处理"可能发生"的运行时问题   │
//    │ 恢复     │ 不允许恢复，直接 abort        │ 可以恢复或优雅降级           │
//    │ 用户消息 │ 不友好，面向开发者调试        │ 友好，面向最终用户           │
//    │ 使用场景 │ 内部假设、前置条件校验        │ 外部输入、I/O、网络等        │
//    └──────────┴─────────────────────────────┴─────────────────────────────┘

// ── 5. NDEBUG：发布版本中禁用断言 ────────────────────────────
//    定义 #define NDEBUG 后，assert 宏被完全禁用，不产生任何代码
//    很多 IDE/构建系统会在 Release 配置中自动定义 NDEBUG
//    Visual Studio 默认：WIN32;NDEBUG;_CONSOLE
//    注意：assert 不应有副作用！因为 Release 中它会被移除

// ❌ 错误：assert 带有副作用
// assert(tryConnect() && "Connection failed");  // Release 中 tryConnect() 不会执行！

// ── 6. 断言的限制与警告 ─────────────────────────────────────
//    ① 断言本身可能写错 → 误报或漏报
//    ② 断言必须无副作用 → 调试版和发布版行为必须一致
//    ③ abort() 立即终止，不做任何清理 → 可能不关闭文件/数据库
//       因此断言只应在"意外终止不太会造成损坏"时使用

// ── 7. static_assert：编译时断言 ─────────────────────────────
//    关键字，不需要头文件
//    编译期检查，条件必须是常量表达式
//    失败时产生编译错误（而非运行时 abort）
//    C++17 起诊断信息可选

static_assert(sizeof(long) == 8, "long must be 8 bytes");      // 失败则编译报错
static_assert(sizeof(int) >= 4);                              // C++17 起可省略消息

// 可放在全局命名空间或任何代码位置

// ── main ─────────────────────────────────────────────────────
int main()
{
    // 正常调用
    std::cout << "Took " << calculateTimeUntilObjectHitsGround(100.0, 9.8)
              << " second(s)\n";

    // 触发断言（取消注释会 abort）：
    // std::cout << "Took " << calculateTimeUntilObjectHitsGround(100.0, -9.8)
    //           << " second(s)\n";

    return 0;
}
```

## 类型别名

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <utility>   // std::pair
#include <cstdint>   // std::int8_t

// ── 1. 类型别名（Type Alias）基础 ───────────────────────────
//    用 using 为现有类型创建新名字，编译时替换为原类型
//    语法：using 别名 = 现有类型;

using Distance = double;   // Distance 是 double 的别名

void demo_basic() {
    Distance miles{ 3.4 };           // 编译器看到 Distance → 替换为 double
    std::cout << miles << '\n';        // 输出 3.4
}

// ── 2. 命名约定 ─────────────────────────────────────────────
//    ① _t 后缀（C 风格，POSIX 保留，现代 C++ 不推荐）
//       例：size_t, nullptr_t
//    ② _type 后缀（标准库嵌套类型，但不一致）
//       例：std::string::size_type
//    ③ 无后缀，大写字母开头（现代 C++ 推荐）
//       例：Distance, StudentId
//    区分大小写：Distance（类型） vs distance（变量/参数）

// ── 3. 别名不是新类型 ───────────────────────────────────────
//    别名与原始类型完全可互换，编译器不区分
//    因此别名之间混用不会报错，但可能有语义问题

using Miles = long;
using Speed = long;

void demo_alias_not_type_safe() {
    Miles distance{ 5 };
    Speed mhz{ 3200 };
    distance = mhz;        // 语法合法：long = long，编译器不警告
    // 语义上把"频率"赋给"距离"是不合理的，但编译器无法阻止
}

// ── 4. 作用域 ─────────────────────────────────────────────
//    与变量相同：块内定义 → 块作用域；全局定义 → 全局作用域
//    跨文件使用：放在头文件中，#include 引入

// mytypes.h 示例：
// #ifndef MYTYPES_H
// #define MYTYPES_H
//     using Miles = long;
//     using Speed = long;
// #endif

// ── 5. typedef（旧式别名，不推荐）────────────────────────────
//    typedef 原类型 别名;   ← 容易记混顺序
//    复杂类型时更难读

typedef long Miles_old;                  // 旧式
using Miles_new = long;                  // 新式，推荐

// 函数指针类型：typedef 把别名藏中间，using 更清晰
typedef int (*FcnType_old)(double, char);       // 别名 FcnType 在中间
using FcnType_new = int(*)(double, char);       // 别名在等号左边，更易读

// ── 6. 用途一：平台无关编码 ─────────────────────────────────
//    用固定宽度的别名隐藏平台差异，配合预处理器

// #ifdef INT_2_BYTES
//     using int8_t  = char;
//     using int16_t = int;
//     using int32_t = long;
// #else
//     using int8_t  = char;
//     using int16_t = short;
//     using int32_t = int;
// #endif

// ⚠️ std::int8_t 通常是 signed char 的别名，用 cout 输出时会按字符打印
void demo_int8_trap() {
    std::int8_t x{ 97 };               // 通常是 signed char 的别名
    std::cout << x << '\n';            // 输出 'a'，不是 97！
    // 解决：static_cast<int>(x)
}

// ── 7. 用途二：简化复杂类型 ─────────────────────────────────
//    长类型名容易写错，用别名大幅简化

// 原始：
// bool hasDuplicates(std::vector<std::pair<std::string, int>> pairlist);

using VectPairSI = std::vector<std::pair<std::string, int>>;

bool hasDuplicates(VectPairSI pairlist) {   // 简洁多了
    return false;
}

void demo_simplify() {
    VectPairSI pairlist;                    // 初始化也简洁
}

// ── 8. 用途三：文档化返回值含义 ─────────────────────────────
//    返回类型本身不说明"这是什么"，别名可以自解释

// 不好：int 到底代表什么？
// int gradeTest();

// 更好：
using TestScore = int;
TestScore gradeTest();                      // 一看就知道返回"测试分数"

// ── 9. 用途四：简化代码维护 ─────────────────────────────────
//    改别名定义一处，不用满世界替换硬编码类型

// using StudentId = short;
using StudentId = long;                     // 只需改这里

// 所有用 StudentId 的地方自动变成 long
// ⚠️ 注意：换类型族（如 int → float，signed → unsigned）可能引入新 bug
//    必须彻底重新测试！

// ── 10. 使用建议 ────────────────────────────────────────────
//    • 主要用于提升可读性和可维护性的场景
//    • 在多处使用时代价最小、收益最大
//    • 避免滥用：利用率低的别名会隐藏熟悉的类型名，反而增加理解成本
//    • 复杂类型（容器、函数指针等）是最佳使用场景

// ── main ─────────────────────────────────────────────────────
int main() {
    demo_basic();
    demo_alias_not_type_safe();
    demo_int8_trap();
    demo_simplify();
    return 0;
}
```

## auto

```cpp
#include <iostream>
#include <string>
#include <string_view>

// ── 1. auto 类型推导基础 ─────────────────────────────────────
//    编译器根据初始值自动推导变量类型，省去重复书写类型
//    语法：auto 变量名 { 初始值 };

void demo_basic() {
    auto d{ 5.0 };          // 5.0 是 double 字面量 → d 为 double
    auto i{ 1 + 2 };        // 1+2 结果是 int → i 为 int
    auto x{ i };            // i 是 int → x 为 int
}

int add(int x, int y) { return x + y; }

void demo_from_function() {
    auto sum{ add(5, 6) };  // add() 返回 int → sum 为 int
}

// ── 2. 配合字面值后缀 ───────────────────────────────────────
//    用后缀控制推导出的具体类型

void demo_suffix() {
    auto a{ 1.23f };        // f 后缀 → float
    auto b{ 5u };           // u 后缀 → unsigned int
}

// ── 3. auto 的限制 ───────────────────────────────────────────
//    ① 必须有初始值（编译器需要依据）
//    ② 不能推导 void 或不完整类型

void foo() {}               // 返回 void

void demo_limits() {
    // auto x;              // ❌ 编译错误：无初始值，无法推导
    // auto y{ };           // ❌ 编译错误：空初始值，无法推导
    // auto z{ foo() };     // ❌ 编译错误：void 不能作为变量类型
}

// ── 4. const / constexpr 会被丢弃 ───────────────────────────
//    auto 推导时会去掉 const/constexpr，如需保留须显式写出

void demo_const_dropped() {
    const int cx{ 5 };      // cx 的类型是 const int
    auto y{ cx };           // y 的类型是 int（const 被丢掉）

    constexpr auto z{ cx }; // z 的类型是 constexpr int（手动加回）
}

// ── 5. 字符串字面量的陷阱 ───────────────────────────────────
//    "..." 推导为 const char*，不是 std::string！
//    要推导为 std::string 或 std::string_view，用 s / sv 后缀

void demo_string() {
    auto s1{ "Hello" };     // s1 是 const char*，不是 std::string

    using namespace std::literals;
    auto s2{ "goo"s };      // s 后缀 → std::string
    auto s3{ "moo"sv };     // sv 后缀 → std::string_view
}

// ── 6. auto 的优点 ───────────────────────────────────────────
//    ① 多个变量对齐，提升可读性
//    ② 强制初始化，避免未初始化变量
//    ③ 避免意外的性能损耗转换

void demo_advantages() {
    // 对齐美观
    auto c{ 5 };
    auto d{ 6.7 };

    // auto 必须给初始值，否则编译报错 → 防止忘记初始化
    // auto y;              // ❌ 编译错误

    // 避免隐式转换开销
    // std::string s1 { getStringView() };  // bad：可能隐式构造
    // auto s2 { getStringView() };          // good：直接推导为 string_view
}

// ── 7. auto 的缺点 ───────────────────────────────────────────
//    ① 隐藏类型信息，容易推导出非预期类型
//    ② 初始值类型变化会导致变量类型连锁变化

void demo_disadvantages() {
    auto y{ 5 };            // oops，想要 double 却给了 int 字面量 → y 是 int
    auto a{ 3 };
    auto b{ 2 };
    std::cout << a / b << '\n';  // oops，整数除法得 1，不是 1.5

    // 如果 add() 返回值从 int 改成 double，sum 的类型也会变
    // auto sum{ add(5, 6) + gravity };
}

// ── 8. 使用建议 ─────────────────────────────────────────────
//    现代 C++ 共识：auto 通常是安全的，可减少类型噪音
//    让代码逻辑更突出，但需确保初始值类型符合预期
//    复杂类型（如迭代器、lambda）用 auto 尤其划算

// ── main ─────────────────────────────────────────────────────
int main() {
    demo_basic();
    demo_from_function();
    demo_suffix();
    demo_const_dropped();
    demo_string();
    demo_advantages();
    demo_disadvantages();
    return 0;
}
```

# 函数重载

