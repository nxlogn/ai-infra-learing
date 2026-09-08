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

## delete说明符

```cpp
#include <iostream>

// ── 1. 为什么需要 =delete ─────────────────────────────────────
//    编译器会做隐式类型提升，把不想要的类型"硬塞"给函数
//    例如：char → int、bool → int，调用能通过编译但语义可疑

void printInt(int x) {
    std::cout << x << '\n';
}

void demo_problem() {
    printInt(5);     // okay：打印 5
    printInt('a');   // 打印 97 —— 'a' 被提升为 int，有意义吗？
    printInt(true);  // 打印 1  —— true 被提升为 int，有意义吗？
}

// ── 2. =delete 说明符：显式禁止某个重载被调用 ─────────────────
//    语法：函数声明后加 = delete;
//    语义：=delete 表示"我禁止这样做"，而不是"这不存在"

void printInt(char) = delete;  // 匹配到它 → 编译错误
void printInt(bool) = delete;  // 匹配到它 → 编译错误

void demo_delete() {
    printInt(97);    // okay：精确匹配 printInt(int)
    // printInt('a');   // ❌ 编译错误：精确匹配到已删除的 printInt(char)
    // printInt(true);  // ❌ 编译错误：精确匹配到已删除的 printInt(bool)
}

// ── 3. 关键规则：删除的函数仍参与重载决议 ─────────────────────
//    ① 删除的重载参与重载决议的所有阶段（不只是精确匹配）
//    ② 一旦"最佳匹配"是被删除的函数 → 编译错误
//    ③ 陷阱：printInt(5.0) 会报"不明确的匹配"而不是调用 int 版本
//       原因：printInt(char) 和 printInt(bool) 都能通过标准转换匹配
//       double，且都被删除，没有唯一最佳匹配 → 歧义

void demo_deleted_still_in_resolution() {
    // printInt(5.0);  // ❌ 编译错误：多个可匹配的函数（含被删除的）
    printInt(6);     // okay：精确匹配 int 版本，无歧义
}

// ── 4. 进阶：函数模板 + =delete 删除所有不匹配的重载 ───────────
//    逐个删除 char/bool/double... 太冗长
//    用一个删除的模板重载兜底：非 int 类型全部精确匹配模板 → 报错
//    （精确匹配优先于需要提升/转换的 int 版本）

void printIntOnly(int x) {
    std::cout << x << '\n';
}

template <typename T>
void printIntOnly(T x) = delete;  // 匹配除 int 外的所有类型 → 编译错误

void demo_template_delete() {
    printIntOnly(97);    // okay：精确匹配非模板的 int 版本
    // printIntOnly('a');   // ❌ 编译错误：匹配到删除的模板
    // printIntOnly(true);  // ❌ 编译错误：匹配到删除的模板
}

// ── main ─────────────────────────────────────────────────────
int main() {
    demo_problem();
    demo_delete();
    demo_deleted_still_in_resolution();
    demo_template_delete();
    return 0;
}
```

## 默认参数

```cpp
#include <iostream>
#include <string>

// ── 1. 默认参数基础 ───────────────────────────────────────────
//    给参数提供默认值：调用方传值则以传的值为准，未传则用默认值
//    本质：编译器在调用点把 print(3) 重写为 print(3, 4)

void print(int x, int y = 4) {
    std::cout << "x: " << x << ", y: " << y << '\n';
}

void demo_basic() {
    print(1, 2);  // 显式传值：y 用 2
    print(3);     // 省略 y：y 用默认值 4
}

// ── 2. 语法限制：只能用等号 ───────────────────────────────────
//    默认参数必须用 = 指定，括号或大括号初始化不符合语法

// void foo(int x = 5);    // ✅ ok
// void goo(int x ( 5 ));  // ❌ 编译错误
// void boo(int x { 5 });  // ❌ 编译错误

// ── 3. 多个默认参数与"右侧规则" ───────────────────────────────
//    规则：一旦某参数有默认值，它右边所有参数也必须有默认值
//    void print(int x = 10, int y);        // ❌ 不允许
//    也不支持 print(, , 3) 跳过中间参数的调用

void print3(int x = 10, int y = 20, int z = 30) {
    std::cout << "Values: " << x << ' ' << y << ' ' << z << '\n';
}

void demo_multi() {
    print3(1, 2, 3);  // 全部显式传值
    print3(1, 2);     // z 用默认值 30
    print3(1);        // y、z 用默认值
    print3();         // 全部用默认值
}

// ── 4. 默认参数不能重新声明 ───────────────────────────────────
//    同一文件中，前向声明和定义不能同时给默认参数
//    void print(int x, int y = 4);        // 前向声明给了
//    void print(int x, int y = 4) { }     // ❌ 重定义默认参数
//    最佳实践：默认参数写在头文件的前向声明中（其他文件可见），
//    没有前向声明时才写在函数定义里

// ── 5. 默认参数与函数重载：歧义陷阱 ───────────────────────────
//    带默认参数的重载本身合法，但调用可能不明确

void show(std::string s) { std::cout << "string: " << s << '\n'; }
void show(char c = ' ')  { std::cout << "char: " << c << '\n'; }

void demo_overload_ok() {
    show("Hello");  // 解析到 print(std::string)
    show('a');      // 解析到 print(char)
    show();         // 相当于 show(' ')，解析到 print(char)
}

void showNum(int x);
void showNum(int x, int y = 10);
void showNum(int x, double y = 20.5);
// 三个声明能通过编译，但注意调用歧义：

void demo_overload_ambiguity() {
    showNum(1, 2);     // ✅ 精确解析到 print(int, int)
    showNum(1, 2.5);   // ✅ 精确解析到 print(int, double)
    // showNum(1);     // ❌ 编译错误：不明确的调用
    // 三个候选（含默认参数）都可能匹配，编译器无法选择
}

// ── main ─────────────────────────────────────────────────────
int main() {
    demo_basic();
    demo_multi();
    demo_overload_ok();
    demo_overload_ambiguity();
    return 0;
}
```

## 函数模板

```cpp
#include <iostream>
#include <string>

// ── 1. 问题背景：相同实现的重载是维护噩梦 ─────────────────────
//    max(int,int) 和 max(double,double) 实现完全相同，只有类型不同
//    每支持一种类型就复制一份 → 违反 DRY 原则
//    且调用方可能用作者没预料到的类型调用 → 普通函数无解

int maxInt(int x, int y) {
    return (x < y) ? y : x;
}

// ── 2. 函数模板：用占位符类型代替具体类型 ─────────────────────
//    语法：template <typename T> + 函数定义
//    ① template <typename T> 是模板参数声明，作用域仅限紧随其后的模板
//    ② typename 和 class 在此处完全等价，推荐 typename
//    ③ 每个函数模板都需要自己的模板参数声明

template <typename T>
T maxT(T x, T y) {
    return (x < y) ? y : x;
}

// ── 3. 只有模板声明、没有定义 T 会编译失败 ─────────────────────
//    T max(T x, T y) { ... }   // ❌ 编译错误：T 未定义
//    这仍然是普通函数，不是函数模板

// ── 4. 模板的使用：编译器按需生成对应类型的函数 ───────────────
//    调用 maxT(1, 2) 时编译器生成 maxT<int>，
//    调用 maxT(1.5, 2.5) 时生成 maxT<double>
//    （具体实例化机制在下一节展开）

void demo_use() {
    std::cout << maxT(1, 2) << '\n';       // T 推导为 int → 2
    std::cout << maxT(1.5, 2.5) << '\n';   // T 推导为 double → 2.5
    std::cout << maxT('a', 'b') << '\n';   // T 推导为 char → b
    std::cout << maxT(std::string{"abc"}, std::string{"abd"}) << '\n';  // abd
}

// ── 5. 模板的优势：能和编写时不存在的类型一起工作 ─────────────
//    模板作者无需预测所有类型，使用时才确定实际类型
//    标准库（std::max、std::vector 等）大量依赖这一特性

// ── 6. 模板参数命名约定 ──────────────────────────────────────
//    ① 含义显而易见：单个大写字母 T、U、V
//    ② 含义不明显：描述性名称，两种风格
//       Allocator   —— 标准库风格（大写开头）
//       TAllocator  —— T 前缀风格（一眼看出是模板类型参数）

template <typename U, typename V>
void printPair(U first, V second) {
    std::cout << first << ", " << second << '\n';
}

void demo_naming() {
    printPair(1, 3.14);            // U=int, V=double
    printPair("age", 18);          // U=const char*, V=int
}

// ── 7. 进阶预告：三种模板参数 ─────────────────────────────────
//    ① 模板类型参数：表示类型（本节，最常用）
//    ② 模板非类型参数：表示 constexpr 值（数组章节讲）
//    ③ 模板模板参数：表示模板（后续课程）

// ── main ─────────────────────────────────────────────────────
int main() {
    demo_use();
    demo_naming();
    return 0;
}
```

## 函数模板实例化

```cpp
#include <iostream>
#include <string>

// ── 1. 实例化：模板是"函数工厂" ───────────────────────────────
//    函数模板本身不是函数，其代码不被直接编译执行
//    它唯一的职责：根据调用生成真正的函数（函数实例）
//    实例化 = 克隆模板 + 用实际类型替换 T
//    每个转换单元只在首次调用时实例化，后续调用复用

template <typename T>
T maxT(T x, T y) {
    return (x < y) ? y : x;
}

void demo_instantiate() {
    std::cout << maxT<int>(1, 2) << '\n';     // 实例化 maxT<int>(int, int)
    std::cout << maxT<int>(4, 3) << '\n';     // 复用已实例化的 maxT<int>
    std::cout << maxT<double>(1, 2) << '\n';  // 实例化 maxT<double>(double, double)
    // maxT<double> 参数是 double，传 int 会隐式转换为 double
}

// ── 2. 模板参数推导：三种调用语法 ─────────────────────────────
//    ① maxT<int>(1, 2)  显式指定 T
//    ② maxT<>(1, 2)     空尖括号：重载决议只考虑模板实例
//    ③ maxT(1, 2)       普通语法：模板 + 非模板重载都参与决议
//    最佳实践：用 ③，除非模板版本优于匹配的非模板函数

int maxInt(int x, int y) {              // 与模板同名的非模板函数
    std::cout << "非模板 max(int, int)\n";
    return (x < y) ? y : x;
}

void demo_deduction() {
    maxT<int>(1, 2);  // 强制走模板
    maxT<>(1, 2);     // 只考虑模板 → 实例化 maxT<int>
    maxT(1, 2);       // 优先调用非模板函数 maxInt（更专用）
}

// ── 3. 混合参数：模板参数 + 普通参数 ──────────────────────────
//    T 匹配任意类型，double 固定类型（float 会隐式提升）

template <typename T>
int someFcn(T, double) {
    return 5;
}

void demo_mixed() {
    someFcn(1, 3.4);     // T=int
    someFcn(1.2, 3.4);   // T=double
    someFcn(1.2f, 3.4);  // T=float
}

// ── 4. 语义陷阱：编译器只查语法，不查语义 ─────────────────────
//    实例化后的函数只要语法有效就能编译，语义是否合理是调用者的责任

template <typename T>
T addOne(T x) {
    return x + 1;
}

void demo_semantic_trap() {
    std::cout << addOne(1) << '\n';      // 2
    std::cout << addOne(2.3) << '\n';    // 3.3
    // std::string s{"hi"};
    // addOne(s);                        // ❌ 编译错误：string + 1 无意义（好在报错了）
    // std::cout << addOne("Hello") << '\n';  // ⚠️ 能编译！指针+1 → "ello"
    // 解法：模板特化 + =delete 封死语义不合理的类型
}

template <>
const char* addOne(const char* x) = delete;  // 禁止 const char* 实例化

// ── 5. 多文件规则：模板定义必须放头文件 ───────────────────────
//    编译器实例化时必须看到完整模板定义
//    定义放 .cpp → 调用方无法实例化 → 链接错误 LNK2019
//    放 .h 则不违反 ODR：模板定义允许多处相同定义，
//    且隐式实例化的函数是隐式 inline 的

// add.h:
//   template <typename T> T addOne(T x) { return x + 1; }
// main.cpp:
//   #include "add.h"   // 编译器看到定义，才能按需实例化

// ── 6. 泛型编程 ──────────────────────────────────────────────
//    模板类型 = 泛型类型；用模板编程 = 泛型编程
//    专注算法逻辑与数据结构设计，不受具体类型束缚

// ── main ─────────────────────────────────────────────────────
int main() {
    demo_instantiate();
    demo_deduction();
    demo_mixed();
    demo_semantic_trap();
    return 0;
}
```

# 复合类型，引用与指针

## 左值和右值

```cpp
// 值类别（左值 lvalue 与右值 rvalue）
#include <iostream>

// ── 1. 表达式的两个属性 ─────────────────────────────────────
//    每个表达式都有：类型 + 值类别
//    类型：编译时必须可确定（类型检查 / auto 推导的依据）
//    值：可在编译时（constexpr）或运行时确定
//    值类别：指示表达式解析为值、函数还是对象

void demo_expr_type() {
    auto v1{ 12 / 4 };    // int / int   → v1 是 int
    auto v2{ 12.0 / 4 };  // double/int  → v2 是 double（int 被转成 double）
}

// ── 2. 左值 lvalue ──────────────────────────────────────────
//    求值为"可识别的对象或函数"的表达式
//    有标识 → 可通过地址区分，生存期超过单个表达式
//    分两类：可修改左值 / 不可修改左值（const、constexpr）

void demo_lvalue() {
    int x{ 5 };
    int y{ x };              // x 是可修改左值
    const double d{ 1.2 };
    const double e{ d };     // d 是不可修改左值
    &x;                      // 取地址 OK → 左值铁证
}

// ── 3. 右值 rvalue ──────────────────────────────────────────
//    "不是左值的表达式"，求值为一个值
//    常见右值：字面值（C 字符串字面值除外！）、按值返回的
//    函数调用、运算符结果、static_cast 结果
//    特点：不可识别（临时值），必须立即使用，表达式结束即丢弃

int return5() { return 5; }

void demo_rvalue() {
    int a{ 5 };               // 5 是右值
    int z{ return5() };       // 按值返回的调用是右值
    int w{ a + 1 };           // 运算符结果是右值
    // &5;                    // ❌ 编译错误：5 是右值，不能取地址
    // &return5();            // ❌ 编译错误：return5() 是右值
}

// ── 4. 特例：C 风格字符串字面值是左值 ───────────────────────
//    "..." 本质是 C 风格数组，可退化为指针，为向后兼容
//    因此它是左值（但不可修改）

void demo_string_literal() {
    const char* p{ "Hello" }; // "Hello" 是左值，可取地址
    // p[0] = 'h';            // ❌ 但它是 const 数组，不可修改
}

// ── 5. 赋值的规则 ───────────────────────────────────────────
//    赋值要求：左操作数是可修改左值，右操作数是右值
//    所以 x = 5 合法，5 = x 非法

void demo_assign() {
    int x{};
    x = 5;                    // ✅ x 是可修改左值，5 是右值
    // 5 = x;                 // ❌ 编译错误：5 不是左值
}

// ── 6. 左值到右值的转换 ─────────────────────────────────────
//    期望右值的上下文若给了左值，会隐式转换为它存储的值
//    所以 x = y 中 y（左值）被转成值 2 后赋给 x
//    x = x + 1：左边 x 是左值，右边 x + 1 里 x 被转成右值

void demo_conversion() {
    int x{ 1 };
    int y{ 2 };
    x = y;                    // y 经左值→右值转换，取其值 2
    x = x + 1;                // 同一变量，左右两侧扮演不同角色
    std::cout << x << '\n';   // 输出 3
}

// ── 7. 判别技巧 ─────────────────────────────────────────────
//    拿不准时写 "&表达式;"：能编译通过的一定是左值
//    经验法则：
//    ① 左值：求值为变量等可识别对象，表达式结束后仍存在
//    ② 右值：求值为函数/运算符返回的值，表达式结束后丢弃
//    （C++11 为移动语义又加了 glvalue/prvalue/xvalue，后面再学）

// ── main ────────────────────────────────────────────────────
int main() {
    demo_expr_type();
    demo_lvalue();
    demo_rvalue();
    demo_string_literal();
    demo_assign();
    demo_conversion();
    return 0;
}
```

## 左值引用

```cpp
// 左值引用（lvalue reference）
#include <iostream>

// ── 1. 引用是对象的别名 ─────────────────────────────────────
//    对引用的操作全部作用于被引用对象
//    引用本质上与被引用的对象相同

void demo_alias() {
    int x{ 5 };
    int& ref{ x };            // ref 是 x 的别名
    std::cout << x << ' ' << ref << '\n';  // 输出 5 5
}

// ── 2. 通过引用读和写 ───────────────────────────────────────
//    ref 改 → x 也变；x 改 → ref 也变（因为是同一个东西）

void demo_modify() {
    int x{ 5 };
    int& ref{ x };
    x = 6;
    std::cout << ref << '\n'; // 6（x 改了，ref 跟着变）
    ref = 7;
    std::cout << x << '\n';   // 7（ref 改了，x 跟着变）
}

// ── 3. 引用必须初始化，且只能绑定可修改左值 ─────────────────
//    绑定过程叫"引用绑定"；左值引用 = 非常量左值引用

void demo_bind() {
    int x{ 5 };
    const int y{ 5 };
    int& ref{ x };            // ✅ 绑定可修改左值
    // int& invalidRef;       // ❌ 编译错误：引用必须初始化
    // int& bad1{ y };        // ❌ 编译错误：不能绑定 const 左值
    // int& bad2{ 0 };        // ❌ 编译错误：不能绑定右值
    // int& bad3{ 3.14 };     // ❌ 编译错误：类型必须匹配
}

// ── 4. 引用无法重置（经典陷阱！）────────────────────────────
//    初始化后永远指向原对象
//    ref = y 不是"改绑到 y"，而是等价于 x = y

void demo_no_rebind() {
    int x{ 5 };
    int y{ 6 };
    int& ref{ x };
    ref = y;                  // 意图：让 ref 改绑 y？
    std::cout << x << '\n';   // 实际输出 6！x 被赋成了 y 的值
}

// ── 5. 作用域与独立的生命周期 ───────────────────────────────
//    引用作用域同普通变量；引用与被引用对象生命周期独立
//    引用先销毁 → 对象无恙
//    对象先销毁 → 引用变成"悬空引用"，访问是未定义行为！

void demo_lifetime() {
    int x{ 5 };
    {
        int& ref{ x };        // ref 是 x 的引用
        std::cout << ref << '\n';
    }                         // ref 在这里销毁，x 不受影响
    std::cout << x << '\n';   // x 还是 5
}

// ── 6. 引用不是对象 ─────────────────────────────────────────
//    引用不需要占存储（编译器会优化掉）
//    不能引用引用：用引用初始化引用，只是绑定到原对象
//    int&& 不是"引用的引用"，C++11 里是右值引用语法

void demo_not_object() {
    int var{};
    int& ref1{ var };
    int& ref2{ ref1 };        // 不是引用的引用！ref2 绑定到 var
    ref2 = 42;
    std::cout << var << '\n'; // 42
    // 需要可重置的引用 → std::reference_wrapper（后续介绍）
}

// ── main ────────────────────────────────────────────────────
int main() {
    demo_alias();
    demo_modify();
    demo_bind();
    demo_no_rebind();
    demo_lifetime();
    demo_not_object();
    return 0;
}
```

## 常量的左值引用

```cpp
// 对常量的左值引用（const lvalue reference）
#include <iostream>

// ── 1. 常量引用：把被引用对象视为 const ─────────────────────
//    普通 int& 不能绑 const 变量（否则可借引用改常量）
//    const int& 可以，且不能通过它修改对象

void demo_const_ref() {
    const int x{ 5 };
    const int& ref{ x };      // ✅ 常量引用绑定 const 左值
    std::cout << ref << '\n'; // 可以读
    // ref = 6;               // ❌ 编译错误：不能通过常量引用修改
}

// ── 2. 绑定可修改左值：仅引用视角受限 ───────────────────────
//    通过 ref 不能改，但通过原标识符 x 仍可改
//    const 限制的是引用，不是底层对象

void demo_bind_modifiable() {
    int x{ 5 };
    const int& ref{ x };
    std::cout << ref << '\n';
    // ref = 7;               // ❌ 编译错误：ref 是常量视角
    x = 6;                    // ✅ 直接改 x 没问题
    std::cout << ref << '\n'; // 6（ref 看到的是新值）
}

// ── 3. 常量引用可以绑定右值！────────────────────────────────
//    会创建临时对象，常量引用绑定到该临时对象
//    普通左值引用做不到这一点

void demo_bind_rvalue() {
    const int& ref{ 5 };      // ✅ 5 是右值，创建临时对象绑定
    std::cout << ref << '\n'; // 输出 5
}

// ── 4. 生命周期扩展 ─────────────────────────────────────────
//    临时对象本该在表达式末尾销毁 → ref 会悬空
//    特殊规则：常量引用直接绑定临时对象时，
//    临时对象生命周期延长到与引用一致 → 安全
//    ⚠️ 仅限"直接绑定"；函数返回的临时对象不适用此规则

// ── 5. 三种绑定能力对比（常量引用更灵活）────────────────────
//                 int&        const int&
//    可修改左值    ✅ 读写      ✅ 只读
//    const 左值    ❌           ✅ 只读
//    右值          ❌           ✅（绑临时对象）
//    最佳实践：尽量用常量引用，除非需要修改被引用对象

void demo_compare() {
    int x{ 5 };
    const int y{ 5 };
    int& r1{ x };             // ✅
    // int& r2{ y };          // ❌
    // int& r3{ 5 };          // ❌
    const int& c1{ x };       // ✅
    const int& c2{ y };       // ✅
    const int& c3{ 5 };       // ✅
    std::cout << r1 + c1 + c2 + c3 << '\n';  // 5+5+5+5=20
}

// ── 6. constexpr 引用（选读）────────────────────────────────
//    constexpr 引用只能绑定静态存储期对象（全局 / static 局部）
//    因为地址必须是编译期常量；不能绑普通局部变量
//    引用 const 对象时需同时写 constexpr 和 const

int g_x{ 5 };

void demo_constexpr_ref() {
    constexpr int& ref1{ g_x };            // ✅ 全局变量
    static int s_x{ 6 };
    constexpr int& ref2{ s_x };            // ✅ 静态局部变量
    static const int s_y{ 6 };
    constexpr const int& ref3{ s_y };      // const 对象要加 const
    int x{ 6 };
    // constexpr int& ref4{ x };           // ❌ 不能绑非静态局部变量
    std::cout << ref1 + ref2 + ref3 << '\n';  // 17
}

// ── main ────────────────────────────────────────────────────
int main() {
    demo_const_ref();
    demo_bind_modifiable();
    demo_bind_rvalue();
    demo_compare();
    demo_constexpr_ref();
    return 0;
}
```

## 指针

```cpp
// 指针简介（pointer）
#include <iostream>
#include <typeinfo>

// ── 1. 取地址 & 与解引用 * ──────────────────────────────────
//    & 拿到对象的内存地址；* 访问地址处的值（返回左值）
//    两者互为逆操作：& 取对象的地址，* 取地址处的对象

void demo_addr_deref() {
    int x{ 5 };
    std::cout << x << '\n';       // 5：变量的值
    std::cout << &x << '\n';      // 十六进制地址
    std::cout << *(&x) << '\n';   // 5：地址处的值（= x）
}

// ── 2. & 和 * 的一词多义（靠上下文区分）─────────────────────
//    int& ref  → 左值引用（类型后）
//    &x        → 取地址（一元）
//    x & y     → 按位 AND（二元）
//    *ptr      → 解引用（一元）
//    x * y     → 乘法（二元）

void demo_ambiguity() {
    int x{ 6 }, y{ 3 };
    int& ref{ x };
    std::cout << (x & y) << '\n'; // 2：按位 AND
    std::cout << x * y << '\n';   // 18：乘法
    std::cout << ref << '\n';     // 6：引用
}

// ── 3. 指针：保存内存地址的对象 ─────────────────────────────
//    int* 是"指向 int 的指针"；星号贴类型名（最佳实践）
//    必须初始化（否则是野指针，解引用 = 未定义行为）
//    &x 的返回值本身就是 int* 类型

void demo_pointer_basic() {
    int x{ 5 };
    int* ptr{ &x };           // ptr 保存 x 的地址，"指向" x
    std::cout << *ptr << '\n';// 5：解引用取值
    std::cout << typeid(&x).name() << '\n';  // &x 的类型是 int*
    int* ptr2{};              // 空指针（好习惯）
    // int* ptr3{ 5 };        // ❌ 编译错误：不能用字面值初始化指针
}

// ── 4. 指针的两种赋值（重点！）──────────────────────────────
//    ptr = &y  → 改指向（ptr 换了地址）
//    *ptr = 6  → 改所指对象的值（x 被修改）

void demo_assign() {
    int x{ 5 };
    int y{ 6 };
    int* ptr{ &x };
    std::cout << *ptr << '\n';// 5
    ptr = &y;                 // 改指向 → 现在指向 y
    std::cout << *ptr << '\n';// 6
    *ptr = 7;                 // 解引用赋值 → y 变成 7
    std::cout << y << '\n';   // 7
}

// ── 5. 指针 vs 引用 ─────────────────────────────────────────
//    相同：都能间接访问/修改另一个对象
//    区别：
//    ① 引用取地址/解引用是隐式的，指针是显式的（&x / *ptr）
//    ② 引用必须初始化，指针不必（但有野指针风险）
//    ③ 引用不是对象，指针是（占存储）
//    ④ 引用不能改绑，指针可以换指向
//    ⑤ 引用必须绑对象，指针可以为空
//    ⑥ 引用安全，指针危险

void demo_vs_ref() {
    int x{ 5 };
    int& ref{ x };            // 隐式：直接当 x 用
    int* ptr{ &x };           // 显式：&x 取地址
    std::cout << ref << ' ' << *ptr << '\n';  // 5 5
}

// ── 6. 指针的大小与悬空指针 ─────────────────────────────────
//    大小与所指类型无关：32 位程序 4 字节，64 位 8 字节
//    悬空指针：保存已销毁对象的地址
//    解引用悬空指针 → 未定义行为
//    （但给悬空指针赋新值如 nullptr 是允许的）

void demo_dangling() {
    int x{ 5 };
    int* ptr{ &x };
    std::cout << *ptr << '\n';   // 有效
    {
        int y{ 6 };
        ptr = &y;
        std::cout << *ptr << '\n';   // 有效
    }                             // y 销毁，ptr 悬空！
    // std::cout << *ptr << '\n'; // ❌ 未定义行为
    ptr = nullptr;                // ✅ 赋新值是允许的
}

// ── main ────────────────────────────────────────────────────
int main() {
    demo_addr_deref();
    demo_ambiguity();
    demo_pointer_basic();
    demo_assign();
    demo_vs_ref();
    demo_dangling();
    return 0;
}
```

## 指针与常量

```cpp
// 指针与常量（pointer and const）
#include <iostream>

// ── 1. 普通指针不能指向 const 变量 ──────────────────────────
//    否则能通过指针修改常量，违反常量性

void demo_normal_limit() {
    const int x{ 5 };
    // int* ptr{ &x };         // ❌ 编译错误：const int* 不能转 int*
}

// ── 2. 指向常量的指针：const int* ───────────────────────────
//    const 在 * 左边 → 修饰所指向的值
//    不能通过指针改值，但可以换指向
//    可指向 const 或非常量变量（只读视角，同 const 引用）

void demo_ptr_to_const() {
    const int x{ 5 };
    const int y{ 6 };
    const int* ptr{ &x };     // 指向 const int
    // *ptr = 6;              // ❌ 编译错误：不能通过指针改常量
    ptr = &y;                 // ✅ 可以换指向
    std::cout << *ptr << '\n';// 6

    int v{ 5 };               // 非常量变量
    const int* p{ &v };       // 指向常量的指针也能指向它
    // *p = 6;                // ❌ 只读视角，不能改
    v = 6;                    // ✅ 但通过原标识符可以改
}

// ── 3. 指针常量：int* const ─────────────────────────────────
//    const 在 * 右边 → 修饰指针本身
//    必须初始化（同 const 变量），地址永远不变
//    但可以解引用修改所指向的值

void demo_const_ptr() {
    int x{ 5 };
    int y{ 6 };
    int* const ptr{ &x };     // ptr 永远指向 x
    // ptr = &y;              // ❌ 编译错误：指针常量不能换指向
    *ptr = 6;                 // ✅ 可以改所指向的值
    std::cout << x << '\n';   // 6
}

// ── 4. 指向常量的指针常量：const int* const ─────────────────
//    双 const：地址不能变，值也不能通过指针改
//    只能读；不能指向右值（右值没有地址）

void demo_both_const() {
    int value{ 5 };
    const int* const ptr{ &value };
    // ptr = nullptr;         // ❌ 不能换地址
    // *ptr = 6;              // ❌ 不能改值
    std::cout << *ptr << '\n';// 只能读：5
}

// ── 5. 四种组合总结表 ───────────────────────────────────────
//    int*                  改指向 ✅   改值 ✅
//    const int*            改指向 ✅   改值 ❌
//    int* const            改指向 ❌   改值 ✅
//    const int* const      改指向 ❌   改值 ❌
//    口诀：const 在 * 左 → 修饰值；const 在 * 右 → 修饰指针

void demo_summary() {
    int v{ 5 };
    int* ptr0{ &v };                   // 普通指针
    const int* ptr1{ &v };             // 指向常量
    int* const ptr2{ &v };             // 指针常量
    const int* const ptr3{ &v };       // 双 const
    *ptr0 = 1; *ptr2 = 2;              // 这两个能改值
    std::cout << *ptr1 << *ptr3 << v << '\n';
}

// ── main ────────────────────────────────────────────────────
int main() {
    demo_normal_limit();
    demo_ptr_to_const();
    demo_const_ptr();
    demo_both_const();
    demo_summary();
    return 0;
}
```

## 按指针传递参数

```cpp
// 通过指针传递函数参数（按地址传递）
#include <iostream>
#include <cassert>
#include <string>

// ── 1. 三种传参方式 ─────────────────────────────────────────
//    按值：拷贝对象，成本高，改副本
//    按引用：别名绑原对象，零拷贝
//    按地址：拷贝的是地址（4/8 字节，很快），解引用访问原对象

void printByValue(std::string val) {
    std::cout << val << '\n';       // 打印副本
}

void printByReference(const std::string& ref) {
    std::cout << ref << '\n';       // 无拷贝
}

void printByAddress(const std::string* ptr) {
    std::cout << *ptr << '\n';      // 解指针访问原对象，无拷贝
}

void demo_three_ways() {
    std::string str{ "Hello, world!" };
    printByValue(str);              // 拷贝
    printByReference(str);          // 引用
    printByAddress(&str);           // 传地址（&str）
}

// ── 2. 按地址传参允许修改实参 ───────────────────────────────
//    非常量指针参数：解引用赋值直接改原对象
//    只读则用指向常量的指针 const int*

void changeValue(int* ptr) {
    *ptr = 6;                       // 修改的是原对象
}

void demo_modify() {
    int x{ 5 };
    changeValue(&x);
    std::cout << x << '\n';         // 6，修改持续生效
}

// ── 3. 空指针检查（按地址传参的必修课）──────────────────────
//    调用方可能传入空指针 → 解引用 = 未定义行为
//    风格①：if (ptr) { ... }  正常逻辑嵌套在 if 内
//    风格②：if (!ptr) return; 快速返回，逻辑平铺（推荐）
//    空指针属"不应发生"时：assert(ptr) 文档化

void printSafe(const int* ptr) {
    assert(ptr);                    // 调试期捕获违规调用
    if (!ptr) return;               // 快速返回，防崩溃
    std::cout << *ptr << '\n';
}

void demo_null_check() {
    int x{ 5 };
    printSafe(&x);                  // 5
    printSafe(nullptr);             // 安全返回，不崩溃
}

// ── 4. 按地址 vs 按引用 ─────────────────────────────────────
//    按地址的劣势：
//    ① 只能传左值（&5 非法，右值无地址）
//    ② & 和 * 语法噪音
//    ③ 有解引用空指针的风险
//    const 引用可接受左值和右值，语法自然

void printByConstRef(const int& ref) {
    std::cout << ref << '\n';
}

void demo_ref_vs_addr() {
    printByConstRef(5);             // ✅ 常量引用能接右值
    // printByAddress(&5);          // ❌ 无法取右值的地址
}

// ── 5. 格言与最佳实践 ───────────────────────────────────────
//    "可以时通过引用传递参数，必须时才通过地址传递参数"
//    除非有特定理由（如需要判空语义、操作裸内存），首选引用

// ── main ────────────────────────────────────────────────────
int main() {
    demo_three_ways();
    demo_modify();
    demo_null_check();
    demo_ref_vs_addr();
    return 0;
}
```

# 枚举与结构体

## 非限定作用域枚举

```cpp
// ## 非限定作用域枚举
#include <iostream>

// ── 1. 从魔数到枚举 ──────────────────────────────────────
// 反面教材：int appleColor{0};  → 魔数，不直观
// 反面教材：constexpr int red{0}; + using Color=int; → 仍是 int，
//   Color eyeColor{8}; 语法正确但语义无意义，编译器无法拦截
// 枚举：值被限制在一组命名符号常量中，写错即编译错误
enum Color {
    red,       // 枚举元素隐式为 constexpr
    green,
    blue,      // 尾随逗号可选，推荐保留
};  // ❗ 枚举定义必须以分号结尾

// ── 2. 类型安全：初始值必须是已定义的枚举元素 ────────────
void demo_type_safety() {
    Color apple { red };    // ✅
    Color shirt { green };  // ✅

    // Color socks { white };  // ❌ 编译错误：white 不是 Color 的元素
    // Color hat   { 2 };      // ❌ 编译错误：2 不是 Color 的元素
    (void)apple; (void)shirt;
}

// ── 3. 不同枚举是不同的类型 ──────────────────────────────
// 每个 enum 都是独立类型（不同于类型别名与原类型视为相同）
enum Pet { cat, dog, pig, whale, };

void demo_distinct() {
    Pet myPet { dog };     // ✅
    // Pet other { blue };  // ❌ 编译错误：blue 不是 Pet 的元素
    (void)myPet;
}

// ── 4. 核心缺陷：元素泄漏到枚举所在作用域 ────────────────
// "非限定作用域"：元素名进入与枚举定义相同的作用域，不创建新作用域
// enum Feeling { happy, tired, blue, };  // ❌ blue 与 Color::blue 全局冲突
// 缓解方案：放进 namespace 提供独立作用域
namespace Feeling {
    enum Feeling {
        happy,
        tired,
        blue,  // Feeling::blue 不与 Color::blue 冲突
    };
}

// ── 5. 命名惯例 ──────────────────────────────────────────
// 枚举类型名大写开头；枚举元素小写开头
// ❌ 避免全大写（易与预处理宏冲突）、避免大写开头（易与类型名混淆）

// ── 6. 典型用法：状态码返回值（替代魔数 -1/-2/-3）───────
enum FileReadResult {
    readResultSuccess,
    readResultErrorFileOpen,
    readResultErrorFileRead,
    readResultErrorFileParse,
};

FileReadResult readFileContents() {
    return readResultSuccess;  // 示例省略文件操作
}

// 枚举小、拷贝便宜，按值传递/返回即可
void demo_status() {
    if (readFileContents() == readResultSuccess)  // 可用 == / != 比较
        std::cout << "读取成功\n";
}

// ── 7. 典型用法：函数选项参数（配 switch）────────────────
enum SortOrder { alphabetical, alphabeticalReverse, numerical, };

void sortData(SortOrder order) {
    switch (order) {
    case alphabetical:         std::cout << "字母序排序\n"; break;
    case alphabeticalReverse:  std::cout << "字母逆序排序\n"; break;
    case numerical:            std::cout << "数值序排序\n"; break;
    }
}

// ── main ─────────────────────────────────────────────────
int main() {
    demo_type_safety();
    demo_distinct();

    Color raspberry { Color::red };       // 非限定枚举元素也可加作用域访问
    std::cout << "raspberry = red\n";

    Feeling::Feeling me { Feeling::blue }; // 必须以命名空间为前缀
    std::cout << "I'm feeling blue\n";

    demo_status();
    sortData(numerical);
    return 0;
}
```

# class

## class简介

```cpp
// ## class 简介（类不变量的引入）
// 注：本卡片在 C++17 下编译
#include <cassert>
#include <iostream>

// ── 1. 没有不变量的 struct：成员彼此独立，怎么用都行 ─────
struct Date {
    int day {};
    int month {};
    int year {};
};

void printDate(const Date& date) {
    std::cout << date.day << '/' << date.month << '/' << date.year << '\n';
}

// ── 2. 类不变量：对象整个生存期内必须为真的条件 ─────────
// Fraction 的不变量：denominator 不能为 0（除 0 数学上未定义）
// 违反不变量 → 对象处于无效状态 → 后续使用可能是 UB
struct Fraction {
    int numerator { 0 };
    int denominator { 1 };  // 默认成员初始值：值初始化时保证有效（软防御）
};

void printFractionValue(const Fraction& f) {
    // 软防御：assert 只在出错时报警，不能"避免出错"
    assert(f.denominator != 0);
    std::cout << f.numerator / f.denominator << '\n';
}

void demo_invariant_violation() {
    Fraction good { 5, 2 };   // ✅ 有效状态
    printFractionValue(good);

    // Fraction bad { 5, 0 };   // ❌ 聚合初始化可以显式破坏不变量！
    // printFractionValue(bad); // 除零错误，程序终止
    // struct 没有任何机制阻止上面两行 —— 这正是 class 要解决的问题
}

// ── 3. 更复杂的跨成员不变量：成员联动靠人肉维护 ─────────
// struct Employee {
//     std::string name {};
//     char firstInitial {};  // 不变量：必须等于 name 首字母（或 '0'）
// };
// 改 name 必须同步改 firstInitial，靠开发者自觉 → 迟早出错

// ── 4. class 的目标 ──────────────────────────────────────
// 提供机制让对象"要么无法进入无效状态，要么立即报错"
// （而不是让 UB 在未来某个随机时刻爆发）

// ── 5. class 与 struct 技术上几乎相同 ────────────────────
class Date2 {
public:              // 访问说明符：使成员可被外部访问
    int m_day {};    // 成员变量惯用 m_ 前缀（原因后续课程讲）
    int m_month {};
    int m_year {};
};

void demo_class_same_as_struct() {
    Date2 date { 4, 10, 21 };  // 公有成员、无构造函数的 class 仍是聚合
    printDate(Date{ date.m_day, date.m_month, date.m_year });
    // 关键点：struct 与 class 可互相实现对方的功能，
    // 差别在于"使用方式"（访问控制、成员函数、封装），后续展开
}

// ── 6. 标准库大多数类型都是 class ────────────────────────
// std::string、std::string_view 等都是 class
// C++ 最初的名字："带类的C（C with Classes）"
void demo_std_is_class() {
    std::string s { "class 的实例" };  // 你早就在用类了
    std::cout << s << '\n';
}

// ── main ─────────────────────────────────────────────────
int main() {
    printDate({ 4, 10, 21 });
    demo_invariant_violation();
    demo_class_same_as_struct();
    demo_std_is_class();
    return 0;
}
```

## 访问说明符

```cpp
// ## 公共和私有成员以及访问说明符
#include <iostream>
#include <string>
#include <string_view>

// ── 1. 默认访问级别：struct 是 public，class 是 private ──
struct DateS {           // struct 默认全 public
    int year {};
    int day {};
};

class DateC {            // class 默认全 private
    int m_year {};       // m_ 前缀：区分成员与参数/局部变量
    int m_day {};        // 并避免与参数同名冲突（参数会遮蔽成员）
};

// ── 2. 私有成员 → 非聚合 → 聚合初始化失效 ────────────────
void demo_aggregate_loss() {
    DateS s { 2020, 14 };   // ✅ struct 是聚合，可聚合初始化
    // DateC c { 2020, 14 };  // ❌ 编译错误：有私有成员，非聚合
    (void)s;
}

// ── 3. class 的正确姿势：成员变量私有 + 成员函数公共 ─────
class Person {
    std::string m_name {};     // 私有：外部无法直接访问

public:                        // 访问说明符：其后所有成员直到下一个说明符
    void setName(std::string_view name) {
        m_name = name;         // m_ 前缀一眼看出改的是对象状态
    }

    void kisses(const Person& p) const {
        // 访问级别"按类"而非"按对象"：
        // p 是别的对象，但同类成员函数可以直接访问其私有成员
        std::cout << m_name << " kisses " << p.m_name << '\n';
    }
};

void demo_class_usage() {
    Person joe;
    joe.setName("Joe");        // 外部只能通过公共接口操作对象
    Person kate;
    kate.setName("Kate");
    joe.kisses(kate);

    // joe.m_name = "x";       // ❌ 编译错误：m_name 是 private
}

// ── 4. 访问级别摘要 ──────────────────────────────────────
//           本类成员   子类    外部 public
// public:      ✅       ✅        ✅
// protected:   ✅       ✅        ❌
// private:     ✅       ❌        ❌
// 说明符可乱序、可重复；class 省略开头 private: 合法但建议显式写出

// ── 5. struct vs class 使用准则（经验法则）───────────────
// 用 struct：简单数据集合 + 聚合初始化够用 + 无不变量/限制/清理
// 用 class：其他一切情况（成员变量私有、成员函数公共）
// 技术 diff 唯一重要点：默认访问级别（struct→public, class→private）
struct Config {   // ✅ 适合 struct：constexpr 全局数据、返回多值的载体
    int width {};
    int height {};
};

// ── main ─────────────────────────────────────────────────
int main() {
    DateS today { 2020, 14 };
    std::cout << today.year << '\n';

    demo_aggregate_loss();
    demo_class_usage();

    Config cfg { 800, 600 };
    std::cout << cfg.width << 'x' << cfg.height << '\n';
    return 0;
}
```

## 访问函数

当数据成员是 **private** 时，外部代码无法直接读写它们，那怎么合理地读取/修改这些值？答案是 **访问函数（access functions）**——普通的 public 成员函数，专门用于检索或更改私有成员。



**1. 两种访问函数**

- **Getter**（访问器）：返回私有成员的值，通常声明为 `const`（这样 const 和非 const 对象都能调用）
- **Setter**（修改器）：设置私有成员的值，必须是非 `const`（因为要修改成员）

**2. 命名约定（三种主流风格）**

- `getDay() / setDay()` —— 前缀 get/set，语义清晰，表明调用成本低
- `day() / day(int)` —— 无前缀，靠重载区分，标准库风格，但 `d.day(5)` 不够直观
- `day() / setDay()` —— 折中方案
- **最佳实践**：setter 强烈建议用 `set` 前缀（语义上明确"会改变对象状态"）；getter 可加可不加

**3. `m_` 前缀的一个重要作用**
C++ 不允许数据成员和 getter 同名（Java 可以），`m_` 前缀正好避免了命名冲突。

**4. Getter 的返回方式**

- 拷贝成本低 → **按值返回**
- 拷贝成本高（如大对象）→ **按 const 左值引用返回**（下一节展开）

**5. 务实的设计建议**（重点，面试/工程常用）

- 类没有不变量、又需要大量访问函数 → 干脆用 **struct**，直接暴露成员
- 优先实现**行为/操作**而非访问函数：比如不写 `setAlive(bool)`，而写 `kill()` 和 `revive()`
- 仅在公共接口确实需要时才提供 getter/setter



```cpp
// ── 1. 访问函数基础：getter 与 setter ──────────────────────
// 访问函数 = 检索/修改私有成员的普通 public 成员函数
// getter 通常 const（const 对象也能调用）；setter 必须非 const
#include <iostream>

class Date {
private:
    int m_year{ 2020 };   // m_ 前缀：避免与 getter 同名（C++ 不允许同名）
    int m_month{ 10 };
    int m_day{ 14 };

public:
    void print() const
    {
        std::cout << m_year << '/' << m_month << '/' << m_day << '\n';
    }

    int getYear() const { return m_year; }        // getter：const
    void setYear(int year) { m_year = year; }     // setter：非 const

    int getMonth() const { return m_month; }
    void setMonth(int month) { m_month = month; }

    int getDay() const { return m_day; }
    void setDay(int day) { m_day = day; }
};

void demo_basic()
{
    Date d{};
    d.setYear(2021);                              // 通过 setter 修改
    std::cout << "The year is: " << d.getYear() << '\n'; // 通过 getter 读取

    const Date cd{};                              // const 对象
    cd.print();                                   // ✅ print/getter 都是 const
    // cd.setYear(2000);                          // ❌ 编译错误：const 对象不能调用非 const 的 setter
}

// ── 2. 三种命名约定 ────────────────────────────────────────
// 1) get/set 前缀：语义清晰（上面已演示）
// 2) 无前缀（标准库风格）：getter 和 setter 同名，靠重载区分
// 3) 折中：getter 无前缀 + setter 带 set 前缀（推荐，setter 用 set 更能体现"会改变状态"）
class Point {
private:
    int m_x{ 0 };
    int m_y{ 0 };

public:
    int x() const { return m_x; }     // 无前缀 getter
    void x(int value) { m_x = value; } // 无前缀 setter（重载区分）
    int y() const { return m_y; }
    void setY(int value) { m_y = value; } // 折中风格：setter 带 set
};

void demo_naming()
{
    Point p{};
    p.x(5);          // 无前缀 setter：语义不够直观，不像"设置"
    std::cout << p.x() << '\n'; // 无前缀 getter：简洁，标准库风格
    p.setY(3);
    std::cout << p.y() << '\n';
}

// ── 3. getter 的返回方式：按值 or const 左值引用 ──────────
// 拷贝成本低（int、double 等标量）→ 按值返回
// 拷贝成本高（std::string、大对象）→ 按 const 左值引用返回
class Name {
private:
    std::string m_name{ "Boo" };

public:
    std::string name() const { return m_name; }              // 按值：拷贝成本可接受
    const std::string& nameRef() const { return m_name; }    // const 引用：避免拷贝
    void setName(const std::string& name) { m_name = name; } // setter 参数同理用 const 引用
};

void demo_return_type()
{
    Name n{};
    std::string copy{ n.name() };   // 得到一份副本，安全
    const std::string& ref{ n.nameRef() }; // 只读别名，无拷贝
    n.setName("Lee");               // 注意：引用指向的对象内容被改变
    std::cout << copy << ' ' << ref << '\n';
}

// ── 4. 务实的设计准则 ─────────────────────────────────────
// 1) 无不变量 + 大量访问函数 → 直接用 struct（成员 public）
// 2) 优先实现"行为"而非访问函数：kill()/revive() 好过 setAlive(bool)
// 3) 仅在公共接口确实需要时才提供 getter/setter
struct PlainData {   // 没有不变量约束 → 用 struct，直接访问成员
    int width{ 0 };
    int height{ 0 };
};

class Creature {     // 有业务含义 → 用行为代替 setter
private:
    bool m_alive{ true };

public:
    void kill() { m_alive = false; }
    void revive() { m_alive = true; }
    bool isAlive() const { return m_alive; } // 状态查询保留 getter
};

void demo_design()
{
    PlainData pd{};         // struct：直接访问，不需要 setter
    pd.width = 100;
    std::cout << pd.width << '\n';

    Creature c{};
    std::cout << c.isAlive() << '\n'; // 1
    c.kill();
    std::cout << c.isAlive() << '\n'; // 0
    // c.m_alive = true;               // ❌ 编译错误：m_alive 是私有成员，不能直接访问
}

// ── main ──────────────────────────────────────────────────
int main()
{
    demo_basic();
    demo_naming();
    demo_return_type();
    demo_design();
    return 0;
}
```

## 构造函数

```cpp
// ── 1. 聚合初始化的边界：私有成员让类不再是聚合 ────────────
// struct（全 public）→ 聚合初始化可用
// class（有私有成员）→ 不能聚合初始化，需要匹配的构造函数
#include <iostream>
#include <string_view>

struct AggFoo {          // 聚合：成员按定义顺序逐个初始化
    int x{};
    int y{};
};

class NonAggFoo {        // 有私有成员 → 不是聚合
private:
    int m_x{};
    int m_y{};

public:
    NonAggFoo(int x, int y) // 构造函数：与类同名、无返回类型
    {
        std::cout << "NonAggFoo(" << x << ", " << y << ") constructed\n";
    }
    void print() const
    {
        std::cout << "NonAggFoo(" << m_x << ", " << m_y << ")\n";
    }
};

void demo_aggregate()
{
    AggFoo af{ 6, 7 };       // ✅ 聚合初始化：af.x=6, af.y=7
    std::cout << af.x << ' ' << af.y << '\n';

    NonAggFoo nf{ 6, 7 };    // ✅ 匹配 NonAggFoo(int, int) 构造函数
    nf.print();              // 打印 0 0 ！构造函数体并未初始化成员
    // NonAggFoo bad{};      // ❌ 编译错误：无匹配构造函数（下一节的默认构造函数可解）
}

// ── 2. 构造函数参数的隐式转换 ──────────────────────────────
// 与普通函数一致：实参可隐式转换为形参类型即可匹配
void match_demo()
{
    NonAggFoo converted{ 'a', true }; // 'a'→int(97), true→int(1)，匹配成功
}

// ── 3. 构造函数不能是 const ───────────────────────────────
// 构造函数要初始化（修改）对象，所以不能 const
// const 对象的构造函数是隐式调用的，不受非 const 限制
class Something {
private:
    int m_x{};

public:
    Something()          // 非 const，但合法
    {
        m_x = 5;         // 只有非 const 的构造函数才能修改成员
    }
    int getX() const { return m_x; }
};

void demo_const_ctor()
{
    const Something s{}; // ✅ const 对象的构造函数是隐式调用的
    std::cout << s.getX() << '\n'; // 5
}

// ── 4. 构造函数 vs Setter ─────────────────────────────────
// 构造函数：在实例化点初始化整个对象
// setter：给已存在对象的单个成员赋值
class Point {
private:
    int m_x{};
    int m_y{};

public:
    Point(int x, int y) { m_x = x; m_y = y; } // 出生时整体初始化
    void setX(int x) { m_x = x; }             // 之后逐个修改
};

void demo_ctor_vs_setter()
{
    Point p{ 1, 2 };     // 构造：创建即完整
    p.setX(10);          // setter：局部修改已存在的对象
    std::cout << p.getX() << '\n'; // 需补 getX，此处示意
}

// ── main ──────────────────────────────────────────────────
int main()
{
    demo_aggregate();
    match_demo();
    demo_const_ctor();
    return 0;
}
```

## 构造函数成员初始化列表

```cpp
// ── 1. 成员初始化列表：正确的成员初始化方式 ────────────────
// 语法：参数列表后冒号开头，成员{初始值}，逗号分隔
// 只能用直接初始化（{}或()），不能用 = 复制初始化
#include <iostream>
#include <algorithm>

class Foo {
private:
    int m_x{};
    int m_y{};

public:
    Foo(int x, int y)
        : m_x{ x }       // ✅ 成员初始化列表：真正"初始化"
        , m_y{ y }       //    推荐格式：冒号换行缩进，逗号开头对齐
    {
        std::cout << "Foo(" << x << ", " << y << ") constructed\n";
    }
    void print() const
    {
        std::cout << "Foo(" << m_x << ", " << m_y << ")\n";
    }
};

void demo_init_list()
{
    Foo foo{ 6, 7 };
    foo.print();          // 这次 print 输出 6 7（上一节的 0 0 问题解决了）
    // Foo f2{ 6, 7 } 若写成 : m_x = x 形式 → ❌ 编译错误：列表不允许 = 
}

// ── 2. 初始化顺序陷阱：按类定义顺序，不是列表书写顺序 ──────
// m_x 定义在前 → 永远先初始化 m_x，即使列表里 m_y 写在前面
class BadOrder {
private:
    int m_x{};            // 定义在前，先初始化！
    int m_y{};

public:
    BadOrder(int x, int y)
        : m_y{ std::max(x, y) }, m_x{ m_y } // ❌ m_x 用了未初始化的 m_y → UB
    {
    }
    void print() const
    {
        std::cout << "BadOrder(" << m_x << ", " << m_y << ")\n";
    }
};

class GoodOrder {
private:
    int m_x{};            // 列表顺序与定义顺序一致
    int m_y{};

public:
    GoodOrder(int x, int y)
        : m_x{ std::max(x, y) }
        , m_y{ m_x }      // ✅ m_x 已初始化，安全
    {
    }
    void print() const
    {
        std::cout << "GoodOrder(" << m_x << ", " << m_y << ")\n";
    }
};

void demo_order()
{
    BadOrder b{ 6, 7 };   // m_x 是垃圾值！编译器一般会发警告
    b.print();
    GoodOrder g{ 6, 7 };
    g.print();            // GoodOrder(7, 7)
}

// ── 3. 三级优先级：列表 > 默认成员初始值 > 默认初始化 ──────
class Priority {
private:
    int m_x{};            // 有默认值，但列表优先 → 被忽略
    int m_y{ 2 };         // 有默认值且不在列表 → 用 2
    int m_z;              // 无默认值也不在列表 → 默认初始化 = 未初始化！

public:
    Priority(int x) : m_x{ x } {}
    void print() const
    {
        std::cout << "Priority(" << m_x << ", " << m_y << ", "
                  << m_z << ")\n";  // m_z 是垃圾值，读它 = UB
    }
};

void demo_priority()
{
    Priority p{ 6 };
    p.print();            // 例如 Priority(6, 2, -858993460)
    // 结论：每个成员要么进列表，要么给默认值，别让基本类型裸奔
}

// ── 4. 构造函数体是赋值，不是初始化（const/引用成员必踩坑）─
class BodyAssign {
private:
    const int m_id;       // const 成员：只能初始化，不能赋值
    int& m_ref;           // 引用成员：必须绑定时初始化

public:
    BodyAssign(int id, int& target)
        : m_id{ id }      // ✅ 初始化列表是 const/引用成员的唯一入口
        , m_ref{ target }
    {
        // m_id = id;     // ❌ 编译错误：const 成员不能在函数体赋值
        // m_ref = target; // ❌ 这是指向的变量被改写，不是重新绑定
    }
    int id() const { return m_id; }
    int ref() const { return m_ref; }
};

void demo_body_vs_list()
{
    int v{ 42 };
    BodyAssign b{ 7, v };
    std::cout << b.id() << ' ' << b.ref() << '\n'; // 7 42
}

// ── main ──────────────────────────────────────────────────
int main()
{
    demo_init_list();
    demo_order();
    demo_priority();
    demo_body_vs_list();
    return 0;
}
```

## 默认构造函数

默认构造函数 = 可无参调用；全默认参数也算；只能有一个；声明了构造函数就没了隐式版，用 `=default` 补回；`=default` 保留值初始化的零初始化而空体 `{}` 不保留；最后——默认值有意义才提供，否则让编译器帮你拦住非法对象

```cpp
// ── 默认构造函数笔记卡片开始 ──────────────────────────────
#include <iostream>
#include <string>
#include <string_view>

// ── 1. 默认构造函数：能"无参调用"的构造函数 ────
// 两种形式都算默认构造函数：无参构造 / 全参数有默认值
// 值初始化 Foo f{} 与 默认初始化 Foo f; 对类类型等价，均调用默认构造函数
// 最佳实践：一律用 {} 值初始化（对聚合也更安全）
class Foo1 {
public:
    Foo1() { std::cout << "Foo1 默认构造\n"; }
};
class Foo2 {
public:
    Foo2(int x = 0, int y = 0) : m_x{ x }, m_y{ y } // 全默认参数 => 也是默认构造函数
    { std::cout << "Foo2(" << m_x << ", " << m_y << ")\n"; }
private:
    int m_x{};
    int m_y{};
};

void demo_basic() {
    Foo1 f1{};   // 值初始化，调用 Foo1()
    Foo1 f1b;    // 默认初始化，同样调用 Foo1()
    Foo2 f2{};   // 用默认参数 (0,0) 调用 Foo2(int,int)
    Foo2 f2b{ 6, 7 };
}

// ── 2. 一个类只能有一个默认构造函数（二义性） ────
// Foo() 与 Foo(int=1, int=2) 同时存在时，Foo f{} 编译器不知调用哪个
class Foo3 {
public:
    Foo3() {}
    Foo3(int x = 1, int y = 2) : m_x{ x }, m_y{ y } {}
private:
    int m_x{};
    int m_y{};
};

void demo_ambiguous() {
    // Foo3 f{};  // ❌ 编译错误：默认构造函数调用有二义性
    Foo3 f{ 1 }; // 指定参数则无歧义，调用 Foo3(int,int)
    (void)f;
}

// ── 3. 隐式默认构造函数：声明了任何构造函数就不再生成 ────
// 类没有用户声明的构造函数 => 编译器生成隐式默认构造函数（空体）
// 一旦写了 Foo(int,int)，隐式默认构造函数消失，无参构造会失败
class Point {
public:
    Point(int x, int y) : m_x{ x }, m_y{ y } {}
private:
    int m_x{};
    int m_y{};
};

void demo_implicit_gone() {
    // Point p{};  // ❌ 编译错误：无匹配的构造函数（隐式默认构造函数已被抑制）
}

// ── 4. =default 显式默认构造函数（最佳实践） ────
// 手写空构造函数 Foo() {} 与 =default 行为不同（见第 5 节）
// 优先使用 =default
class Foo4 {
public:
    Foo4() = default;                       // 显式默认构造函数
    Foo4(int x) : m_x{ x } { (void)x; }     // 有参构造抑制了隐式生成，靠 =default 补回
private:
    int m_x{};
};

void demo_explicit_default() {
    Foo4 a{};      // 调用 =default 生成的默认构造函数
    Foo4 b{ 3 };   // 调用有参构造
    (void)a; (void)b;
}

// ── 5. =default 与空用户定义构造函数的关键区别 ────
// 值初始化 X{} 时：=default（或无构造函数）会先对整个对象零初始化
// 空体构造函数 X() {} 则没有零初始化阶段，无默认值的成员是未初始化的！
class UserEmpty {
public:
    UserEmpty() {} // 空体，不进行零初始化
    int a() const { return m_a; }
    int b() const { return m_b; }
private:
    int m_a;   // 无默认成员初始化器 => 值初始化后仍是垃圾值
    int m_b{}; // 有默认成员初始化器 => 安全
};
class Defaulted {
public:
    Defaulted() = default; // =default，零初始化阶段仍生效
    int a() const { return m_a; }
    int b() const { return m_b; }
private:
    int m_a;   // 值初始化时先被零初始化为 0，安全
    int m_b{};
};

void demo_default_vs_empty() {
    UserEmpty u{};
    Defaulted d{};
    std::cout << "空构造: a=" << u.a() << " b=" << u.b() << '\n'; // a 是垃圾值(UB)
    std::cout << "=default: a=" << d.a() << " b=" << d.b() << '\n'; // 0 0
    // 教训：给所有成员写默认成员初始化器 int m{};，彻底避免此类问题
}

// ── 6. 仅有意义时才提供默认构造函数 ────
// 默认值有意义（Fraction 默认 0/1）=> 提供默认构造
// 默认值无意义（雇员必须有名字和 ID）=> 不提供，让编译期直接报错
class Fraction {
public:
    Fraction() = default; // 默认 0/1
    Fraction(int n, int d) : m_n{ n }, m_d{ d } {}
    void print() const { std::cout << "Fraction " << m_n << '/' << m_d << '\n'; }
private:
    int m_n{ 0 };
    int m_d{ 1 };
};
class Employee {
public:
    Employee(std::string_view name, int id) : m_name{ name }, m_id{ id } {}
    void print() const { std::cout << "Employee(" << m_name << ", " << m_id << ")\n"; }
private:
    std::string m_name{};
    int m_id{};
};

void demo_when_to_provide() {
    Fraction f1{ 3, 5 };
    f1.print();     // Fraction 3/5
    Fraction f2{};
    f2.print();     // Fraction 0/1，默认值有意义

    Employee e1{ "Joe", 1 };
    e1.print();
    // Employee e2{};  // ❌ 编译错误：无匹配构造函数——没有名字的雇员无意义
}

// ── main ─────────────────────────────
int main() {
    demo_basic();
    demo_ambiguous();
    demo_implicit_gone();
    demo_explicit_default();
    demo_default_vs_empty();
    demo_when_to_provide();
    return 0;
}
// ── 默认构造函数笔记卡片结束 ──────────────────────────────
```

## 委托构造函数

多个构造函数的初始化列表和函数体往往高度相似（DRY 原则）。常见做法是抽一个私有成员函数（如 `printCreated()`）复用函数体逻辑，但初始化列表部分的重复无法消除

```cpp
// ── 委托构造函数笔记卡片开始 ──────────────────────────────
#include <iostream>
#include <string>
#include <string_view>

// ── 1. 构造函数体里"调用"另一个构造函数：行不通 ────
// 在构造函数体内写 Employee(name); 是编译错误
// 无参写法 Foo(); 更隐蔽：等价于 Foo{}，创建临时对象后立刻丢弃，无编译错误！
class Foo1 {
public:
    int x{};
    int y{};
    Foo1() { x = 5; }
    Foo1(int v) : y{ v }
    {
        // Foo1();  // ❌ 不是调用 Foo1()，而是值初始化一个临时 Foo1 对象并丢弃
        //          //    本对象的 x 仍是 0，且无任何编译警告
    }
};

void demo_naive_call() {
    Foo1 f{ 9 };
    std::cout << "Foo1: " << f.x << ' ' << f.y << '\n'; // 打印 0 9，而非期望的 5 9
    // 教训：不要从函数体里直接调用构造函数
}

// ── 2. 委托构造函数：把另一个构造函数放进初始化列表 ────
// 语法：Delegate(...) : Target{ args } { }  （构造函数链）
// 执行顺序：被委托构造函数完整执行（初始化列表+函数体）=> 委托者的函数体
// 铁律：初始化列表里委托了，就不能再初始化其他成员（二选一）
class Employee {
private:
    std::string m_name{};
    int m_id{ 0 };
public:
    Employee(std::string_view name)
        : Employee{ name, 0 } // 委托：参数少的 => 参数多的
    {
    }
    Employee(std::string_view name, int id) // 非委托构造函数（链的末端）
        : m_name{ name }, m_id{ id }
    {
        std::cout << "Employee " << m_name << " (" << m_id << ") created\n";
    }
};

void demo_delegate() {
    Employee e1{ "James" };  // 委托 => Employee(string_view, int) => 打印
    Employee e2{ "Dave", 42 }; // 直接调用末端构造函数
}

// ── 3. 委托循环与方向选择 ────
// A 委托 B、B 委托 A => 无限循环，栈耗尽崩溃；必须保证链末端是非委托构造函数
// 方向惯例：参数少的委托给参数多的；反过来则多余成员无处初始化
class Bad {
private:
    int a{};
    int b{};
public:
    Bad() : Bad{ 1 } {}        // A 委托 B
    Bad(int x) : Bad{}         // ❌ B 又委托 A：无限循环，运行时栈溢出
    {
        (void)x;
    }
};

void demo_cycle() {
    // Bad b{ 2 };  // ❌ 运行时崩溃：构造函数委托形成无限循环
}

// ── 4. 用默认参数减少构造函数数量 ────
// 默认参数只能放最右侧 => 最佳实践：
// 必须提供的成员先定义、作构造函数最左参数；有默认值的成员后定义、作最右参数
class Employee2 {
private:
    std::string m_name{}; // 必须提供 => 最左
    int m_id{ 0 };        // 可选     => 最右
public:
    Employee2(std::string_view name, int id = 0) // 一个构造函数覆盖两种调用
        : m_name{ name }, m_id{ id }
    {
        std::cout << "Employee2 " << m_name << " (" << m_id << ")\n";
    }
};

void demo_default_param() {
    Employee2 a{ "James" };
    Employee2 b{ "Dave", 42 };
}

// ── 5. 难题：默认值重复 与 static constexpr 解法 ────
// 委托/默认参数都无法引用"默认成员初始化器"的值 => 字面值 0 需写多处
// 解法：类内 static constexpr 常量，所有位置统一引用，值只定义一次
class Employee3 {
private:
    static constexpr int default_id{ 0 }; // 命名常量：默认值的唯一出处
    std::string m_name{};
    int m_id{ default_id };                          // 用在默认成员初始化器
public:
    Employee3(std::string_view name, int id = default_id) // 用在默认参数
        : m_name{ name }, m_id{ id }
    {
        std::cout << "Employee3 " << m_name << " (" << m_id << ")\n";
    }
};

void demo_named_constant() {
    Employee3 a{ "James" };
    Employee3 b{ "Dave", 42 };
}

// ── main ─────────────────────────────
int main() {
    demo_naive_call();
    demo_delegate();
    demo_cycle();
    demo_default_param();
    demo_named_constant();
    return 0;
}
// ── 委托构造函数笔记卡片结束 ──────────────────────────────
```

## 拷贝构造函数

```cpp
// ── 拷贝构造函数笔记卡片开始 ──────────────────────────────
#include <iostream>
#include <string>

// ── 1. 拷贝构造函数：用同类型已有对象初始化新对象 ────
// 隐式版本执行成员级逐一初始化，通常正是想要的 => 首选隐式
class Fraction {
private:
    int m_numerator{ 0 };
    int m_denominator{ 1 };
public:
    Fraction(int numerator = 0, int denominator = 1)
        : m_numerator{ numerator }, m_denominator{ denominator }
    {
    }
    // 手写拷贝构造函数：参数必须是（const）左值引用
    // 访问控制按"类"而非按"对象"，故可直接读 fraction 的 private 成员
    Fraction(const Fraction& f)
        : m_numerator{ f.m_numerator }
        , m_denominator{ f.m_denominator }
    {
        std::cout << "拷贝构造: (" << m_numerator << '/' << m_denominator << ")\n";
    }
    void print() const { std::cout << "Fraction(" << m_numerator << ", " << m_denominator << ")\n"; }
};

void demo_copy_ctor() {
    Fraction f{ 5, 3 };       // 调用 Fraction(int,int)
    Fraction fCopy{ f };      // 调用 Fraction(const Fraction&) 拷贝构造
    f.print();
    fCopy.print();
}

// ── 2. 参数为什么必须是引用 ────
// 若参数是 Fraction f（按值），传参本身又要调拷贝构造 => 无限递归，编译错误
// class Wrong {
// public:
//     Wrong(Wrong w) {}  // ❌ 编译错误：拷贝构造函数的参数不能按值传递
// };

// ── 3. 按值传参 / 按值返回 会隐式调用拷贝构造函数 ────
// 注意：编译器可能做拷贝省略优化，实际拷贝次数可能少于预期
void printFraction(Fraction f) // 按值传参 => 调用拷贝构造函数
{
    f.print();
}

Fraction makeFraction(int n, int d) {
    Fraction f{ n, d };
    return f; // 按值返回 => 理论上调用拷贝构造函数（可能被省略优化）
}

void demo_pass_by_value() {
    Fraction f{ 5, 3 };
    printFraction(f);                       // 拷贝 1 次
    Fraction f2{ makeFraction(1, 2) };      // 返回时可能拷贝（可能被省略）
    printFraction(f2);                      // 再拷贝 1 次
}

// ── 4. 拷贝构造函数不应有副作用 ────
// 编译器在特定场景允许省略拷贝 => 依赖拷贝时打印/计数等行为不可靠
// 正确姿势：拷贝构造函数只做复制

// ── 5. =default 与 =delete ────
class Defaulted {
public:
    Defaulted() = default;
    Defaulted(const Defaulted&) = default; // 显式请求默认拷贝构造函数（成员级复制）
};

class NoCopy {
public:
    NoCopy() = default;
    NoCopy(const NoCopy&) = delete;        // 禁止复制，拷贝尝试直接编译错误
};

void demo_default_delete() {
    Defaulted a{};
    Defaulted b{ a };  // OK：逐成员复制
    NoCopy c{};
    // NoCopy d{ c };  // ❌ 编译错误：拷贝构造函数已删除
    (void)b; (void)c;
}

// ── 6. 拷贝时机陷阱：聚合容器内拷贝不可省略 ────
// std::string 等类成员在成员级复制时执行深拷贝，注意性能
class Contact {
private:
    std::string m_name{ "anonymous" };
public:
    Contact() = default;
    Contact(const Contact& c) = default;   // string 成员用其自身的拷贝构造 => 深拷贝内容
    const std::string& name() const { return m_name; }
};

void demo_member_copy() {
    Contact a{};
    Contact b{ a };
    std::cout << "b.name = " << b.name() << '\n'; // "anonymous"，独立于 a 的副本
}

// ── main ─────────────────────────────
int main() {
    demo_copy_ctor();
    demo_pass_by_value();
    demo_default_delete();
    demo_member_copy();
    return 0;
}
// ── 拷贝构造函数笔记卡片结束 ──────────────────────────────
```

## 转换构造函数和explicit关键字

**转换构造函数**是一种特殊的构造函数，它能用**一个**其他类型的参数，隐式地把那个类型转换成当前类的对象。而 **`explicit` 关键字**的作用，就是**禁止**这种隐式转换，强制要求必须显式地调用构造函数。

// 在C++中，任何只接受一个参数的构造函数（或者虽然有多个参数，但除第一个外都有默认值的构造函数），都叫做转换构造函数。

```cpp
class MyString {
public:
    // 这是一个转换构造函数：它允许从 const char* 隐式转换为 MyString
    MyString(const char* s) {
        // 假设这里做了字符串拷贝
    }
};

void printString(MyString str) {
    // 打印 str
}

int main() {
    // 正常调用：直接传 MyString 对象
    printString(MyString("hello"));

    // !!! 转换构造函数的隐式转换生效了 !!!
    // 编译器看到 printString 需要 MyString，但你给了 const char*，
    // 它会自动调用 MyString(const char*) 来创建一个临时对象。
    printString("world");  // 这里发生了隐式转换，语法完全合法

    return 0;
}
```

```cpp
class MyString {
public:
    // 加上 explicit，禁止隐式转换
    explicit MyString(const char* s) {
        // 假设这里做了字符串拷贝
    }
};

void printString(MyString str) {
    // 打印 str
}

int main() {
    // 显式调用：完全没问题
    printString(MyString("hello"));

    // !!! 编译错误 !!!
    // 因为构造函数是 explicit 的，编译器不能再偷偷把 "world" 转成 MyString
    printString("world");  // 这行会报错

    // 但如果你用 C++ 的列表初始化（花括号），且是直接初始化，依然可以
    MyString s1{"hello"};  // OK
    // MyString s2 = "hello"; // 这也属于隐式转换，会报错（拷贝初始化）

    return 0;
}
```

### 为什么用explicit关键字？

1. **防止意外的类型转换**：隐式转换有时候会在你无意识的情况下发生，导致代码执行了你没预料到的操作，产生难以追踪的 bug。
2. **让代码意图更清晰**：阅读代码的人看到 `MyString("world")`，立刻就明白这里创建了一个临时对象。如果只写 `"world"`，阅读者需要去查类的定义才能知道发生了转换

## this指针

- **本质**：每个**非静态**成员函数都有一个隐藏的、名为 `this` 的 `const` 指针参数，它指向当前正在操作的那个对象。
- **编译器的幕后工作**：当你写下 `simple.setID(2)` 时，编译器会“偷偷”将它重写为类似 `Simple::setID(&simple, 2)` 的形式，把对象的地址作为参数传进去。
- **成员访问的实质**：函数内部对成员变量（如 `m_id`）的访问，实际上都被编译器加上了 `this->` 前缀，变成了 `this->m_id`。所以 `this->m_id` 和直接写 `m_id` 是完全等价的，后者只是前者的简写。

```cpp
struct Something {
    int data{};
    void setData(int data) {
        this->data = data; // this->data 是成员，data 是参数
    }
};
```

## 析构函数

对象销毁时清理工作**必然**要做，为什么不自动做呢？——这就是析构函数的意义：**对象销毁时自动执行的清理机制**

```cpp
#include <iostream>

class Simple {
private:
    int m_id {};
public:
    Simple(int id) : m_id { id } {
        std::cout << "Constructing Simple " << m_id << '\n';
    }
    ~Simple() {  // 析构函数
        std::cout << "Destructing Simple " << m_id << '\n';
    }
};

int main() {
    Simple simple1{ 1 };
    {                          // 嵌套作用域
        Simple simple2{ 2 };
    }                          // simple2 在这里销毁（作用域结束）
    return 0;
}                              // simple1 在这里销毁
```

Constructing Simple 1
Constructing Simple 2
Destructing Simple 2   ← 先销毁后构造的
Destructing Simple 1

## 静态成员变量

每个对象都有自己独立的 `value` 副本。但有时我们希望**所有对象共享同一份数据**——比如计数器、ID 生成器，这时就需要 `static`。**本质**：静态成员就是**放在类作用域里的全局变量**。它有静态存储期——程序启动时创建、结束时销毁，**和对象的生命周期完全无关**。哪怕一个对象都没创建，它也存在。

```cpp
class Whatever {
public:
    // ① 常量整型/枚举：本来就允许
    static const int s_value{ 4 };

    // ② inline 变量：任何类型都行（首选）
    static inline int s_count{ 0 };

    // ③ constexpr：隐式 inline，还支持类类型
    static constexpr double s_ratio{ 2.2 };
    static constexpr std::string_view s_view{ "Hello" };
};

class Something {
private:
    static inline int s_idGenerator{ 1 };  // 所有对象共享的计数器
    int m_id{};                            // 每个对象自己的 ID
public:
    Something() : m_id{ s_idGenerator++ } {}  // 取当前值并自增
    int getID() const { return m_id; }
};

int main() {
    Something first{}, second{}, third{};
    std::cout << first.getID() << '\n';   // 1
    std::cout << second.getID() << '\n';  // 2
    std::cout << third.getID() << '\n';   // 3
}
```

## 静态成员函数

静态成员变量如果设为 `private`，外界就没法直接访问了。用普通成员函数虽然可以访问它，但**必须先创建一个对象**才能调用，解决方案：把函数也声明为 `static`

```cpp
class Something {
private:
    static inline int s_value{ 1 };
public:
    static int getValue() { return s_value; }  // static 成员函数
};

int main() {
    std::cout << Something::getValue() << '\n';  // 不需要任何对象！
}
```

普通成员函数调用时隐式传入一个 `this` 指针指向当前对象。静态成员函数不作用于任何对象，所以**没有 `this`**；只能访问静态成员；

## 友元函数

前几节课一直在强调封装的好处：私有成员 + 公共接口。但有些场景会陷入两难：

- **职责分离**：比如“存储类”和“显示类”分开设计很合理，但显示类需要读存储类的私有数据才能工作
- **语法偏好**：有些功能写成非成员函数更自然（最典型的是后面的运算符重载，如 `cout << obj`）
- **不想污染公共接口**：为这些功能专门加 public 成员函数，会暴露过多实现细节、让接口变臃肿

我们需要一种**按个案精确开放访问权限**的机制——这就是 `friend`。

**友元权限由“被访问的类”自己授予**（在类内写 friend 声明），而不是由想访问的类自行决定。类的封装权始终在自己手里。

```cpp
class Accumulator {
private:
    int m_value{ 0 };
public:
    void add(int value) { m_value += value; }

    friend void print(const Accumulator& accumulator);  // 友元声明
};

// 注意：这是普通函数，不是成员函数！没有 Accumulator:: 前缀
void print(const Accumulator& accumulator) {
    std::cout << accumulator.m_value;  // ✅ 可以访问私有成员
}

int main() {
    Accumulator acc{};
    acc.add(5);
    print(acc);  // 直接调用，不是 acc.print()
}
```

## 友元类和友元成员函数

友元类则是授予**另一个类的所有成员函数**访问权

```cpp
class Storage {
private:
    int m_nValue{};
    double m_dValue{};
public:
    Storage(int nValue, double dValue)
        : m_nValue{ nValue }, m_dValue{ dValue } {}

    friend class Display;  // 授予 Display 类友元权限
};

class Display {
private:
    bool m_displayIntFirst{};
public:
    void displayStorage(const Storage& storage) {
        // Display 是 Storage 的友元 → 可访问其全部私有成员
        if (m_displayIntFirst)
            std::cout << storage.m_nValue << ' ' << storage.m_dValue << '\n';
        else
            std::cout << storage.m_dValue << ' ' << storage.m_nValue << '\n';
    }
};

friend void Display::displayStorage(const Storage& storage); // 单独授予一个函数权限
```

