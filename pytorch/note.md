# Tensor、shape、dtype、device

这四个概念是 PyTorch 的基石，可以理解为：**Tensor 是容器，shape/dtype/device 是它的三个"身份属性"**。

## 1. Tensor（张量）

张量就是**多维数组**，是 PyTorch 中所有数据的载体：

| 阶数 (dim) | 名称          | 例子             |
| ---------- | ------------- | ---------------- |
| 0          | 标量 (scalar) | 一个数 `3.14`    |
| 1          | 向量 (vector) | `[1, 2, 3]`      |
| 2          | 矩阵 (matrix) | 二维表格         |
| n          | n 维张量      | 图像批次、视频等 |

```python
import torch

a = torch.tensor(3.14)            # 0 维
b = torch.tensor([1, 2, 3])       # 1 维
c = torch.tensor([[1, 2], [3, 4]]) # 2 维
```

## 2. shape（形状）

shape 描述张量**每个维度的长度**，即"数据的骨架"：

```python
x = torch.zeros(2, 3, 4)
print(x.shape)   # torch.Size([2, 3, 4])
print(x.ndim)    # 3
```

深度学习中最常见的 shape 语义：

```
[batch_size, channels, height, width]   # 图像 (NCHW)
[batch_size, seq_len, embed_dim]        # 文本 (Transformer 输入)
```

**维度对齐是调 bug 时最常做的事**，比如矩阵乘法 `@` 要求内维匹配：`(2,3) @ (3,4) → (2,4)`。

## 3. dtype（数据类型）

dtype 决定**每个元素用什么类型存储**：

| dtype                        | 说明                         |
| ---------------------------- | ---------------------------- |
| `torch.float32`              | 默认浮点型，训练最常用       |
| `torch.float16` / `bfloat16` | 半精度，省显存、加速         |
| `torch.int64`                | 整型（索引、标签的默认类型） |
| `torch.bool`                 | 布尔（掩码 mask）            |

```python
x = torch.tensor([1.0, 2.0])
print(x.dtype)              # torch.float32
y = x.to(torch.float16)     # 转换精度
labels = torch.tensor([0, 1])  # 默认 int64
```

注意：**混合 dtype 运算会报错**，如 `float32 + int64` 需要显式转换。

## 4. device（设备）

device 决定**数据存放在哪个硬件上**：

```python
print(torch.cuda.is_available())   # 是否有 GPU

x = torch.randn(2, 2)                 # CPU
x = x.to("cuda")                      # 移到 GPU
x = x.to("cuda:0")                    # 指定第 0 块 GPU
x = x.cpu()                           # 移回 CPU
```

核心规则：**模型和数据必须在同一设备上**，否则直接报错：

```python
model = MyModel().to("cuda")
inputs = inputs.to("cuda")
output = model(inputs)   # ✅ 都在 GPU
```

## 综合示例

```python
x = torch.randn(4, 3, device="cuda", dtype=torch.float32)

print(x.shape)   # torch.Size([4, 3])  —— 4 行 3 列
print(x.dtype)    # torch.float32       —— 单精度浮点
print(x.device)   # cuda:0              —— 存在第 0 块 GPU
```

# stride、连续性、view、reshape、transpose

> **一个 Tensor = 一块扁平的内存（storage） + shape（形状） + stride（步长）**。
> `transpose`/`view` 只改"形状和步长"（不搬数据），`reshape`/`contiguous` 可能会真的复制数据。

---

## 1. stride（步长）：张量的"内存导航图"

stride 回答一个问题：**沿着第 d 维走一步，在底层一维内存里要跳过多少个元素？**

```python
import torch

t = torch.arange(1, 7).reshape(2, 3)
# [[1, 2, 3],
#  [4, 5, 6]]
print(t.shape)    # torch.Size([2, 3])
print(t.stride()) # (3, 1)
print(t.storage())# [1, 2, 3, 4, 5, 6]  底层就是这一条扁平内存
```

- 沿第 0 维（换行）走一步：跳 3 个元素 → stride[0] = 3
- 沿第 1 维（换列）走一步：跳 1 个元素 → stride[1] = 1

寻址公式：`元素[i, j] = storage[i * stride[0] + j * stride[1]]`，比如 `t[1, 2] = storage[1*3 + 2*1] = storage[5] = 6`。

三维同理：`(2, 3, 4)` 的张量 stride 是 `(12, 4, 1)`。

---

## 2. 连续性（contiguity）：stride 是否"标准排列"

如果 stride 恰好满足 **`stride[i] = stride[i+1] * shape[i+1]`**（即从外到内紧密递减，行优先排列），这个张量就是**连续（contiguous）**的。

```python
print(t.is_contiguous())  # True
```

注意：**连续性不是内存的性质，而是 (shape, stride) 这一对组合的性质**。同一块内存，换个 stride 就可能"不连续"。

---

## 3. transpose：只改 stride，不搬数据

```python
tt = t.transpose(0, 1)      # 或 t.t()（仅限 2D）
print(tt.shape)             # torch.Size([3, 2])
print(tt.stride())          # (1, 3)  ← 两个维度互换步长
print(tt)                   # [[1, 4],
                            #  [2, 5],
                            #  [3, 6]]
print(tt.storage())         # [1, 2, 3, 4, 5, 6]  ← 内存原封不动！
print(tt.is_contiguous())   # False
```

transpose 本质只是**交换了 stride 的分量**，底层内存一个字节都没动，所以它是**视图（view）操作**：

```python
tt[0, 0] = 100
print(t[0, 0])   # tensor(100)  ← 改 tt 会影响 t，因为它们共享内存
```

`permute(2, 0, 1)` 是同族操作（多维度任意重排），stride 也跟着重排。

---

## 4. view vs reshape：一个严格、一个兜底

|              | `view`                | `reshape`                        |
| ------------ | --------------------- | -------------------------------- |
| 语义         | 换 shape 看同一块内存 | "能看就看，不能看就复制一份再看" |
| 是否可能复制 | **绝不复制**          | 必要时复制                       |
| 对非连续张量 | 常报错                | 永远成功                         |
| 速度         | 快（O(1)）            | 可能 O(n) 拷贝                   |

```python
tt.view(-1)     # RuntimeError: view size is not compatible with
                # input tensor's size and stride ...

tt.reshape(-1)  # 成功：tensor([  1,   4,   2,   5,   3,   6])
                # 注意顺序变了，因为它是先复制成连续内存再展平
```

为什么 `view` 失败？因为 tt 的逻辑顺序（1,4,2,5,3,6）在内存里是跳着走的，**无法用"单一 stride"表达成一维张量**，只能靠复制来"重排"。

经验法则：

- 你想**确保零拷贝**（性能敏感、想共享内存）→ 用 `view`
- 你只想**拿到正确形状**、不在乎是否拷贝 → 用 `reshape`（更安全）

---

## 5. contiguous()：把"跳着走"变成"紧挨着"

```python
c = tt.contiguous()          # 不连续 → 复制出一份行优先排列的新内存
print(c.stride())            # (2, 1)
c.view(-1)                   # 现在可以了
```

如果张量本来就连续，`contiguous()` 直接返回自身（零开销）。

# nn.Module、Parameter、buffer

> 一句话总纲：**`nn.Module` 是一棵会自动注册成员的树；`Parameter` 是"会被优化器更新的成员"；`buffer` 是"不被更新但算模块状态、要跟着搬迁和保存的成员"。**

---

## 1. nn.Module：不只是基类，而是一张"注册表"

你继承它、实现 `forward`，但真正的魔法在**赋值那一刻**。`nn.Module` 重写了 `__setattr__`：

```python
class MyLayer(nn.Module):
    def __init__(self):
        super().__init__()
        self.weight = nn.Parameter(torch.randn(2, 2))  # → 注册进 _parameters
        self.relu = nn.ReLU()                          # → 注册进 _modules
        self.register_buffer('scale', torch.tensor(2.0))  # → 注册进 _buffers
        self.plain = torch.tensor(3.0)                 # → 只是个普通属性，没人管
```

所以 `model.parameters()`、`.to(device)`、`state_dict()` 这些统一接口，靠的都是"赋值时自动登记"。

几个必知行为：

```python
out = model(x)     # ✅ 走 __call__ → 触发 hooks → 再调 forward
out = model.forward(x)  # ⚠️ 能跑，但跳过所有 hooks，一般别这么干

model.train() / model.eval()  # 设置 training 标志并递归传给所有子模块
                              # 影响 Dropout、BatchNorm 的行为
```

| 常用 API                              | 作用                                           |
| ------------------------------------- | ---------------------------------------------- |
| `parameters()` / `named_parameters()` | 递归列出所有 Parameter（名字形如 `fc.weight`） |
| `children()` / `modules()`            | 遍历直接子模块 / 所有模块                      |
| `state_dict()` / `load_state_dict()`  | 序列化参数 + 持久 buffer                       |
| `to(device/dtype)`                    | 原地搬迁所有参数和 buffer                      |
| `zero_grad()`                         | 清空所有参数梯度                               |

---

## 2. Parameter：会被训练的成员

`nn.Parameter` 是 `Tensor` 的**子类**，默认 `requires_grad=True`，但关键不在"要梯度"，而在"被注册"：

```python
w1 = nn.Parameter(torch.randn(2, 2))              # 注册型
w2 = torch.randn(2, 2, requires_grad=True)        # 有梯度，但不是 Parameter

class M(nn.Module):
    def __init__(self):
        super().__init__()
        self.a = w1   # ✅ 在 model.parameters() 里，优化器能更新它
        self.b = w2   # ❌ 不在 parameters() 里，优化器根本看不到它
```

**优化器的视角**：`optim.SGD(model.parameters(), lr=0.1)` 在创建时**抓走了一批 Parameter 对象的引用**，之后每步更新的是这些对象的 `.data`。推论：

- 优化器创建**之后**才注册的 Parameter，不会被更新；
- 所以标准流程是：定义完模型 → `model.to(device)` → 再创建优化器。

动态集合用 `nn.ParameterList` / `nn.ParameterDict`（用普通 list 装 Parameter 不会注册）。

---

## 3. Buffer：不训练，但算"模块状态"

典型场景：BatchNorm 的 `running_mean`/`running_var`、位置编码表、因果 mask。它们不是参数（不需要梯度、优化器不碰），但**必须跟着模型走**：

```python
class Block(nn.Module):
    def __init__(self):
        super().__init__()
        self.weight = nn.Parameter(torch.ones(2, 2))
        self.register_buffer('mask', torch.tril(torch.ones(3, 3)))  # 下三角 mask
        self.register_buffer('tmp', torch.zeros(1), persistent=False)  # 不进 state_dict
```

- `.to('cuda')` → mask 跟着搬，**普通 Tensor 属性不搬**
- `state_dict()` → mask 会被保存（`persistent=False` 则只搬不存，适合缓存类数据）
- `parameters()` → 不含 mask，优化器不会更新它

---

## 4. 三者对比（背下来）

|                       | `Parameter` | Buffer（persistent） | 普通属性 Tensor |
| --------------------- | ----------- | -------------------- | --------------- |
| 出现在 `parameters()` | ✅           | ❌                    | ❌               |
| 优化器更新            | ✅           | ❌                    | ❌               |
| `requires_grad`       | 默认 True   | False                | 默认 False      |
| `.to(device)` 搬迁    | ✅           | ✅                    | ❌               |
| 进入 `state_dict()`   | ✅           | ✅                    | ❌               |

完整验证：

```python
import torch
import torch.nn as nn

class Block(nn.Module):
    def __init__(self):
        super().__init__()
        self.weight = nn.Parameter(torch.ones(2, 2))
        self.register_buffer('scale', torch.tensor(2.0))
        self.plain = torch.tensor(3.0)

    def forward(self, x):
        return (x @ self.weight) * self.scale

b = Block()
print([n for n, _ in b.named_parameters()])  # ['weight']
print([n for n, _ in b.named_buffers()])     # ['scale']
print(list(b.state_dict().keys()))           # ['weight', 'scale']  没有 plain
print(len(list(b.parameters())))             # 1
```

---

## 5. 常见坑

```python
# 坑 1：忘记 super().__init__()
# 赋值 Parameter 时会直接报错（_parameters 还不存在）

# 坑 2：用普通 list 装子模块
self.layers = [nn.Linear(3, 3) for _ in range(3)]  # ❌ 不注册，参数丢失
self.layers = nn.ModuleList([...])                 # ✅

# 坑 3：位置编码用普通 Tensor 属性
self.pos_emb = torch.randn(100, 512)   # ❌ .cuda() 后还在 CPU → device mismatch
self.register_buffer('pos_emb', torch.randn(100, 512))  # ✅

# 坑 4：优化器创建太早
optimizer = optim.SGD(model.parameters(), lr=0.1)
model.head = nn.Linear(10, 10)   # 后注册的 head.weight 永远不会被更新
```

---

## 6. 用 C++ 的思维理解

| PyTorch                               | C++ 类比                                                     |
| ------------------------------------- | ------------------------------------------------------------ |
| `nn.Module` 的 `__setattr__` 自动注册 | 带"父指针"的成员对象（类似 Qt `QObject` 的父子树），赋值即挂到对象树上 |
| `parameters()` 递归遍历               | 对对象树做深度优先遍历，收集特定类型成员                     |
| `Parameter` 被优化器持有引用          | 训练管理器里存了一批 `T*` 指针，每步 `*p += delta`           |
| `state_dict()`                        | `save()/load()` 序列化协议：遍历所有"需要持久化"的成员       |
| `buffer`                              | 需要随对象一起序列化/搬迁的 `const` 缓存数据（如查表、mask） |
| `train()/eval()`                      | 沿树传播的模式标志位（影响子模块行为，类似策略开关）         |

**记忆锚点**：判断一个张量该怎么放，问自己两个问题——

1. 它需要被训练吗？→ 需要就 `nn.Parameter`
2. 它需要跟着 `.to(device)` 走 / 进 `state_dict` 吗？→ 需要就 `register_buffer`

两个都否 → 普通属性随便放。

---

需要的话，我可以把这份整理追加进 [note.md](file:///c:/project/cpplearn/pytorch/note.md)，或者把上面的验证代码写进 [demo.py](file:///c:/project/cpplearn/pytorch/demo.py) 方便你直接跑（比如给 Block 加个 `.to('cuda')` 前后对比 `plain` 和 `scale` 的 device）。