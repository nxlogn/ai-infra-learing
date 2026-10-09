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

# 推导式

## 列表推导式

基本格式：

```python
[表达式 for 变量 in 可迭代对象]
```

例如，计算每个数字的平方：

```python
squares = [x ** 2 for x in range(5)]
print(squares)  # [0, 1, 4, 9, 16]
```

等价于：

```python
squares = []

for x in range(5):
    squares.append(x ** 2)
```

可以按这个顺序理解：**遍历数据 → 计算表达式 → 收集结果**。

## 加上筛选条件

```python
[表达式 for 变量 in 可迭代对象 if 条件]
```

例如，只保留偶数的平方：

```python
nums = [1, 2, 3, 4, 5, 6]

result = [x ** 2 for x in nums if x % 2 == 0]
print(result)  # [4, 16, 36]
```

这里先判断条件，条件成立才计算并收集结果。

## 区分“筛选”和“条件表达式”

**末尾的 `if` 用于筛选，可能减少元素数量：**

```python
result = [x for x in range(5) if x % 2 == 0]
print(result)  # [0, 2, 4]
```

**前面的 `if ... else ...` 用于决定每个元素生成什么值：**

```python
result = ["偶数" if x % 2 == 0 else "奇数" for x in range(5)]
print(result)  # ['偶数', '奇数', '偶数', '奇数', '偶数']
```

第二个例子没有过滤，每个输入都对应一个输出。

## 字典推导式和集合推导式

字典推导式需要生成键和值：

```python
squares = {x: x ** 2 for x in range(4)}
print(squares)  # {0: 0, 1: 1, 2: 4, 3: 9}
```

集合推导式会自动去重：

```python
remainders = {x % 3 for x in range(10)}
print(remainders)  # 包含 0、1、2，顺序不保证
```

## 多层循环的推导式

例如，把二维列表展开成一维列表：

```python
matrix = [
    [1, 2, 3],
    [4, 5, 6],
]

flat = [value for row in matrix for value in row]
print(flat)  # [1, 2, 3, 4, 5, 6]
```

多个 `for` 的顺序与普通嵌套循环一致：

```python
flat = []

for row in matrix:
    for value in row:
        flat.append(value)
```

推导式太长、条件太复杂时，普通循环通常更容易读。

## 圆括号得到的是生成器

```python
numbers = (x ** 2 for x in range(3))
```

这不是“元组推导式”，而是**生成器表达式**。它按需计算，不会立即生成完整列表：

```python
print(next(numbers))  # 0
print(next(numbers))  # 1
print(next(numbers))  # 4
```

生成器用完后就耗尽了。如果需要元组，可以显式转换：

```python
numbers = tuple(x ** 2 for x in range(3))
print(numbers)  # (0, 1, 4)
```

## 4. 把三者放在一起

假设有一组学生成绩，要取前三名记录，并找出其中及格的学生姓名：

```python
students = [
    ("小明", 90),
    ("小红", 55),
    ("小刚", 80),
    ("小丽", 95),
]

names = [name for name, score in students[:3] if score >= 60]

print(names)  # ['小明', '小刚']
```

这一行包含了三个动作：

1. `students[:3]`：**切片**，取前三条记录。
2. `name, score`：**解包**，将每条记录拆成姓名和成绩。
3. `[name ... if score >= 60]`：**推导式**，筛选及格记录并收集姓名。

# 闭包

Python 的**闭包（closure）**，指的是：**内部函数使用了外层函数的变量，即使外层函数已经执行结束，内部函数仍然能访问这些变量。**

可以先把它理解成：**函数带着它需要的外部环境一起被保留下来。**

## 1. 从一个例子开始

```python
def make_adder(n):
    def add(x):
        return x + n

    return add
```

调用它：

```python
add_five = make_adder(5)

print(add_five(3))  # 8
print(add_five(10)) # 15
```

执行过程是：

1. `make_adder(5)` 中，`n` 为 `5`。
2. 定义内部函数 `add`，它使用了外层的变量 `n`。
3. `return add` 返回函数对象，注意这里没有 `()`。
4. 外层函数结束后，返回的 `add` 仍然能够访问 `n`。

因此，`add_five(3)` 相当于计算 `3 + 5`。

每次调用外层函数，都可以创建独立的环境：

```python
add_five = make_adder(5)
add_ten = make_adder(10)

print(add_five(2))  # 7
print(add_ten(2))   # 12
```

**闭包保留的是变量的绑定，并不是简单地把当时的值复制进函数。** 这一点在后面的循环例子里很重要。

## 2. 闭包与变量作用域

Python 查找变量时，一般按 **LEGB** 顺序：

| 层级      | 含义                            |
| --------- | ------------------------------- |
| Local     | 当前函数的局部作用域            |
| Enclosing | 外层嵌套函数的作用域            |
| Global    | 当前模块的全局作用域            |
| Built-in  | 内置作用域，例如 `len`、`print` |

在前面的例子中：

```python
def make_adder(n):
    def add(x):
        return x + n
    return add
```

- `x` 是 `add` 的局部变量。
- `n` 来自外层函数作用域，对于 `add` 来说是**自由变量**。
- `add` 通过闭包保留对 `n` 的访问。

仅仅访问全局变量，一般不称为闭包：

```python
n = 5

def add(x):
    return x + n  # 查找的是全局变量
```

## 3. 修改外层变量：`nonlocal`

闭包不仅可以读取外层变量，还可以保存不断变化的状态。例如计数器：

```python
def make_counter():
    count = 0

    def counter():
        nonlocal count
        count += 1
        return count

    return counter
```

使用：

```python
counter = make_counter()

print(counter())  # 1
print(counter())  # 2
print(counter())  # 3
```

这里的：

```
nonlocal count
```

表示：**`count` 使用外层函数中已有的绑定，不要把它当作当前函数的新局部变量。**

如果不写：

```python
def make_counter():
    count = 0

    def counter():
        count += 1
        return count

    return counter
```

调用 `counter()` 时会报 `UnboundLocalError`。

因为 `count += 1` 包含赋值，Python 会把 `count` 当成内部函数的局部变量，但加一之前，它还没有被赋值。

可以这样区分：

- `nonlocal`：重新绑定外层函数中的变量。
- `global`：重新绑定模块级的全局变量。

## 4. 修改对象，不一定需要 `nonlocal`

如果只是修改外层变量指向的可变对象，没有给变量重新赋值，就不需要 `nonlocal`：

```python
def make_collector():
    items = []

    def collect(value):
        items.append(value)
        return items.copy()

    return collect
collect = make_collector()

print(collect("苹果"))  # ['苹果']
print(collect("香蕉"))  # ['苹果', '香蕉']
```

这里 `items.append(value)` 修改的是列表本身，没有重新绑定 `items`。

对比：

```python
items.append(value)       # 修改对象，不需要 nonlocal
items = items + [value]   # 重新赋值，需要 nonlocal
```

注意，`items += [value]` 也包含赋值操作，因此在这种情况下同样需要声明 `nonlocal items`。

## 5. 同一次调用创建的闭包可以共享状态

```python
def make_account():
    balance = 0

    def deposit(amount):
        nonlocal balance
        balance += amount

    def get_balance():
        return balance

    return deposit, get_balance
deposit, get_balance = make_account()

deposit(100)
deposit(50)

print(get_balance())  # 150
```

`deposit` 和 `get_balance` 来自同一次 `make_account()` 调用，共享同一个 `balance`。

再次调用 `make_account()`，则会得到另一份独立的状态。

## 6. 常见陷阱：循环中的闭包

看这个例子：

```python
def make_functions():
    funcs = []

    for i in range(3):
        funcs.append(lambda: i)

    return funcs


funcs = make_functions()
print([f() for f in funcs])  # [2, 2, 2]
```

为什么不是 `[0, 1, 2]`？

因为这三个函数使用的是**同一个外层变量 `i`**。调用它们时，循环已经结束，`i` 的值是 `2`。

这叫作**延迟绑定**：使用自由变量的值发生在函数执行时，而不是创建函数时。

#### 方法一：使用默认参数固定每次的值

```python
def make_functions():
    funcs = []

    for i in range(3):
        funcs.append(lambda i=i: i)

    return funcs


print([f() for f in make_functions()])  # [0, 1, 2]
```

`lambda i=i: i` 中：

- 左边的 `i` 是函数参数。
- 右边的 `i` 是创建函数时的外层变量值。
- 默认参数在函数创建时求值。

这里通过默认参数保存了当时的值，函数体中的 `i` 已经是局部参数。

#### 方法二：每次调用工厂函数，创建独立绑定

```python
def make_value(value):
    def get_value():
        return value
    return get_value


funcs = [make_value(i) for i in range(3)]

print([f() for f in funcs])  # [0, 1, 2]
```

每次 `make_value(i)` 都创建一个独立的 `value`，所以不会共享同一个循环变量。

## 7. 闭包有什么用？

闭包常用于：

- **定制函数**：例如创建“加 5”“乘 10”的函数。
- **保存状态**：例如计数器、缓存。
- **装饰器**：包装一个函数，同时保留对原函数的访问。
- **回调函数**：让回调保留执行时需要的上下文。

例如创建不同折扣的计算函数：

```python
def make_discount(rate):
    def calculate(price):
        return price * rate
    return calculate


discount_80 = make_discount(0.8)
discount_90 = make_discount(0.9)

print(discount_80(100))  # 80.0
print(discount_90(100))  # 90.0
```

学习闭包时，重点抓住三件事：**内部函数访问外层变量；外层函数结束后绑定仍然可以保留；重新赋值外层变量时使用 `nonlocal`。**

# 类，继承，特殊方法

Python 中，**类**用于把数据和操作这些数据的方法组织在一起；**继承**让新类复用、扩展已有类；**特殊方法**让对象支持 `print()`、`len()`、`+` 等内置操作。

先从一个简单的类开始，再逐步加入继承和特殊方法。

## **1. 类和对象**

类描述一种对象具有哪些属性、能做哪些事；实例是根据这个类创建的具体对象。

```python
class Student:
    def __init__(self, name, score):
        self.name = name
        self.score = score

    def introduce(self):
        return f"我是{self.name}，成绩是{self.score}"
```

创建和使用实例：

```python
s1 = Student("小明", 90)
s2 = Student("小红", 85)

print(s1.name)         # 小明
print(s2.score)        # 85
print(s1.introduce())  # 我是小明，成绩是90

s1.score = 95
```

这里：

- `class Student`：定义类。
- `Student(...)`：创建实例。
- `self.name`、`self.score`：实例属性，每个学生分别保存自己的数据。
- `introduce()`：实例方法。
- `__init__()`：实例创建后执行的初始化方法。

`self` 表示调用方法的那个实例。调用：

```python
s1.introduce()
```

可以理解为：

```python
Student.introduce(s1)
```

Python 自动把实例传给第一个参数。`self` 是约定名称，不是关键字，但应当遵守这个约定。

## **2. 实例属性和类属性**

实例属性属于各个实例；类属性定义在类中，可以由实例共同访问。

```python
class Student:
    school = "第一中学"  # 类属性

    def __init__(self, name):
        self.name = name  # 实例属性
a = Student("小明")
b = Student("小红")

print(a.name)         # 小明
print(b.name)         # 小红
print(Student.school) # 第一中学
print(a.school)       # 第一中学
```

修改类属性：

```python
Student.school = "第二中学"

print(a.school)  # 第二中学
print(b.school)  # 第二中学
```

但通过实例赋值，通常会创建同名实例属性，遮住类属性：

```python
a.school = "实验中学"

print(a.school)        # 实验中学
print(b.school)        # 第二中学
print(Student.school) # 第二中学
```

一个常见错误是把每个实例应当独立拥有的列表写成类属性：

```python
class Team:
    members = []  # 所有实例访问的是同一个列表
```

如果希望各个队伍有自己的成员列表，应放进 `__init__`：

```python
class Team:
    def __init__(self):
        self.members = []
```

## **3. 继承：复用和扩展已有类**

例如，狗和猫都属于动物：

```python
class Animal:
    def __init__(self, name):
        self.name = name

    def speak(self):
        return "发出声音"


class Dog(Animal):
    def speak(self):
        return "汪汪"


class Cat(Animal):
    def speak(self):
        return "喵喵"
```

`Dog(Animal)` 表示 `Dog` 继承 `Animal`。

```python
dog = Dog("旺财")

print(dog.name)     # 旺财
print(dog.speak())  # 汪汪
```

`Dog` 没有定义 `__init__`，因此使用继承来的初始化方法；它重新定义了 `speak()`，这叫作**方法重写**。

可以检查继承关系：

```python
print(isinstance(dog, Dog))     # True
print(isinstance(dog, Animal))  # True
print(issubclass(Dog, Animal))  # True
```

## **4. 用 `super()` 扩展继承的方法**

如果子类需要额外的初始化，可以调用已有的初始化逻辑：

```python
class Dog(Animal):
    def __init__(self, name, breed):
        super().__init__(name)
        self.breed = breed

    def speak(self):
        return f"{self.name}：汪汪"
dog = Dog("旺财", "柴犬")

print(dog.name)   # 旺财
print(dog.breed)  # 柴犬
```

如果子类定义了自己的 `__init__`，Python 不会自动再执行父类的 `__init__`，所以这里显式调用：

```python
super().__init__(name)
```

在单继承中，可以先把 `super()` 理解为访问父类的方法。更准确地说，它按**方法解析顺序（MRO）**继续查找方法，这对多继承尤其重要。

Python 支持多继承：

```python
class C(A, B):
    pass
```

可以通过 `C.__mro__` 查看方法查找顺序。初学时先掌握单继承即可。

## **5. 多态：相同操作，不同表现**

不同对象可以提供同名方法：

```python
animals = [
    Dog("旺财", "柴犬"),
    Cat("咪咪"),
]

for animal in animals:
    print(animal.speak())
```

输出：

```
旺财：汪汪
喵喵
```

调用方只需要调用 `speak()`，具体行为由对象决定。

Python 也不强制这些对象必须继承同一个类：

```python
class Robot:
    def speak(self):
        return "你好，人类"


def make_sound(obj):
    print(obj.speak())


make_sound(Robot())  # 你好，人类
```

这种关注“对象能做什么”的方式，常被称为**鸭子类型**。

## **6. 特殊方法：让对象支持 Python 的通用操作**

特殊方法通常以双下划线开头和结尾，例如 `__init__`、`__len__`。

你在类中定义它们，Python 会在对应操作发生时调用。

| 特殊方法       | 对应操作                    | 作用                   |
| -------------- | --------------------------- | ---------------------- |
| `__init__`     | `MyClass(...)` 的初始化阶段 | 初始化实例             |
| `__str__`      | `str(obj)`、`print(obj)`    | 提供易读的字符串       |
| `__repr__`     | `repr(obj)`                 | 提供适合调试的表示     |
| `__len__`      | `len(obj)`                  | 返回长度               |
| `__getitem__`  | `obj[key]`                  | 支持索引、切片或键访问 |
| `__iter__`     | `iter(obj)`、`for`          | 返回迭代器             |
| `__contains__` | `x in obj`                  | 成员判断               |
| `__eq__`       | `a == b`                    | 判断相等               |
| `__add__`      | `a + b`                     | 定义加法               |
| `__call__`     | `obj(...)`                  | 让实例可以被调用       |

通常使用右侧的常规语法即可，例如写 `len(obj)`。

**7. `__str__` 和 `__repr__`**

```python
class Student:
    def __init__(self, name, score):
        self.name = name
        self.score = score

    def __str__(self):
        return f"{self.name}：{self.score}分"

    def __repr__(self):
        return f"Student(name={self.name!r}, score={self.score!r})"
s = Student("小明", 90)

print(s)        # 小明：90分
print(repr(s))  # Student(name='小明', score=90)
print([s])      # [Student(name='小明', score=90)]
```

- `__str__` 侧重方便阅读。
- `__repr__` 侧重调试，尽量清楚、明确。
- 两者都必须返回字符串。
- 如果没有定义 `__str__`，默认实现会使用 `__repr__`。

`!r` 表示在格式化时使用 `repr()`，所以字符串会带上引号。

## **8. 用特殊方法实现一个小容器**

```python
class BookShelf:
    def __init__(self, books):
        self.books = list(books)

    def __len__(self):
        return len(self.books)

    def __getitem__(self, index):
        return self.books[index]

    def __iter__(self):
        return iter(self.books)

    def __contains__(self, book):
        return book in self.books
```

现在这个类的实例就可以支持熟悉的容器操作：

```python
shelf = BookShelf(["Python入门", "算法基础", "计算机网络"])

print(len(shelf))            # 3
print(shelf[0])              # Python入门
print(shelf[:2])             # ['Python入门', '算法基础']
print("算法基础" in shelf)   # True

for book in shelf:
    print(book)
```

这里 `shelf[:2]` 会把一个 `slice` 对象传给 `__getitem__`。因为内部列表本身支持切片，所以直接转交给它即可。

## **9. 用 `__add__` 和 `__eq__` 定义运算**

例如二维向量：

```python
class Vector:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __add__(self, other):
        if not isinstance(other, Vector):
            return NotImplemented
        return Vector(self.x + other.x, self.y + other.y)

    def __eq__(self, other):
        if not isinstance(other, Vector):
            return NotImplemented
        return self.x == other.x and self.y == other.y

    def __repr__(self):
        return f"Vector({self.x}, {self.y})"
a = Vector(1, 2)
b = Vector(3, 4)

print(a + b)                # Vector(4, 6)
print(a == Vector(1, 2))    # True
print(a is Vector(1, 2))    # False
```

这里：

- `==` 使用自定义的相等规则。
- `is` 判断是不是同一个对象，不能通过 `__eq__` 改写。
- `NotImplemented` 表示当前方法不支持这组操作数，让 Python 尝试其他适用的处理方式。它与 `NotImplementedError` 异常不同。

## **10. `__call__` 与之前的闭包联系起来**

之前用闭包实现过计数器，也可以用类实现：

```python
class Counter:
    def __init__(self):
        self.count = 0

    def __call__(self):
        self.count += 1
        return self.count
counter = Counter()

print(counter())  # 1
print(counter())  # 2
print(counter())  # 3
```

`counter` 是实例，但定义了 `__call__` 后，就能像函数一样调用。这里状态保存在 `self.count` 中；闭包版本则把状态保存在外层函数的变量中。

当状态简单、主要提供一个操作时，闭包通常很方便；当需要管理多个属性、提供多个相关操作时，类通常更容易组织。

# 可变对象，引用，浅拷贝和深拷贝

理解这几个概念，关键是先记住：**Python 的变量绑定到对象；赋值通常不会复制对象。**

例如：

```python
a = [1, 2, 3]
b = a
```

此时不是创建了两个列表，而是两个变量引用同一个列表：

```python
a ──┐
    ├──> [1, 2, 3]
b ──┘
```

下面从这个关系逐步展开。

## **1. 可变对象与不可变对象**

“可变”指的是：**对象创建后，能否修改它本身的内容。**

| 类型                        | 是否可变 |
| --------------------------- | -------- |
| `list`、`dict`、`set`       | 可变     |
| `int`、`float`、`bool`      | 不可变   |
| `str`、`tuple`、`frozenset` | 不可变   |

列表可以原地修改：

```python
a = [1, 2, 3]
a.append(4)
a[0] = 99

print(a)  # [99, 2, 3, 4]
```

字符串不能原地修改：

```python
s = "hello"

# s[0] = "H"  # TypeError
s = "Hello"  # 可以：让变量 s 绑定到另一个字符串
```

这里要区分两件事：

- **修改对象**：对象还是原来那个，内容变了。
- **重新赋值**：变量改为引用另一个对象。

不可变限制的是对象，不是变量能否重新赋值。

## **2. 引用：多个变量可以指向同一个对象**

```python
a = [1, 2]
b = a

b.append(3)

print(a)  # [1, 2, 3]
print(b)  # [1, 2, 3]
```

通过 `b` 修改列表，`a` 也能看到，因为它们访问同一个对象。

但给 `b` 重新赋值，不会改变 `a` 的绑定：

```python
a = [1, 2]
b = a

b = [8, 9]

print(a)  # [1, 2]
print(b)  # [8, 9]
```

重新赋值之后：

```python
a ──> [1, 2]
b ──> [8, 9]
```

不可变对象也可以被多个变量引用，只是不能原地修改：

```python
a = 10
b = a

b = b + 1

print(a)  # 10
print(b)  # 11
```

`b + 1` 得到一个结果对象，再把 `b` 绑定到它；整数 `10` 本身没有变化。

## **3. `==` 与 `is`：值相等和同一个对象**

```python
a = [1, 2]
b = [1, 2]
c = a

print(a == b)  # True：列表内容相等
print(a is b)  # False：不是同一个列表
print(a is c)  # True：引用同一个列表
```

- `==`：按类型定义的规则比较是否相等。
- `is`：判断是否为同一个对象。

判断数字或字符串的值是否相等，使用 `==`。判断是否为 `None`，通常使用：

```python
if value is None:
    print("没有值")
```

不要依赖某些整数或字符串可能被复用的现象来使用 `is` 比较值。

## **4. 浅拷贝：复制外层，内部对象仍然共享**

先看一个简单列表：

```python
a = [1, 2, 3]
b = a.copy()

print(a is b)  # False

b.append(4)
print(a)      # [1, 2, 3]
print(b)      # [1, 2, 3, 4]
```

`a.copy()` 创建了一个新的外层列表。

但是，**新列表里的元素仍然引用原来的那些对象**。嵌套列表能清楚地体现这一点：

```python
a = [[1, 2], [3, 4]]
b = a.copy()

print(a is b)        # False：外层列表不同
print(a[0] is b[0])  # True：内部列表相同
```

关系可以表示为：

```
a ──> 外层列表 A ──┬──> 内部列表 [1, 2]
                  └──> 内部列表 [3, 4]
                         ↑       ↑
b ──> 外层列表 B ─────────┴───────┘
```

所以修改内部列表会互相影响：

```python
b[0].append(99)

print(a)  # [[1, 2, 99], [3, 4]]
print(b)  # [[1, 2, 99], [3, 4]]
```

但替换 `b` 中的某个元素，只影响 `b` 的外层列表：

```python
b[0] = ["新列表"]

print(a)  # [[1, 2, 99], [3, 4]]
print(b)  # [['新列表'], [3, 4]]
```

这两种操作的区别是：

```python
b[0].append(99)  # 修改共享的内部对象
b[0] = [...]    # 修改 b 的外层列表，让它引用另一个对象
```

常见的浅拷贝写法：

```
b = a.copy()       # 列表、字典、集合等提供的方法
b = a[:]          # 列表的完整切片
b = list(a)       # 从已有列表创建新列表

import copy
b = copy.copy(a)  # 通用的浅拷贝函数
```

## **5. 深拷贝：递归复制内部内容**

如果希望嵌套的可变对象也独立，可以使用 `copy.deepcopy()`：

```python
import copy

a = [[1, 2], [3, 4]]
b = copy.deepcopy(a)

print(a is b)        # False
print(a[0] is b[0])  # False

b[0].append(99)

print(a)  # [[1, 2], [3, 4]]
print(b)  # [[1, 2, 99], [3, 4]]
```

字典嵌套列表也是一样：

```python
original = {
    "name": "小明",
    "scores": [80, 90],
}

shallow = copy.copy(original)
deep = copy.deepcopy(original)

original["scores"].append(100)

print(shallow["scores"])  # [80, 90, 100]
print(deep["scores"])     # [80, 90]
```

深拷贝不意味着所有对象都必须创建新实例。整数、字符串等不可变对象通常可以复用；自定义对象也可以控制自己的拷贝行为。

## **6. 三种操作放在一起比较**

对于一个包含内部列表的列表 `a`：

| 操作                   | 外层列表是否新建 | 内部列表是否共享         |
| ---------------------- | ---------------- | ------------------------ |
| `b = a`                | 否               | 是，整个对象都共享       |
| `b = copy.copy(a)`     | 是               | 是                       |
| `b = copy.deepcopy(a)` | 是               | 与原对象的内部列表不共享 |

深拷贝还有一个容易忽略的细节：**它通常会保留原对象内部的共享关系。**

```python
import copy

inner = [1, 2]
a = [inner, inner]

b = copy.deepcopy(a)

print(b[0] is inner)  # False：已经复制了内部列表
print(b[0] is b[1])   # True：副本内部仍然共享同一个列表
```

因此深拷贝后，修改 `b[0]` 仍会影响 `b[1]`，但不会影响原来的 `inner`。

## **7. 函数参数也遵循相同规则**

把列表传入函数时，不会自动复制：

```python
def add_item(items):
    items.append(3)

nums = [1, 2]
add_item(nums)

print(nums)  # [1, 2, 3]
```

调用时，参数 `items` 和变量 `nums` 引用同一个列表。

但重新绑定参数，不会让调用方变量跟着改变：

```python
def replace(items):
    items = [8, 9]

nums = [1, 2]
replace(nums)

print(nums)  # [1, 2]
```

所以理解函数传参时，关注函数里做的是**修改对象**还是**重新绑定参数**，比简单记“传值”或“传引用”更准确。

## **8. 三个常见陷阱**

**① `+=` 对不同类型可能有不同效果**

列表的 `+=` 通常原地修改：

```python
a = [1, 2]
b = a

a += [3]

print(b)  # [1, 2, 3]
```

列表的 `+` 创建新列表，再赋值：

```python
a = [1, 2]
b = a

a = a + [3]

print(a)  # [1, 2, 3]
print(b)  # [1, 2]
```

因此，涉及可变对象时，`a += b` 和 `a = a + b` 不一定具有相同的共享影响。

**② 用列表乘法创建二维列表**

```python
matrix = [[0] * 3] * 2

matrix[0][0] = 99

print(matrix)
# [[99, 0, 0], [99, 0, 0]]
```

外层的 `* 2` 重复了对同一个内部列表的引用。

要创建独立的每一行，可以使用推导式：

```python
matrix = [[0] * 3 for _ in range(2)]

matrix[0][0] = 99

print(matrix)
# [[99, 0, 0], [0, 0, 0]]
```

**③ 可变默认参数会被重复使用**

```python
def collect(value, items=[]):
    items.append(value)
    return items

print(collect(1))  # [1]
print(collect(2))  # [1, 2]
```

默认参数只在函数定义时求值一次，两个调用使用同一个列表。

如果希望每次省略参数时都创建新列表：

```python
def collect(value, items=None):
    if items is None:
        items = []

    items.append(value)
    return items

print(collect(1))  # [1]
print(collect(2))  # [2]
```

实际选择时，如果需要共享状态就直接赋值；只需要独立增删外层元素时用浅拷贝；需要独立修改嵌套数据时再考虑深拷贝。

# 模块，包，虚拟环境，依赖管理

## 1. 模块（Module）—— 一个 `.py` 文件

模块就是**任何一个 `.py` 文件**，用来把代码拆分、复用。

```python
# utils.py —— 这是一个模块
def add(x, y):
    return x + y

PI = 3.14159
```

```python
# main.py —— 导入使用
import utils            # 导入整个模块
utils.add(1, 2)

from utils import add   # 只导入某个成员
add(1, 2)

import utils as u       # 起别名
u.PI
```

**关键机制——`__name__`：**

```python
# utils.py
if __name__ == "__main__":
    print("直接运行才会执行")
```

- 直接运行 `python utils.py` → `__name__` 是 `"__main__"`，打印
- 被 `import utils` → `__name__` 是 `"utils"`，不打印

这就是为什么每个脚本都建议写这个判断：**模块可以被导入，也可以直接运行，两种行为要分开**。

Python 运行时会在 `sys.path` 列出的路径中搜索模块，优先级大致是：**当前目录 → 环境变量 `PYTHONPATH` → 安装的第三方包 → 标准库**。

## 2. 包（Package）—— 带目录结构的模块集合

包就是**包含 `__init__.py` 的文件夹**，用于组织大量模块。

```
myproject/
├── myapp/                  ← 包
│   ├── __init__.py         ← 包的"标记"（可为空）
│   ├── core.py             ← 模块 myapp.core
│   └── utils/              ← 子包 myapp.utils
│       ├── __init__.py
│       └── text.py         ← 模块 myapp.utils.text
└── main.py
```

```python
from myapp import core                  # 导入模块
from myapp.utils.text import clean      # 导入深层成员
from myapp.core import *                # 不推荐：污染命名空间
```

**`__init__.py` 的作用：**

- 标记目录为包（Python 3.3+ 有 namespace package 的宽松模式，但显式写上仍是惯例）
- 控制导入行为，可以在这里做“接口整理”：

```python
# myapp/__init__.py
from myapp.core import add   # 让外部直接 from myapp import add
```

> 相对导入：包内部用 `from . import core`（`.` 表示当前包），`from .. import x` 表示上级包。相对导入只能在被导入时用，不能直接运行包内的文件。

## 3. 虚拟环境（Virtual Environment）—— 隔离的 Python 运行空间

**为什么需要它？** 全局安装的包是所有项目共享的：

- 项目 A 要 `requests==2.25`，项目 B 要 `requests==2.31` → 冲突
- 装太多包污染系统 Python，卸载困难

**解决方案：** 给每个项目一个独立的、可随时删除重建的 Python 环境。

```bash
# Windows 下创建虚拟环境
python -m venv .venv

# 激活（PowerShell）
.venv\Scripts\Activate.ps1

# 激活（CMD）
.venv\Scripts\activate.bat

# 激活后命令行前面会出现 (.venv) 标记
# 此时 pip 安装的一切都只进这个目录，退出/删除目录即干净卸载
(.venv) pip install requests    # 装进 .venv，不碰全局

# 退出虚拟环境
deactivate
```

**原理一句话：** 激活脚本只是修改了当前会话的 `PATH`，让 `python` 和 `pip` 指向 `.venv` 目录里的副本。虚拟环境不是复制整个 Python，而是轻量的目录 + 链接（Windows 下会复制一份 python.exe）。

**现代替代方案：** 如果用 VS Code，右下角选择解释器时直接指向 `.venv` 即可，终端会自动激活。社区目前也流行 `uv`（Rust 编写，速度快几十倍）：

```bash
uv venv          # 创建
uv add requests  # 装包 + 自动管理依赖
```

## 4. 依赖管理 —— 让环境可复现

虚拟环境解决了“隔离”，但还有问题：**换一台电脑怎么重建一模一样的环境？** 这就需要把依赖清单化。

**核心工具链（pip + requirements.txt）：**

```bash
# 安装第三方包（从 PyPI 下载）
pip install requests

# 导出当前环境的所有依赖及精确版本
pip freeze > requirements.txt

# 输出形如：
# requests==2.31.0
# urllib3==2.0.7
# certifi==2023.11.17
# ...（连间接依赖也锁死了）

# 在新机器上重建
python -m venv .venv
.venv\Scripts\activate
pip install -r requirements.txt
```

**现代方案对比：**

| 工具                       | 特点                                                 |
| -------------------------- | ---------------------------------------------------- |
| `pip` + `requirements.txt` | 标准做法，简单但功能少                               |
| `pipenv`                   | 自带 Pipfile，声明式依赖                             |
| `poetry`                   | 依赖管理 + 打包发布一体，有锁文件                    |
| **`uv`**                   | 2024 年后新宠，极快，兼容 pip 生态，`uv.lock` 锁版本 |

以 `uv` 为例的完整工作流：

```bash
uv init myproject      # 初始化项目，生成 pyproject.toml
cd myproject
uv add requests        # 添加依赖（自动写入 pyproject.toml 并生成 uv.lock）
uv run main.py         # 自动使用项目环境运行
```

## 串起来：一个规范项目的样子

```
myproject/
├── .venv/                  ← 虚拟环境（永远加进 .gitignore）
├── myapp/                  ← 包
│   ├── __init__.py
│   └── core.py             ← 模块
├── main.py
├── requirements.txt        ← 依赖清单（提交到 git）
└── .gitignore
```

**四者的关系：** 模块是最小复用单元 → 包把它们组织成层次结构 → 项目代码写好后，虚拟环境保证每个项目的依赖互不干扰 → 依赖清单保证任何人在任何机器上都能 `pip install -r requirements.txt` 还原出一样的环境。

# 迭代器、生成器、装饰器

## 1. 迭代器（Iterator）—— 惰性取值的协议

先区分两个概念：

- **可迭代对象（Iterable）**：实现了 `__iter__` 方法，能被 `for` 遍历。如 list、str、dict、set
- **迭代器（Iterator）**：同时实现了 `__iter__` 和 `__next__`，是“取值的游标”，**用一次就少一个**

```python
nums = [1, 2, 3]        # list 是可迭代对象，但不是迭代器
it = iter(nums)         # iter() 拿到迭代器（调用了 nums.__iter__()）

next(it)   # 1    （调用了 it.__next__()）
next(it)   # 2
next(it)   # 3
next(it)   # StopIteration 异常！耗尽了
```

**`for` 循环的本质**就是这套协议的语法糖：

```python
# for x in nums:  等价于：
it = iter(nums)
while True:
    try:
        x = next(it)
        print(x)
    except StopIteration:
        break
```

**为什么迭代器是“一次性”的？** 因为它不保存所有数据，只有一个游标：

```python
it = iter([1, 2, 3])
print(list(it))    # [1, 2, 3]
print(list(it))    # []  ← 已经耗尽，第二次为空！
```

**手动实现一个迭代器**（体会协议的繁琐，引出生成器）：

```python
class CountDown:
    def __init__(self, n):
        self.n = n

    def __iter__(self):
        return self

    def __next__(self):
        if self.n <= 0:
            raise StopIteration
        self.n -= 1
        return self.n + 1

for x in CountDown(3):
    print(x)    # 3, 2, 1
```

## 2. 生成器（Generator）—— 一行 `yield` 替代整个类

生成器是**自动实现迭代器协议的函数**：函数体里只要出现 `yield`，这个函数就变成生成器函数，调用它不会执行代码，而是返回一个生成器对象。

```python
def countdown(n):
    while n > 0:
        yield n        # 暂停！交出值，等下次 next 再从这里继续
        n -= 1

gen = countdown(3)     # ⚠️ 不会执行函数体！只是创建生成器
next(gen)   # 3
next(gen)   # 2
next(gen)   # 1
next(gen)   # StopIteration
```

**执行流程**（理解 `yield` 的暂停/恢复）：

```
调用 countdown(3) ──→ 返回生成器，代码没跑
next(gen) ──→ 跑到 yield 3，暂停，把 3 交出去
next(gen) ──→ 从 yield 处恢复，n 变 2，跑到 yield 2，暂停
...
n <= 0 ──→ 函数结束，自动抛 StopIteration
```

上面的 `CountDown` 类 10 行代码，用生成器 4 行搞定——这就是生成器的价值：**免去手写 `__iter__/__next__` 和状态管理**。

**核心优势：惰性求值，省内存**

```python
# 内存：立即创建 1000 万个数字的列表
sum([x * x for x in range(10_000_000)])

# 内存：只保存计算逻辑，逐个产出，随时可中断
sum(x * x for x in range(10_000_000))   # 圆括号 → 生成器表达式
```

处理大文件时尤其明显：

```python
# 一次性读入整个文件（大文件会爆内存）
lines = open("huge.log").readlines()

# 逐行读取，内存占用恒定
def read_large(path):
    with open(path, encoding="utf-8") as f:
        for line in f:
            yield line.strip()

for line in read_large("huge.log"):
    process(line)
```

**进阶用法——`yield` 接收值**（协程雏形，了解即可）：

```python
def echo():
    while True:
        received = yield      # yield 不只吐值，还能收值
        print("收到:", received)

gen = echo()
next(gen)             # 预激：推进到第一个 yield
gen.send("hello")     # 收到: hello
```

## 3. 装饰器（Decorator）—— 不改源码，增强函数

**核心思想**：函数是 Python 的一等公民，可以作为参数传递。装饰器就是一个**接收函数、返回新函数**的函数。

```python
def log(func):                      # ① 接收原函数
    def wrapper(*args, **kwargs):   # ② 包装：兼容任意参数
        print(f"调用 {func.__name__}")
        result = func(*args, **kwargs)
        print(f"返回 {result}")
        return result
    return wrapper                  # ③ 返回替换后的函数

@log                                # 语法糖，等价于 add = log(add)
def add(a, b):
    return a + b

add(1, 2)
# 输出：
# 调用 add
# 返回 3
```

`@log` 只是简洁写法，展开就是：

```python
def add(a, b):
    return a + b
add = log(add)    # add 名字现在指向 wrapper
```

**一个必踩的坑——元信息丢失**：

```python
add.__name__     # 'wrapper' ← 函数身份被顶掉了！
```

解法：用 `functools.wraps` 复制原函数的元信息（写装饰器的标准模板）：

```python
from functools import wraps

def log(func):
    @wraps(func)                    # 保留 func 的名字、docstring 等
    def wrapper(*args, **kwargs):
        print(f"调用 {func.__name__}")
        return func(*args, **kwargs)
    return wrapper
```

**带参数的装饰器**——多包一层：

```python
def repeat(n):                      # 装饰器工厂：先收参数
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            for _ in range(n):
                result = func(*args, **kwargs)
            return result
        return wrapper
    return decorator

@repeat(3)                          # 等价于 say = repeat(3)(say)
def say(msg):
    print(msg)

say("hi")    # 打印 3 次 hi
```

**实用内置装饰器一览**：

| 装饰器                 | 作用                             |
| ---------------------- | -------------------------------- |
| `@staticmethod`        | 静态方法（不接收 self）          |
| `@classmethod`         | 类方法（第一个参数是 cls）       |
| `@property`            | 把方法伪装成属性访问             |
| `@functools.lru_cache` | 自动缓存函数结果（递归优化神器） |
| `@functools.cache`     | lru_cache(maxsize=None) 的简写   |

```python
from functools import lru_cache

@lru_cache(maxsize=None)
def fib(n):
    return n if n < 2 else fib(n - 1) + fib(n - 2)

fib(100)   # 瞬间出结果；不加缓存则是指数级慢
```

## 三者串联：一个综合例子

```python
from functools import wraps
import time

def timed(func):                          # 装饰器：计时
    @wraps(func)
    def wrapper(*args, **kwargs):
        start = time.perf_counter()
        result = func(*args, **kwargs)
        print(f"{func.__name__} 耗时 {time.perf_counter() - start:.4f}s")
        return result
    return wrapper

@timed
def consume(gen):                         # 接收生成器，惰性消费
    total = 0
    for x in gen:                         # for 自动走迭代器协议
        total += x
    return total

consume(x * x for x in range(1_000_000))  # 生成器表达式 + 装饰器
```

## 总结对比

| 概念   | 一句话                                | 关键字/协议             |
| ------ | ------------------------------------- | ----------------------- |
| 迭代器 | 惰性取值的游标对象                    | `__iter__` + `__next__` |
| 生成器 | 用 `yield` 写的迭代器（自动实现协议） | `yield`                 |
| 装饰器 | 接收函数返回函数，`@` 语法糖增强它    | `@decorator`            |

**记忆锚点**：`for` 循环驱动迭代器 → 生成器让迭代器好写十倍 → 装饰器让“函数增强”可以像贴标签一样复用。

# 类型标注、dataclass

## 一、类型标注（Type Hints）

### 1. 本质：只做“标注”，不做“强制”

Python 是动态类型语言，类型标注**在运行时不做任何检查**——标注写错了程序照样跑。它的价值在于：

- **IDE 智能提示和补全**（PyCharm、VS Code 的 Pylance）
- **静态检查工具**（mypy、pyright）能在运行前发现 bug
- **代码可读性**，相当于自带文档

### 2. 基础用法

```python
# 变量标注
age: int = 25
name: str = "Alice"
prices: list[float] = [9.9, 19.9]

# 函数标注：参数 + 返回值
def add(a: int, b: int) -> int:
    return a + b

# 返回 None 用 -> None（约定俗成）
def greet(name: str) -> None:
    print(f"Hello, {name}")
```

### 3. 容器与泛型（Python 3.9+ 直接用内置类型）

```python
def process(items: list[str]) -> dict[str, int]:
    return {item: len(item) for item in items}

# 元组两种写法
point: tuple[int, int] = (3, 4)        # 固定长度，每个位置类型确定
scores: tuple[int, ...] = (90, 85, 77) # 任意长度，元素同类型

# 字典：键 -> 值
config: dict[str, int] = {"timeout": 30}

# 集合
tags: set[str] = {"a", "b"}
```

> 注意：Python 3.8 及以前需要 `from typing import List, Dict`（大写开头），3.9+ 直接用 `list[str]` 这种内置写法即可。

### 4. Optional 与联合类型（3.10+ 的 `|` 语法）

```python
# 老写法
from typing import Optional, Union
def find(key: str) -> Optional[str]:   # 可能返回 str 或 None
    ...

def parse(x: Union[int, str]) -> int:  # 参数可以是 int 或 str
    ...

# 新写法（3.10+，推荐）
def find(key: str) -> str | None:      # Optional[str] 等价于 str | None
    ...

def parse(x: int | str) -> int:
    ...
```

`Optional[X]` **不是**“参数可省略”，它就是 `X | None`，这一点常被误解。

### 5. 进阶：Callable、迭代器、泛型

```python
from collections.abc import Callable, Iterator

# Callable[[参数类型列表], 返回类型] —— 函数作为参数
def apply(func: Callable[[int], int], x: int) -> int:
    return func(x)

# 生成器的标注（呼应你之前学的 generator）
def squares(n: int) -> Iterator[int]:
    for i in range(n):
        yield i * i

# 泛型：T 是占位符，"同进同出"
from typing import TypeVar
T = TypeVar("T")

def first(items: list[T]) -> T:
    return items[0]

first([1, 2, 3])   # 推断出 T = int，返回 int
```

### 6. 更高级的几个（了解即可）

| 类型                | 用途                                         |
| ------------------- | -------------------------------------------- |
| `Literal["a", "b"]` | 只允许几个字面量值，类似枚举                 |
| `Protocol`          | 结构化类型（“鸭子类型”的静态版），不要求继承 |
| `TypedDict`         | 给字典的键值定类型                           |
| `Final`             | 常量，不允许重新赋值                         |

---

## 二、dataclass（数据类）

### 1. 解决什么问题

传统写一个“只装数据”的类要写一堆样板代码：

```python
class Point:
    def __init__(self, x: int, y: int):
        self.x = x
        self.y = y
    def __repr__(self):
        return f"Point(x={self.x}, y={self.y})"
    def __eq__(self, other):
        return isinstance(other, Point) and self.x == other.x and self.y == other.y
```

`@dataclass` 装饰器**自动生成** `__init__`、`__repr__`、`__eq__` 等：

```python
from dataclasses import dataclass

@dataclass
class Point:
    x: int          # 字段必须有类型标注，这是 dataclass 的依据
    y: int

p = Point(1, 2)          # 自动生成的 __init__
print(p)                 # Point(x=1, y=2)  自动生成的 __repr__
print(p == Point(1, 2))  # True             自动生成的 __eq__（按字段比较）
```

> 这里体现了两个知识点的联动：dataclass 的字段标注是**必须的**，它是类型标注最重要的应用场景。

### 2. 默认值与 `field`

```python
from dataclasses import dataclass, field

@dataclass
class Cart:
    items: list[str] = field(default_factory=list)  # 可变默认值必须用 default_factory
    user: str = "guest"                             # 不可变默认值直接写
```

**为什么可变默认值要绕一圈？** 如果直接写 `items: list = []`，所有实例会共享同一个列表（和函数默认参数的坑同源）。`default_factory=list` 表示“每次创建实例时调用 `list()` 生成新列表”。

### 3. 常用参数

```python
@dataclass(frozen=True, order=True, slots=True)
class Config:
    host: str = "localhost"
    port: int = 8080
```

| 参数                    | 作用                                                         |
| ----------------------- | ------------------------------------------------------------ |
| `frozen=True`           | 不可变（赋值会报 `FrozenInstanceError`），且可哈希、能当字典键 |
| `order=True`            | 生成 `<`、`<=` 等比较方法，可排序                            |
| `slots=True`（3.10+）   | 用 `__slots__` 省内存、加速属性访问                          |
| `kw_only=True`（3.10+） | 强制关键字传参，避免一堆位置参数                             |

### 4. `__post_init__`：生成式初始化

`__init__` 是自动生成的，那初始化后的派生逻辑放哪？用 `__post_init__`：

```python
@dataclass
class Rect:
    width: float
    height: float
    area: float = field(init=False)  # 不参与 __init__ 参数

    def __post_init__(self):
        self.area = self.width * self.height  # 在 __init__ 之后自动执行
```

### 5. 实战模式：嵌套 + 响应你之前学的装饰器

dataclass 本质上也是一个装饰器（和你的 `@log`、`@timed` 是同类机制——接收类、返回加工后的类），所以两者可以叠加。

---

## 三、完整可运行示例

```python
from dataclasses import dataclass, field
from collections.abc import Iterator
from typing import TypeVar

T = TypeVar("T")

def first(items: list[T]) -> T:
    return items[0]

@dataclass(frozen=True, order=True)
class Student:
    name: str
    score: int = 0
    tags: list[str] = field(default_factory=list)

    def passed(self) -> bool:
        return self.score >= 60

if __name__ == "__main__":
    a = Student("Alice", 92, ["A"])
    b = Student("Bob", 58)
    print(a)                      # Student(name='Alice', score=92, tags=['A'])
    print(a == Student("Alice", 92, ["A"]))  # True
    print(b.passed())             # False
    print(sorted([a, b]))         # order=True 使按字段排序
    # a.score = 100               # frozen=True 下会报错，取消注释试试
    print(first([a, b]))          # 泛型：推断 T = Student
```

**运行方式**（Windows）：

```powershell
python c:\project\cpplearn\python\main.py
```

# 文件操作，json，日志，命令行

## 一、文件操作

### 1. `open()` 与 `with`：永远用 with

```python
# 传统写法：容易忘记 close
f = open("data.txt", "r", encoding="utf-8")
content = f.read()
f.close()

# 推荐写法：with 上下文管理器，自动关闭（即使中途抛异常）
with open("data.txt", "r", encoding="utf-8") as f:
    content = f.read()
# 离开 with 块，f 自动关闭
```

> `with` 背后就是你之前接触过的**上下文管理器协议**（`__enter__`/`__exit__`），和迭代器协议是姊妹篇。

### 2. 模式与编码

```python
"r"   # 读（默认）
"w"   # 写：覆盖原文件！文件不存在则创建
"a"   # 追加：在末尾写
"x"   # 新建写入：文件已存在则报错（防误覆盖）
"r+"  # 读写

# 加 b 就是二进制模式："rb", "wb"（图片、pickle 等）
# t 是文本模式（默认）
```

**编码大坑**：Windows 上默认编码可能是 GBK，读写 UTF-8 文件会报 `UnicodeDecodeError` 或乱码。**永远显式写 `encoding="utf-8"`**。

### 3. 读取的几种方式

```python
with open("data.txt", encoding="utf-8") as f:
    text = f.read()            # 一次全读（大文件慎用）
    # lines = f.readlines()    # 全读成列表，每项带 \n

# 文件对象本身就是迭代器！直接 for，逐行、省内存 —— 呼应你学的迭代器
with open("data.txt", encoding="utf-8") as f:
    for line in f:
        print(line.rstrip("\n"))   # 行尾自带换行，通常要 strip
```

### 4. pathlib：现代路径操作

```python
from pathlib import Path

p = Path("data") / "scores.json"   # 用 / 拼路径，跨平台
p.parent        # 上级目录
p.suffix        # 扩展名 ".json"
p.exists()      # 是否存在
p.mkdir(parents=True, exist_ok=True)   # 递归建目录，已存在不报错
p.read_text(encoding="utf-8")          # 一行读文本
p.write_text("hello", encoding="utf-8")  # 一行写文本
list(Path(".").glob("*.py"))           # 通配符找文件
```

> 新代码建议统一用 `pathlib`，它把文件、路径、目录操作都对象化了。

---

## 二、JSON

### 1. 两对函数：字符串 vs 文件

```python
import json

data = {"name": "张三", "scores": [90, 85], "passed": True}

# Python 对象 -> JSON 字符串
s = json.dumps(data, ensure_ascii=False, indent=2)

# JSON 字符串 -> Python 对象
d = json.loads(s)

# 直接写文件 / 读文件（配合刚学的文件操作）
with open("data.json", "w", encoding="utf-8") as f:
    json.dump(data, f, ensure_ascii=False, indent=2)

with open("data.json", encoding="utf-8") as f:
    d = json.load(f)
```

**记忆技巧**：带 `s`（dumps/loads）操作**字符串**，不带 `s`（dump/load）操作**文件流**。

### 2. 类型对照表

| Python                      | JSON                                |
| --------------------------- | ----------------------------------- |
| `dict`                      | `object`                            |
| `list`、`tuple`             | `array`（注意 tuple 读回来变 list） |
| `str`                       | `string`                            |
| `int` / `float`             | `number`                            |
| `True` / `False`            | `true` / `false`                    |
| `None`                      | `null`                              |
| `set`、`datetime`、自定义类 | ❌ 不支持，需自己转换                |

### 3. 两个必知参数与一个坑

```python
json.dumps(data, ensure_ascii=False, indent=2)
# ensure_ascii=False：否则中文变 "\u5f20\u4e09"
# indent=2：格式化缩进，人能看懂；不写则是压成一行的紧凑格式
# sort_keys=True：键排序，输出稳定（利于 diff）

# 坑：json.loads 解析失败抛 json.JSONDecodeError（ValueError 的子类）
# 实际项目中读外部 JSON 一定要 try/except
try:
    d = json.loads(raw)
except json.JSONDecodeError as e:
    print(f"JSON 格式错误: {e}")
```

如果需要序列化 `datetime` 之类的对象，给 `dumps` 传 `default=str` 或自定义转换函数。

---

## 三、日志（logging）

### 1. 为什么不用 print

print 的问题：没法分级、没法关、没法输出到文件、没法带时间和模块名。`logging` 全都解决。

### 2. 五个级别

```python
import logging

logging.debug("调试细节")      # 10
logging.info("常规信息")       # 20
logging.warning("警告")        # 30  ← 默认级别
logging.error("出错了")        # 40
logging.critical("系统崩溃")   # 50
```

默认级别是 WARNING，所以 debug/info 默认看不到。级别是个“闸门”：设成 INFO 就放行 INFO 及以上的。

### 3. basicConfig：一次性配置

```python
import logging

logging.basicConfig(
    level=logging.INFO,
    format="%(asctime)s [%(levelname)s] %(name)s: %(message)s",
    datefmt="%Y-%m-%d %H:%M:%S",
)
logging.info("启动完成")
# 2026-10-08 10:00:00 [INFO] root: 启动完成
```

### 4. 记录异常堆栈（最实用的一招）

```python
try:
    1 / 0
except ZeroDivisionError:
    logging.exception("计算失败")   # 自动附带完整堆栈，不用手动 traceback
```

### 5. 模块化最佳实践

```python
logger = logging.getLogger(__name__)   # 每个模块一个自己的 logger
logger.info("...")

# 同时输出到控制台和文件：
logger = logging.getLogger("app")
logger.setLevel(logging.DEBUG)
h1 = logging.StreamHandler()                          # 控制台
h2 = logging.FileHandler("app.log", encoding="utf-8") # 文件
h1.setFormatter(logging.Formatter("%(levelname)s %(message)s"))
h2.setFormatter(logging.Formatter("%(asctime)s %(name)s %(levelname)s %(message)s"))
logger.addHandler(h1)
logger.addHandler(h2)
```

> `basicConfig` 适合小脚本；多模块项目用 `getLogger(__name__)` + 在入口统一配置。

---

## 四、命令行参数

### 1. sys.argv：最原始

```python
import sys
# python tool.py input.json --verbose
print(sys.argv)   # ['tool.py', 'input.json', '--verbose'] —— 全是字符串
```

能用，但要自己解析标志位、处理类型转换，很快就会乱。

### 2. argparse：标准库正解

```python
import argparse

parser = argparse.ArgumentParser(description="JSON 处理工具")
parser.add_argument("input", help="输入文件路径")              # 位置参数（必填）
parser.add_argument("-o", "--output", default="out.json",     # 可选参数，-o 是短名
                    help="输出文件路径")
parser.add_argument("-n", "--top", type=int, default=3,       # 自动转 int
                    help="显示前 N 条")
parser.add_argument("-v", "--verbose", action="store_true",   # 开关：出现即 True
                    help="显示调试日志")

args = parser.parse_args()
print(args.input, args.output, args.top, args.verbose)
# args.verbose 是 bool；args.top 是 int
```

运行与自动帮助：

```powershell
python tool.py data.json -o result.json -n 5 -v
python tool.py -h        # 自动生成帮助文档
```

> `argparse` 还支持 `choices=["a","b"]`（枚举限制）、`nargs="+"`（多个值）等。第三方库 `click`/`typer`（基于类型标注！）更优雅，等你的类型标注用熟了可以试试 typer。

# asyncio，多线程，多进程

## 一、总览：先分清两个概念

|              | asyncio（协程）  | 多线程 threading        | 多进程 multiprocessing |
| ------------ | ---------------- | ----------------------- | ---------------------- |
| 并发模型     | 单线程协作式切换 | 多线程抢占式切换        | 多进程真并行           |
| 切换成本     | 极低（用户态）   | 较低（内核态）          | 高（进程间）           |
| 是否绕过 GIL | ✅ 单线程无需绕   | ❌ CPU 密集仍受 GIL 限制 | ✅ 每进程独立 GIL       |
| 共享内存     | 天然共享         | 天然共享（需加锁）      | 需 Queue/Pipe/共享内存 |
| 适用场景     | 高并发 IO        | IO 密集 + 已有阻塞库    | CPU 密集计算           |

**两个关键背景：**

1. **GIL（全局解释器锁）**：CPython 中同一时刻只有一个线程执行 Python 字节码，所以多线程**无法利用多核跑满 CPU**。
2. **IO 密集 vs CPU 密集**：
   - IO 密集（网络请求、读写文件、爬虫）→ 瓶颈在等待，asyncio 或多线程都行
   - CPU 密集（图像处理、排序、科学计算）→ 瓶颈在算力，只能多进程

---

## 二、asyncio：单线程协程

原理：**遇到 IO 就主动让出控制权**，事件循环（event loop）调度下一个协程。因为是"协作式"，切换由你自己的 `await` 决定，没有线程切换的开销，也不用锁。

```python
import asyncio, aiohttp  # aiohttp 是异步版 requests

async def fetch(session, url):
    async with session.get(url) as resp:
        return await resp.text()

async def main():
    async with aiohttp.ClientSession() as session:
        urls = ["https://example.com"] * 10
        tasks = [fetch(session, u) for u in urls]
        results = await asyncio.gather(*tasks)  # 并发发起 10 个请求
        print(len(results))

asyncio.run(main())
```

要点：

- `async def` 定义协程，`await` 只能出现在协程内部，含义是"这里会等，先去跑别人"
- **不能在协程里调用阻塞函数**（如 `requests.get`、`time.sleep`），否则整个线程都卡住，等于退化成串行。要用 `aiohttp`、`asyncio.sleep` 这类异步库
- 适合：Web 服务器（FastAPI、aiohttp）、爬虫、WebSocket 高并发连接

---

## 三、多线程 threading

原理：操作系统抢占式调度，多个线程真正交替执行。线程间共享进程内存，**要小心竞态条件**。

```python
import threading

counter = 0
lock = threading.Lock()

def worker():
    global counter
    for _ in range(100000):
        with lock:            # 关键操作必须加锁
            counter += 1

threads = [threading.Thread(target=worker) for _ in range(4)]
for t in threads: t.start()
for t in threads: t.join()
print(counter)  # 400000
```

要点：

- 优点：**可以直接用 `requests`、`sqlite3` 这些现成的阻塞库**，改造成本低；共享数据方便
- 缺点：① 受 GIL 限制，CPU 密集任务加速比接近 1（甚至因切换开销更慢）；② 锁用不好会死锁
- Python 3.13+ 提供了 free-threaded（no-GIL）构建，但目前还不是默认
- 适合：调用阻塞的第三方库、小规模 IO 并发、GUI 程序保持界面响应

---

## 四、多进程 multiprocessing

原理：每个进程有**独立的解释器和 GIL**，可以真正利用多核并行。

```python
from multiprocessing import Pool

def calc(n):
    return sum(i * i for i in range(n))

if __name__ == "__main__":   # Windows 必须加这行，否则递归创建进程
    with Pool(processes=4) as p:
        results = p.map(calc, [10**7] * 8)   # 4 个核分摊任务
    print(results)
```

要点：

- 数据不能直接共享，需要 `multiprocessing.Queue`、`Pipe` 或 `Manager`
- 进程创建和通信开销大，任务要**足够重**才划算（一般单个任务 > 100ms）
- Windows 上必须把入口代码放在 `if __name__ == "__main__":` 里
- 适合：图像/视频处理、大数据计算、机器学习训练前的预处理

---

## 五、怎么选？决策树

```
任务瓶颈在哪？
├─ CPU 密集（纯计算）        → 多进程 multiprocessing
└─ IO 密集（等待）
   ├─ 能改成纯异步库？       → asyncio（最高并发，万级连接）
   ├─ 依赖阻塞库 requests 等？ → 多线程（改造成本最低）
   └─ 混合型？               → 进程池跑计算 + 线程/协程跑 IO
```

## 六、一个直观的类比

- **asyncio**：一个服务员（单线程），点完这桌单不等上菜，立刻去下一桌，靠"记得哪桌快好了"来回照应 —— 效率高但不能分身
- **多线程**：多个服务员共享一个厨房，能同时服务，但厨房有个规矩（GIL）同一时刻只许一人炒菜
- **多进程**：直接开多家分店，每店独立厨房，真正同时炒菜，但传菜（进程通信）麻烦

# numpy

## 一、为什么需要 NumPy？

```python
import numpy as np

# Python list：循环逐个相加，慢，且不能直接相加
a = [1, 2, 3]
b = [4, 5, 6]
# a + b  → 结果是拼接 [1,2,3,4,5,6]，不是逐元素相加！

# NumPy array：向量化运算，一条语句搞定，底层是 C 循环
a = np.array([1, 2, 3])
b = np.array([4, 5, 6])
print(a + b)   # [5 7 9]  逐元素相加
print(a * 10)  # [10 20 30]  标量广播
```

性能差距通常是 **10~100 倍**，因为：

1. **连续内存存储**：ndarray 在内存中连续排列，CPU 缓存友好
2. **向量化（vectorization）**：运算在 C 层循环执行，无 Python 对象开销
3. **广播（broadcasting）**：不同形状的数组自动对齐运算，省掉手写循环

## 二、核心数据结构：ndarray

```python
a = np.array([1, 2, 3])            # 一维
b = np.array([[1, 2], [3, 4]])     # 二维（矩阵）
c = np.zeros((2, 3))               # 2x3 全 0 矩阵
d = np.ones((3, 3))                # 全 1
e = np.arange(0, 10, 2)            # [0 2 4 6 8] 类似 range
f = np.linspace(0, 1, 5)           # 0 到 1 等分 5 份
g = np.random.rand(2, 2)           # 2x2 随机数
```

关键属性：

```python
b.shape    # (2, 2)  形状
b.ndim     # 2       维度数
b.dtype    # int32   数据类型（重要！）
b.size     # 4       元素总数
```

**dtype 是 NumPy 的重要考点**：ndarray 要求元素类型统一（同质），不像 list 可以混装。常用类型：`int32/int64`、`float64`（默认浮点）、`bool`。类型不匹配时会自动向上转型：

```python
np.array([1, 2.5]).dtype  # float64，int 被提升为 float
```

## 三、索引与切片（和 list 的区别是重点）

```python
a = np.array([[1, 2, 3],
              [4, 5, 6],
              [7, 8, 9]])

a[0, 1]        # 2   逗号分隔行列
a[:2, 1:]      # 二维切片，取前两行的后两列
a[a > 5]       # 布尔索引：[6 7 8 9]，返回一维数组！
a[:, 0]        # 第一列 [1 4 7]，注意与 list 切片不同
```

⚠️ **两个易错点**：

```python
x = a[0:2]     # 切片 → 是视图（view），改了会影响原数组
y = a[a > 5]   # 布尔/花式索引 → 是拷贝，改了不影响原数组

x[0, 0] = 99   # 原数组 a 也被改了！
# 想要独立副本用 a.copy()
```

这和 Python list 的切片行为（永远是浅拷贝）**完全不同**，是面试常问点。

## 四、广播（broadcasting）

形状不同的数组运算时，NumPy 自动扩展小数组：

```python
a = np.array([[1], [2], [3]])   # 形状 (3, 1)
b = np.array([10, 20, 30])      # 形状 (3,)
a + b                            # 结果 (3, 3)：
# [[11 21 31]
#  [12 22 32]
#  [13 23 33]]
```

规则（从尾部维度对齐）：维度相等，或其中一方为 1，即可扩展。理解广播能让你**少写很多 for 循环**——而少写循环正是 NumPy 提速的秘诀。

## 五、常用操作速查

```python
a = np.arange(1, 13).reshape(3, 4)   # reshape 改形状，元素总数必须匹配

a.sum()        # 全部求和      a.sum(axis=0)  # 按列求和（压缩行）
a.mean()       # 平均值        a.max(axis=1)  # 每行最大值
a.min(); a.std(); a.argmax()  # 最小值/标准差/最大值的下标
a.sort(axis=1)              # 每行排序
np.dot(a, b)                # 矩阵乘法
a.T                          # 转置
np.concatenate([a, b])      # 拼接
np.vstack([a, b]) / np.hstack([a, b])  # 纵向/横向堆叠
```

**聚合类函数都有 axis 参数**，记住一句话：`axis=0` 是"沿行的方向压缩（跨行运算）"，`axis=1` 是沿列的方向。

## 六、ufunc（通用函数）

所有对单个元素的数学运算都有向量化版本：

```python
np.sqrt(a); np.exp(a); np.log(a)
np.sin(a); np.abs(a)
np.clip(a, 0, 5)   # 把超出 [0,5] 的值截断，预处理常用
```

## 七、线性代数与文件

```python
np.linalg.inv(M)      # 逆矩阵
np.linalg.det(M)      # 行列式
np.linalg.eig(M)      # 特征值/特征向量

np.save('arr.npy', a)       # 二进制保存（快）
a = np.load('arr.npy')
np.savetxt('a.csv', a, delimiter=',')   # CSV
```