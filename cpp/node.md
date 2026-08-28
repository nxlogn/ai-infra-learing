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

