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

# 内置类型和容器

Python 的**内置类型**是语言直接提供的数据类型，例如整数 `int`、字符串 `str`、列表 `list`。**容器**用于存放或组织多个对象，例如列表、元组、字典、集合。

因此，内置类型和容器不是两个互斥的类别：`list` 既是内置类型，也是容器。

## 1. 常见内置类型

| 分类   | 类型                 | 示例                | 说明                   |
| ------ | -------------------- | ------------------- | ---------------------- |
| 数值   | `int`                | `42`                | 整数                   |
| 数值   | `float`              | `3.14`              | 浮点数                 |
| 数值   | `complex`            | `1 + 2j`            | 复数                   |
| 布尔   | `bool`               | `True`、`False`     | 真、假                 |
| 空值   | `NoneType`           | `None`              | 表示没有值             |
| 文本   | `str`                | `"hello"`           | 字符序列               |
| 序列   | `list`               | `[1, 2, 3]`         | 可修改的序列           |
| 序列   | `tuple`              | `(1, 2, 3)`         | 不可修改的序列         |
| 序列   | `range`              | `range(5)`          | 整数范围序列           |
| 映射   | `dict`               | `{"name": "小明"}`  | 键值对                 |
| 集合   | `set`                | `{1, 2, 3}`         | 不重复元素的集合       |
| 集合   | `frozenset`          | `frozenset({1, 2})` | 不可变集合             |
| 二进制 | `bytes`、`bytearray` | `b"abc"`            | 不可变、可变的字节序列 |

可以查看或判断对象的类型：

```python
x = [1, 2, 3]

print(type(x))              # <class 'list'>
print(isinstance(x, list))  # True
```

## 2. 先理解“可变”和“不可变”

**可变**表示可以直接修改对象本身；**不可变**表示对象创建后，其值不能直接修改。

- 常见可变类型：`list`、`dict`、`set`、`bytearray`。
- 常见不可变类型：数值、`bool`、`str`、`tuple`、`range`、`bytes`、`frozenset`。

例如，列表可以原地修改：

```python
items = [10, 20]
items[0] = 99

print(items)  # [99, 20]
```

字符串不可以：

```python
text = "cat"
# text[0] = "b"  # TypeError

text = "bat"    # 可以：让变量指向另一个字符串
```

**变量重新赋值和修改对象是两回事。**“不可变”并不意味着变量以后不能再赋值。

## 3. 列表 `list`：存放一串可以修改的数据

列表有顺序、允许重复，并且可以存放不同类型的对象：

```python
items = [10, "hello", True]
numbers = [10, 20, 20, 30]
```

常用操作：

```python
nums = [10, 20, 30]

nums.append(40)        # 末尾添加一个元素
nums.extend([50, 60])  # 逐个添加多个元素
nums.insert(1, 15)     # 在索引 1 处插入 15
nums.remove(20)        # 删除第一个值为 20 的元素
last = nums.pop()      # 删除并返回最后一个元素
nums[0] = 99           # 修改元素

print(nums)           # [99, 15, 30, 40, 50]
print(last)           # 60
```

索引和切片：

```python
nums = [10, 20, 30, 40, 50]

print(nums[0])     # 10
print(nums[-1])    # 50
print(nums[1:4])   # [20, 30, 40]
print(nums[::2])   # [10, 30, 50]
print(nums[::-1])  # [50, 40, 30, 20, 10]
```

切片格式为 `序列[start:stop:step]`，包含起点、不包含终点。

适合：成绩列表、任务列表、需要不断添加或修改的数据。

## 4. 元组 `tuple`：元素位置固定的序列

元组与列表一样，有序、允许重复、支持索引和切片，但不能替换、添加或删除其中的元素。

```python
point = (10, 20)

print(point[0])  # 10
# point[0] = 99  # TypeError
```

元组经常用于组合几个相关的值，也支持解包：

```python
person = ("小明", 20)
name, age = person

print(name)  # 小明
print(age)   # 20
```

**只有一个元素时，逗号不能省略：**

```python
a = (10)   # int
b = (10,)  # tuple
```

元组不可变，但它引用的可变对象仍然可以修改：

```python
data = ([1, 2], "hello")
data[0].append(3)

print(data)  # ([1, 2, 3], 'hello')
```

这里没有替换元组中的元素，只是修改了那个列表的内容。

适合：坐标、固定结构的记录、函数返回多个值。

## 5. 字典 `dict`：通过键查找值

字典存放“键 → 值”的对应关系：

```python
student = {
    "name": "小明",
    "age": 20,
    "scores": [85, 90, 88],
}
```

常用操作：

```python
print(student["name"])            # 小明
print(student.get("city", "未知")) # 未知

student["age"] = 21               # 修改已有键的值
student["city"] = "上海"          # 添加新键值对
del student["age"]                # 删除键值对
```

直接使用 `student["不存在的键"]` 会抛出 `KeyError`；`get()` 可以指定找不到时的默认值。

遍历：

```python
for key, value in student.items():
    print(key, value)
```

需要记住：

- 键唯一；给同一个键重新赋值，会覆盖原来的值。
- 字典保留插入顺序，但不是按键自动排序。
- `in` 默认判断的是键是否存在。

```python
student = {"name": "小明", "age": 20}

print("name" in student)  # True
print("小明" in student)  # False
```

**键必须可哈希**，可以先理解为：能够提供稳定的哈希值，用于查找。字符串、整数以及元素均可哈希的元组可以作为键；列表、字典和集合不可以。

```python
locations = {(10, 20): "起点"}  # 可以用元组作键
# bad = {[10, 20]: "起点"}     # 列表不能作键
```

适合：用户信息、配置、根据编号查找记录。

## 6. 集合 `set`：去重和集合运算

集合中的元素不重复，不支持位置索引，也不保证遍历顺序。元素必须可哈希。

```python
nums = {1, 2, 2, 3}

print(len(nums))  # 3
print(2 in nums)  # True

nums.add(4)
nums.discard(2)   # 删除 2；不存在也不报错
```

集合运算：

```python
a = {1, 2, 3}
b = {3, 4, 5}

print(a & b)  # 交集：{3}
print(a | b)  # 并集：包含 1、2、3、4、5
print(a - b)  # 差集：{1, 2}
print(a ^ b)  # 对称差集：只在其中一个集合中出现的元素
```

创建空集合需要使用 `set()`：

```python
a = {}     # 空字典
b = set()  # 空集合
```

适合：去重、成员判断、比较两组数据的共同点和差异。

## 7. 字符串和 `range` 也是序列

字符串是不可变的文本序列，支持很多与列表相似的操作：

```python
text = "python"

print(len(text))       # 6
print(text[0])         # p
print(text[1:4])       # yth
print("py" in text)    # True：这里判断的是子串
```

`range` 表示一个整数范围，不需要把范围内的所有整数一次性存入列表：

```python
numbers = range(0, 10, 2)

print(numbers[2])      # 4
print(list(numbers))  # [0, 2, 4, 6, 8]
```

## 8. 容器的一个重要陷阱：赋值不会复制

```python
a = [1, 2]
b = a

b.append(3)

print(a)  # [1, 2, 3]
```

`a` 和 `b` 指向同一个列表，因此通过任意一个变量修改列表，另一个都能看到变化。

如果需要一个独立的外层列表：

```python
a = [1, 2]
b = a.copy()

b.append(3)

print(a)  # [1, 2]
print(b)  # [1, 2, 3]
```

不过，`copy()` 是**浅拷贝**：如果列表里还有列表，内部对象仍然共享。

```python
a = [[1, 2], [3, 4]]
b = a.copy()

b[0].append(99)

print(a)  # [[1, 2, 99], [3, 4]]
```

需要同时复制嵌套内容时，可以使用 `copy.deepcopy()`。

## 9. 如何选择容器

| 需求                           | 常用选择 |
| ------------------------------ | -------- |
| 保存有顺序、需要修改的一组数据 | `list`   |
| 保存结构固定的一组值           | `tuple`  |
| 根据名称、编号等键查找值       | `dict`   |
| 去重、判断成员、做集合运算     | `set`    |

还可以记住一个通用规则：**空字符串和空容器在条件判断中都是假，非空时都是真。**

```python
tasks = []

if not tasks:
    print("没有任务")
```

这比写 `if len(tasks) == 0:` 更简洁，也是常见的 Python 写法。

