# 基础

Python 的基础语法可以围绕**变量、条件、循环、函数和常用数据结构**来学。下面的例子都使用 Python 3。

## 1. 缩进与注释

Python 使用**缩进表示代码块**，通常每级缩进 4 个空格，不需要 `{}`，行末一般也不写分号。

```python
# 这是单行注释
age = 18

if age >= 18:
    print("已成年")
    print("可以进入")
```

`if` 后面需要冒号 `:`。两条缩进的语句都属于这个 `if`。

## 2. 变量与基本类型

变量直接赋值，不需要提前声明类型：

```python
name = "小明"       # str：字符串
age = 20            # int：整数
height = 1.75       # float：浮点数
is_student = True   # bool：布尔值，True 或 False
result = None       # 表示没有值
```

Python 是动态类型语言，同一个变量可以重新绑定不同类型的值：

```python
x = 10
x = "你好"
```

但不会自动把数字和字符串相加：

```python
age = 20
print("年龄：" + str(age))  # 显式转换成字符串
print(f"年龄：{age}")      # 更常用：f-string 格式化
```

## 3. 输入与输出

```python
name = input("请输入姓名：")
age = int(input("请输入年龄："))

print("你好", name)
print(f"明年你将满 {age + 1} 岁")
```

**`input()` 返回的总是字符串**，需要参与计算时通常要用 `int()` 或 `float()` 转换。

## 4. 运算符

| 类别         | 运算符            | 示例                     |
| ------------ | ----------------- | ------------------------ |
| 算术         | `+ - * /`         | `7 / 2` 得到 `3.5`       |
| 向下取整除法 | `//`              | `7 // 2` 得到 `3`        |
| 取余         | `%`               | `7 % 2` 得到 `1`         |
| 幂运算       | `**`              | `2 ** 3` 得到 `8`        |
| 比较         | `== != > < >= <=` | `age >= 18`              |
| 逻辑         | `and or not`      | `age >= 18 and age < 60` |
| 成员判断     | `in`、`not in`    | `"a" in "apple"`         |

注意：`=` 是赋值，`==` 才是比较是否相等。

```python
count = 0
count += 1   # 相当于 count = count + 1

# Python 支持连续比较
print(18 <= age < 60)
```

## 5. 条件判断

```python
score = 85

if score >= 90:
    print("优秀")
elif score >= 60:
    print("及格")
else:
    print("不及格")
```

程序从上到下判断，只执行第一个条件成立的分支。

## 6. 循环

**`for`：遍历一组数据**

```python
for fruit in ["苹果", "香蕉", "橙子"]:
    print(fruit)

for i in range(5):
    print(i)   # 依次输出 0、1、2、3、4
```

`range(start, stop, step)` 包含起点，不包含终点：

```python
for i in range(1, 6, 2):
    print(i)   # 1、3、5
```

**`while`：条件成立时一直执行**

```python
count = 0

while count < 3:
    print(count)
    count += 1
```

循环控制：

- `break`：结束当前循环。
- `continue`：跳过本轮剩余代码，进入下一轮。

```python
for i in range(5):
    if i == 1:
        continue
    if i == 4:
        break
    print(i)   # 0、2、3
```

## 7. 常用数据结构

| 类型         | 写法               | 特点                       |
| ------------ | ------------------ | -------------------------- |
| 列表 `list`  | `[1, 2, 3]`        | 有序，可以修改             |
| 元组 `tuple` | `(1, 2, 3)`        | 有序，元素位置不能修改     |
| 字典 `dict`  | `{"name": "小明"}` | 按键保存和查找值           |
| 集合 `set`   | `{1, 2, 3}`        | 元素不重复，不支持位置索引 |

**列表与切片**

```python
nums = [10, 20, 30, 40]

print(nums[0])    # 10：索引从 0 开始
print(nums[-1])   # 40：最后一个元素
print(nums[1:3])  # [20, 30]：包含起点，不包含终点

nums.append(50)   # 在末尾添加元素
nums[0] = 100     # 修改元素

print(len(nums))  # 5：元素数量
```

**字典**

```python
person = {"name": "小明", "age": 20}

print(person["name"])
person["age"] = 21
person["city"] = "北京"

for key, value in person.items():
    print(key, value)
```

**集合**

```python
numbers = {1, 2, 2, 3}
print(numbers)   # 只有 1、2、3，输出顺序不保证
```

空字典是 `{}`，空集合要写成 `set()`。

## 8. 字符串

单引号和双引号都可以表示字符串：

```python
text = "Hello Python"

print(text[0])                 # H
print(text[:5])                # Hello
print(text.lower())           # hello python
print(text.replace("Python", "World"))
```

字符串不能通过索引直接修改：

```python
# text[0] = "h"  # 会报错
text = "h" + text[1:]  # 创建新字符串，再赋给 text
```

## 9. 函数

用 `def` 定义函数，`return` 返回结果：

```python
def add(a, b):
    return a + b

result = add(3, 5)
print(result)   # 8
```

参数可以设置默认值：

```python
def greet(name, message="你好"):
    return f"{message}，{name}！"

print(greet("小明"))           # 你好，小明！
print(greet("小明", "早上好")) # 早上好，小明！
```

没有执行带值的 `return` 时，函数返回 `None`。

## 10. 列表推导式

用于根据已有数据生成新列表：

```python
squares = [x ** 2 for x in range(5)]
print(squares)   # [0, 1, 4, 9, 16]

evens = [x for x in range(10) if x % 2 == 0]
print(evens)     # [0, 2, 4, 6, 8]
```

第一条相当于：

```python
squares = []

for x in range(5):
    squares.append(x ** 2)
```

## 11. 异常处理

用 `try` 和 `except` 处理可能发生的错误：

```python
try:
    number = int(input("请输入一个整数："))
    print(10 / number)
except ValueError:
    print("输入的内容不是整数")
except ZeroDivisionError:
    print("不能除以零")
```

## 12. 导入模块

模块可以提供现成的函数和其他功能：

```python
import math

print(math.sqrt(16))  # 4.0
print(math.pi)
```

也可以只导入需要的内容：

```python
from math import sqrt

print(sqrt(25))  # 5.0
```

刚开始建议先练熟**变量 → 条件 → 循环 → 列表和字典 → 函数**。可以用下面这个小程序把它们串起来：

```python
def average(numbers):
    if not numbers:
        return 0
    return sum(numbers) / len(numbers)


scores = []

for i in range(3):
    score = float(input(f"请输入第 {i + 1} 门成绩："))
    scores.append(score)

avg = average(scores)

print(f"平均分：{avg:.2f}")  # 保留两位小数

if avg >= 60:
    print("平均分及格")
else:
    print("平均分不及格")
```



