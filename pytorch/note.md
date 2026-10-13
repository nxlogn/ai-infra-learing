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

# 常见网络层和算子

## 一、先分清两个概念

| 概念                | 英文              | 本质                             | 是否带参数 | 典型 API                 |
| ------------------- | ----------------- | -------------------------------- | ---------- | ------------------------ |
| **层 (Layer)**      | `nn.Module`       | 有状态、可持有权重、可组合成模型 | ✅ 通常有   | `nn.Linear`、`nn.Conv2d` |
| **算子 (Operator)** | `torch.*` / `F.*` | 无状态的纯函数，输入→输出        | ❌ 无       | `torch.matmul`、`F.relu` |

一句话：**层 = 算子 + 可学习参数 + 状态管理（如 state_dict）**

## 二、常用网络层（nn.*）

### 1. 全连接层 `nn.Linear`

```python
fc = nn.Linear(in_features=128, out_features=64, bias=True)
y = fc(x)   # x: (B, 128) -> y: (B, 64)
```

本质就是 `y = x @ W.T + b`，权重形状 `W: (out, in)`。**Transformer、MLP 的最后一层几乎都是它。**

### 2. 卷积层 `nn.Conv2d` / `Conv1d`

```python
conv = nn.Conv2d(in_channels=3, out_channels=16, kernel_size=3, padding=1, stride=1)
y = conv(x)   # x: (B, 3, H, W) -> y: (B, 16, H, W)
```

- 局部连接 + 权重共享，专治图像的空间结构。
- 关键超参：`kernel_size`（感受野）、`stride`（下采样）、`padding`（保尺寸）、`groups`（分组卷积，`groups=in=out` 即深度可分离）。

### 3. 池化层 `nn.MaxPool2d` / `AvgPool2d`

```python
pool = nn.MaxPool2d(kernel_size=2, stride=2)
y = pool(x)   # (B, C, H, W) -> (B, C, H/2, W/2)
```

无参数，只做降采样。现代网络里常被 `stride=2` 的卷积或 `AdaptiveAvgPool2d(1)`（全局池化）替代。

### 4. 归一化层 `nn.BatchNorm2d` / `LayerNorm`

```python
bn  = nn.BatchNorm2d(16)          # CNN 常用，对 (B,H,W) 归一化，含 running 统计
ln  = nn.LayerNorm(128)           # Transformer 常用，对最后一维归一化
```

**注意**：BN 有 `running_mean/running_var` 这种"不参与梯度但进 state_dict"的量——本质就是 buffer（跟你 demo 里的 `scale` 同类）。`train()` 和 `eval()` 下行为不同，这是新手最常见的坑。

### 5. Dropout `nn.Dropout`

```python
dp = nn.Dropout(p=0.5)
```

训练时随机置零、缩放，`eval()` 时变成恒等。**防过拟合**，仅训练期生效。

### 6. 激活函数层 `nn.ReLU` / `GELU` / `Sigmoid`

```python
act = nn.GELU()   # Transformer 默认
act = nn.ReLU()   # CNN 默认
```

它们本身是无参层，等价于对应的 `F.*` 算子；包成层只是为了塞进 `nn.Sequential`。

### 7. 嵌入层 `nn.Embedding`

```python
emb = nn.Embedding(num_embeddings=10000, embedding_dim=128)
y = emb(idx)   # idx: (B, L) 的 int64 -> y: (B, L, 128)
```

本质是一张可学习的查找表（`(vocab, dim)` 的矩阵），NLP 输入的第一站。

### 8. 序列/注意力层 `nn.LSTM` / `nn.MultiheadAttention`

```python
mha = nn.MultiheadAttention(embed_dim=128, num_heads=8, batch_first=True)
out, attn = mha(q, k, v)   # batch_first=True 时形状为 (B, L, D)
```

`nn.TransformerEncoderLayer` 就是 `MultiheadAttention + LayerNorm + FFN + Dropout` 的封装。

### 9. 容器 `nn.Sequential` / `ModuleList` / `ModuleDict`

```python
net = nn.Sequential(nn.Linear(128, 64), nn.ReLU(), nn.Linear(64, 10))

layers = nn.ModuleList([nn.Linear(64, 64) for _ in range(4)])   # 会被注册进参数
plain_list = [nn.Linear(64, 64) for _ in range(4)]              # ❌ 不会注册，参数丢失
```

**这是极高频的坑**：用普通 Python `list` 存子层，`parameters()` 会漏掉它们。

## 三、常用算子（torch.* / F.*）

### 1. 线性代数类

| 算子                     | 说明                   | 形状                      |
| ------------------------ | ---------------------- | ------------------------- |
| `a @ b` / `torch.matmul` | 矩阵乘（支持广播批维） | `(B,m,k)@(B,k,n)→(B,m,n)` |
| `torch.einsum`           | 爱因斯坦求和，万能表达 | `"bij,bjk->bik"`          |
| `torch.bmm`              | 批量矩阵乘             | `(B,m,k)@(B,k,n)`         |

### 2. 逐元素类（element-wise）

```python
a + b, a * b, torch.exp(a), torch.clamp(a, 0, 1)
```

要求形状可**广播**（broadcasting），这是"隐式扩维"机制，比如 `(B,1,D) + (B,L,D)`。

### 3. 归约类（reduction）

| 算子                           | 说明                              |
| ------------------------------ | --------------------------------- |
| `x.sum(dim=1)`                 | 沿某维求和                        |
| `x.mean(dim=-1, keepdim=True)` | 求均值并保留维度                  |
| `x.max(dim=1)`                 | 返回 `(values, indices)` 两个结果 |
| `torch.softmax(x, dim=-1)`     | 归一化成概率                      |

`dim` 参数是核心——选错维度是最常见 bug。

### 4. 形状变换类

```python
x.view(B, -1)          # 要求内存连续，否则报错
x.reshape(B, -1)       # 不连续时自动复制
x.permute(0, 2, 1)     # 换维，改 stride 不搬数据
x.unsqueeze(1)         # 插入维度
x.squeeze()            # 去掉长度为 1 的维
x.flatten(1)           # 从第 1 维起拉平
```

### 5. 拼接/堆叠/索引

```python
torch.cat([a, b], dim=1)    # 沿已有维拼接
torch.stack([a, b], dim=0)  # 新建一维堆叠
x[mask]                     # 布尔掩码索引
torch.gather(x, 1, idx)     # 按索引取值
```

## 四、层 vs 算子的选择原则

```python
# 有参数、要进 state_dict → 用层
self.proj = nn.Linear(128, 128)

# 无参数、临时计算 → 用算子
y = torch.relu(self.proj(x) + residual)
```

**判据**：需要被优化器更新/需要保存权重 → 层；只是纯计算 → 算子

# 训练与推理模式

## 一、autograd（自动微分）

### 1. 核心思想：动态计算图

每次对 Tensor 做运算，PyTorch 会**边算边记录**一张图（动态图，define-by-run）：

```python
import torch

x = torch.tensor([2.0], requires_grad=True)
y = x ** 2 + 3 * x          # 前向：同时建图
y.backward()                # 反向：沿图回传
print(x.grad)               # dy/dx = 2x + 3 = 7
```

- **前向传播**：算出结果，同时记住"这个结果是怎么来的"。
- **反向传播**：从 loss 出发，用链式法则自动求导。

### 2. 关键概念对照表

| 概念                | 含义                                 | 关键 API                 |
| ------------------- | ------------------------------------ | ------------------------ |
| `requires_grad`     | 是否追踪该张量的梯度                 | `x.requires_grad_(True)` |
| **叶子张量 (leaf)** | 用户直接创建的张量，梯度存于 `.grad` | `x.is_leaf`              |
| **非叶子张量**      | 运算产生的中间结果，默认不保存 grad  | `y.is_leaf → False`      |
| `.grad`             | 累积的梯度（**注意是累加不是覆盖**） | `x.grad`                 |
| `grad_fn`           | 指向生成该张量的反向函数             | `y.grad_fn`              |
| 计算图              | 前向记录下来的求导关系网             | —                        |

```python
x = torch.tensor([2.0], requires_grad=True)   # 叶子
y = x * 3                                      # 非叶子
z = y.sum()
print(y.grad_fn)      # <MulBackward0>
print(y.is_leaf)      # False
z.backward()
print(x.grad)         # tensor([3.])   ← 只有叶子有 .grad
```

### 3. 三个必踩的坑

**坑 1：梯度会累积，必须手动清零**

```python
for step in range(3):
    loss = model(x).sum()
    loss.backward()
    # ❌ 忘了清零，梯度会叠加
    optimizer.zero_grad()   # ✅ 标准位置：backward 之后、step 之前
    optimizer.step()
```

`x.grad` 是**累加**的（为了支持梯度累积技巧），所以每个 iteration 前要 `zero_grad()`。更规范的顺序是：

```python
optimizer.zero_grad()   # 1. 清零
loss.backward()         # 2. 反向
optimizer.step()        # 3. 更新参数
```

**坑 2：推理时不需要建图**

```python
with torch.no_grad():        # 关掉建图，省显存、加速
    y = model(x)
```

**坑 3：切断梯度用 `detach()`**

```python
a = torch.tensor([1.0], requires_grad=True)
b = a.detach()      # b 与 a 共享数据，但脱离计算图
c = a * 2           # c 会回传到 a
```

`detach()` 常用于：固定 target、对抗训练、只需数值不需梯度。

### 4. `no_grad` vs `inference_mode`

| 方式                     | 效果                           | 场景           |
| ------------------------ | ------------------------------ | -------------- |
| `torch.no_grad()`        | 不建图，结果仍是普通张量       | 验证、通用场景 |
| `torch.inference_mode()` | 更彻底，禁用版本计数，**更快** | 纯推理、部署   |
| `torch.enable_grad()`    | 在 no_grad 内临时重开          | 嵌套控制       |

`inference_mode` 里的张量**不能再参与需要梯度的计算**，所以只用于纯前向。日常 `no_grad` 更安全。

## 二、训练模式 vs 推理模式

### 1. 为什么需要两种模式？

有些层在两种模式下**行为不同**：

| 层          | `train()` 模式                        | `eval()` 模式             |
| ----------- | ------------------------------------- | ------------------------- |
| `Dropout`   | 随机置零 + 缩放                       | 恒等（不动）              |
| `BatchNorm` | 用当前 batch 统计，更新 running stats | 用固定的 running_mean/var |
| `LayerNorm` | 无差别                                | 无差别                    |

**这是新手最高频的 bug**：训练完忘了 `eval()`，验证集指标飘忽不定。

### 2. 两个开关，别搞混

```python
model.train()   # 切"训练模式"：Dropout/BN 开启训练行为（默认就是 train）
model.eval()    # 切"推理模式"：Dropout/BN 切到推理行为

# 另一个是"是否建图"，与上面独立：
with torch.no_grad():
    ...
```

**关键区分**：

- `model.train()` / `model.eval()` → 控制**层的行为**（Dropout、BN）。
- `torch.no_grad()` → 控制**是否记录计算图**。

推理时**两个都要做**：

```python
model.eval()
with torch.no_grad():
    out = model(x)
```

它们**互相独立**：`eval()` 不会自动关建图，`no_grad()` 也不会自动切换 Dropout 行为。这正是很多人困惑的点。

### 3. `eval()` 的递归性

`model.eval()` 会**递归**把子模块都设为 eval（因为它是 `nn.Module` 的方法），手写的自定义层若行为依赖模式，可以覆写：

```python
def train(self, mode: bool = True):
    super().train(mode)
    # 自定义逻辑
    return self
```

## 三、标准训练循环（融合上面所有点）

```python
model.train()
for epoch in range(epochs):
    for x, y in train_loader:
        x, y = x.to(device), y.to(device)

        optimizer.zero_grad()      # 1. 清梯度
        out = model(x)             # 2. 前向（建图）
        loss = criterion(out, y)   # 3. 算损失
        loss.backward()            # 4. 反向（求梯度）
        optimizer.step()           # 5. 更新参数

    model.eval()                   # 切推理模式
    with torch.no_grad():          # 关建图
        for x, y in val_loader:
            out = model(x)
            # 计算验证指标
    model.train()                  # 切回训练模式
```

记忆口诀：

> **训练 = `train()` + 建图；推理 = `eval()` + `no_grad()`。**
> 每步 `zero_grad → forward → backward → step`。

# state_dict、模型保存与权重加载

## 一、state_dict 到底是什么

`state_dict` 是一个 **`OrderedDict`**，保存了模型**所有需要持久化的张量**，即：

```
state_dict = parameters（可学习权重） + buffers（不可学习但需保存的状态）
```

回到你 demo.py 的那个 `Block`：

```python
class Block(nn.Module):
    def __init__(self):
        super().__init__()
        self.weight = nn.Parameter(torch.ones(2,2))   # → 参数
        self.register_buffer('scale', torch.tensor(2.0))  # → buffer
        self.plain = torch.tensor(3.0)                # → 普通属性，都不进

b = Block()
print([n for n, _ in b.named_parameters()])   # ['weight']
print([n for n, _ in b.named_buffers()])      # ['scale']
print(list(b.state_dict().keys()))            # ['weight', 'scale']  ← 两者之和
print(len(list(b.parameters())))              # 1
```

| 属性                  | 是否进 `parameters()` | 是否进 `state_dict()` | 是否更新梯度 |
| --------------------- | --------------------- | --------------------- | ------------ |
| `nn.Parameter`        | ✅                     | ✅                     | ✅            |
| `register_buffer`     | ❌                     | ✅                     | ❌            |
| 普通属性 `self.plain` | ❌                     | ❌                     | ❌            |

**一句话**：`state_dict` = 参数 ∪ buffer。BN 的 `running_mean/running_var` 就是靠 buffer 机制被保存下来的，这也解释了为什么它"不训练却要存"。

## 二、模型保存的三种方式

### 方式 1：只存 state_dict（**推荐**）

```python
torch.save(model.state_dict(), "model.pth")
```

- 存的是**纯张量字典**，与模型代码解耦。
- 加载时需要先 `new_model = MyModel()`，再 `load_state_dict`。
- ✅ 官方推荐，稳定、可跨版本、体积小。

### 方式 2：存整个模型（不推荐）

```python
torch.save(model, "model_full.pth")     # 底层用 pickle 序列化整个对象
model = torch.load("model_full.pth")
```

- ❌ 强依赖类的定义路径（重构/改名就加载失败）、有安全风险、体积大。
- 只适合临时调试。

### 方式 3：存 checkpoint（训练中断恢复）

```python
torch.save({
    "epoch": epoch,
    "model_state": model.state_dict(),
    "optimizer_state": optimizer.state_dict(),
    "scheduler_state": scheduler.state_dict(),
    "loss": loss.item(),
}, "ckpt.pth")
```

- 存**训练的全部状态**，用于断点续训。
- **优化器状态也要存**（如 Adam 的 `exp_avg`），否则续训会掉点。

| 方式         | 内容                 | 用途               |
| ------------ | -------------------- | ------------------ |
| `state_dict` | 权重 + buffer        | 发布、推理、迁移   |
| 整个模型     | pickle 对象          | 临时调试（不推荐） |
| checkpoint   | 权重 + 优化器 + 进度 | 断点续训           |

## 三、权重加载 load_state_dict

### 1. 标准流程

```python
model = MyModel()
state = torch.load("model.pth", map_location="cpu")
model.load_state_dict(state)
model.eval()
```

注意 `load_state_dict` 是**原地修改**（in-place），直接改 `model` 自己的参数，不返回新对象。

### 2. strict 参数与两类报错

```python
model.load_state_dict(state, strict=True)   # 默认：键必须完全一致
```

| 报错              | 含义                   | 常见原因            |
| ----------------- | ---------------------- | ------------------- |
| `missing_keys`    | 模型有、权重文件里没有 | 权重是旧版/少存了层 |
| `unexpected_keys` | 权重文件有、模型里没有 | 多了层、改了结构    |

**部分加载**（迁移学习核心）：

```python
info = model.load_state_dict(state, strict=False)
print(info.missing_keys)      # 未被赋值的层（会保持随机初始化）
print(info.unexpected_keys)   # 被忽略的多余权重
```

`strict=False` 是迁移学习/加载预训练权重时的标准操作。

### 3. 只加载部分层（冻结 backbone）

```python
pretrained = torch.load("resnet.pth")
model_dict = model.state_dict()
# 只保留名字和形状都匹配的
matched = {k: v for k, v in pretrained.items()
           if k in model_dict and v.shape == model_dict[k].shape}
model_dict.update(matched)
model.load_state_dict(model_dict)。

# 冻结已加载的层
for name, param in model.named_parameters():
    if name in matched:
        param.requires_grad = False
```

## 四、设备与 dtype 问题

```python
# 在 GPU 上存的权重，想在 CPU 加载 → 必须 map_location
state = torch.load("model.pth", map_location="cpu")
state = torch.load("model.pth", map_location="cuda:0")
state = torch.load("model.pth", map_location={"cuda:0": "cpu"})  # 精细映射
```

**关键**：保存时 `model.state_dict()` 里的张量带着原设备信息。跨设备加载**务必用 `map_location`**，否则会因找不到原 GPU 而报错。加载后再统一 `.to(device)`：

```python
model = MyModel().to(device)
model.load_state_dict(torch.load("model.pth", map_location=device))
```

## 五、保存/加载的最佳实践清单

```python
# ---- 保存 ----
model.eval()                                   # 建议先切 eval，保证 buffer 是推理态
torch.save(model.state_dict(), "best.pth")     # 只存权重

# ---- 加载 ----
model = MyModel()                              # 1. 先构造同结构模型
state = torch.load("best.pth", map_location="cpu")  # 2. 加载 + 设备映射
model.load_state_dict(state, strict=True)      # 3. 严格校验
model.to(device)                               # 4. 移到目标设备
model.eval()                                   # 5. 切推理模式
```

**易错点速查**：

| 坑                                | 正确做法                                |
| --------------------------------- | --------------------------------------- |
| 用 `torch.save(model)` 存整个模型 | 改成 `torch.save(model.state_dict())`   |
| 加载后忘了 `eval()`               | 推理前必须 `model.eval()`               |
| 跨设备加载报错                    | 加 `map_location`                       |
| 断点续训只存了权重                | checkpoint 要连优化器一起存             |
| 改了结构后 `strict=True` 报错     | 用 `strict=False` 看 missing/unexpected |

记忆口诀：

> **存：`torch.save(model.state_dict())`；取：先建模型 → `load_state_dict` → `eval()`。**
> `state_dict = 参数 + buffer`，跨设备记得 `map_location`

# FP32 / FP16 / BF16 / 混合精度

这四个概念都围绕一个核心问题：**如何用更少的比特表示浮点数，从而在训练/推理时省显存、提速，同时尽量不损失精度。**

---

## 一、先理解浮点数的三要素

任何浮点数格式都由三段组成（IEEE 754 标准）：

```
[ 符号位 sign | 指数位 exponent | 尾数位 mantissa ]
      1 bit         决定范围         决定精度
```

- **符号位**：1 bit，正负。
- **指数位（exponent）**：决定这个数能表示**多大 / 多小**（动态范围）。
- **尾数位（mantissa / fraction）**：决定这个数的**有效数字位数**（精度）。

> 关键记忆：**指数位管"范围"，尾数位管"精度"**。这是理解 FP16 和 BF16 差异的钥匙。

---

## 二、三种格式逐位对比

| 格式     | 总位数 | 符号 | 指数 | 尾数 | 指数偏移 | 动态范围（约） | 十进制有效精度 |
| -------- | ------ | ---- | ---- | ---- | -------- | -------------- | -------------- |
| **FP32** | 32     | 1    | 8    | 23   | 127      | ±3.4×10³⁸      | ~7 位          |
| **FP16** | 16     | 1    | 5    | 10   | 15       | ±65504         | ~3 位          |
| **BF16** | 16     | 1    | 8    | 7    | 127      | ±3.4×10³⁸      | ~2 位          |

### 逐个拆解

**FP32（单精度，float）**

- 深度学习早期的默认格式，精度高、范围大。
- 缺点：显存占用大、计算慢。一张 24GB 卡存 FP32 模型，换成 FP16 能存近两倍。

**FP16（半精度，half）**

- 指数只有 **5 位**，所以动态范围很小，最大只有 **65504**。
- 尾数 10 位，精度尚可（约 3 位十进制）。
- 致命弱点：**容易溢出（overflow）或下溢（underflow）**。梯度、激活值稍大就会变成 `inf`，稍小就变成 `0`。这就是为什么需要 **loss scaling**（损失缩放）。

**BF16（Brain Float 16，bfloat16）**

- Google Brain 提出的格式。核心设计思想：**"偷" FP32 的指数位，牺牲尾数精度**。
- 指数位和 FP32 **完全一样（8 位）**，所以动态范围和 FP32 相同，**不会溢出**。
- 代价：尾数只有 7 位，精度比 FP16 还差（约 2 位十进制）。
- 直觉理解：**BF16 ≈ 把 FP32 截断保留高 16 位**，是 FP32 的"粗略近似"。

> 一句话对比：
>
> - **FP16 = 范围小、精度高** → 需要小心溢出
> - **BF16 = 范围大、精度低** → 稳，不易溢出，但有效数字少

---

## 三、为什么需要混合精度？

纯 FP16 训练的问题：

1. **梯度太小**：反向传播的梯度常常小到 1e-8，FP16 直接下溢成 0 → 训练不动。
2. **数值溢出**：大激活值超过 65504 → 变 `inf` → 权重被污染成 `NaN`。

**混合精度（Mixed Precision）** 的核心思想是：**把不同精度用在最合适的地方**。

典型策略（以 PyTorch AMP 为例）：

| 环节                         | 使用精度        | 原因                             |
| ---------------------------- | --------------- | -------------------------------- |
| 前向传播 / 矩阵乘法          | **FP16 / BF16** | 计算密集，用低精度加速、省显存   |
| 权重主副本（master weights） | **FP32**        | 参数更新需要高精度，避免累积误差 |
| 梯度累加 / 优化器更新        | **FP32**        | 防止小梯度下溢                   |
| Loss Scaling                 | 动态缩放        | 把 FP16 梯度放大后再算，避免下溢 |

### 动态损失缩放（Dynamic Loss Scaling）原理

```
1. 计算 loss
2. loss *= scale（比如 2^16）      # 放大，让梯度进入 FP16 可表示范围
3. 反向传播，得到放大的梯度
4. 梯度 /= scale                    # 还原
5. 如果检测到 inf/NaN → 减小 scale；若长期稳定 → 增大 scale
```

这就是 PyTorch `torch.cuda.amp.GradScaler` 帮你自动做的事。

---

## 四、PyTorch 代码示例

```python
import torch

# ---------- 1. 类型转换 ----------
x = torch.tensor([1.0, 2.0, 3.0], dtype=torch.float32)  # 默认 FP32
x_fp16 = x.half()          # 转 FP16
x_bf16 = x.bfloat16()      # 转 BF16

print(torch.finfo(torch.float16))   # 查看 FP16 范围/精度信息
print(torch.finfo(torch.bfloat16))

# ---------- 2. 混合精度训练（AMP 自动混合精度）----------
model = MyModel().cuda()
optimizer = torch.optim.Adam(model.parameters(), lr=1e-3)

# FP16 场景用 GradScaler 防下溢
scaler = torch.cuda.amp.GradScaler()

for data, target in dataloader:
    optimizer.zero_grad()

    with torch.autocast(device_type="cuda", dtype=torch.float16):
        output = model(data)          # 前向自动用 FP16
        loss = loss_fn(output, target)

    scaler.scale(loss).backward()     # 放大后反向传播
    scaler.step(optimizer)            # 内部先反缩放再更新
    scaler.update()                   # 动态调整 scale
```

**BF16 的简化**：因为 BF16 范围和 FP32 一样，**通常不需要 GradScaler**：

```python
with torch.autocast(device_type="cuda", dtype=torch.bfloat16):
    output = model(data)
    loss = loss_fn(output, target)

loss.backward()          # 直接反传即可
optimizer.step()
```

---

## 五、如何选择？（实用决策）

| 场景                                      | 推荐                   | 理由                                  |
| ----------------------------------------- | ---------------------- | ------------------------------------- |
| 老架构 GPU（V100、T4、RTX 20 系）         | **FP16 + GradScaler**  | 硬件支持 FP16 Tensor Core，但需防溢出 |
| 新架构 GPU（A100、H100、RTX 30/40/50 系） | **BF16**               | 原生支持 BF16，范围大、免缩放，更省心 |
| 需要最高数值稳定性（科学计算）            | **FP32**               | 精度优先                              |
| 大模型推理                                | **FP16 / BF16 / INT8** | 省显存、提吞吐                        |
| 训练大语言模型（LLM）                     | **BF16 为主**          | 稳定 + 省显存，已是行业默认           |

> **一句话总结选择逻辑**：
>
> - 硬件支持 BF16 就优先用 **BF16**（省心、稳）。
> - 只支持 FP16 就用 **FP16 + GradScaler**（需处理溢出）。
> - 追求极致精度或做数值敏感计算时用 **FP32**。

---

## 六、和其他概念的关系（延伸）

- **TF32**：NVIDIA A100 引入，19 位（1+8+10），介于 FP32 和 FP16 之间，**专用于矩阵乘法**，PyTorch 默认在 Ampere 及以上开启 `torch.backends.cuda.matmul.allow_tf32`。
- **FP8（E4M3 / E5M2）**：H100 及更新的卡支持，用于超大模型训练/推理，是当前最前沿方向。
- **INT8 / INT4**：量化推理，用整数表示，和浮点精度是另一条技术路线。

---

## 核心记忆点

1. **指数位管范围，尾数位管精度**。
2. **FP16**：范围小精度高 → 易溢出，需 loss scaling。
3. **BF16**：范围大精度低 → 稳定，免 scaling，现代首选。
4. **混合精度**：计算用低精度、累加/更新用 FP32，兼顾速度与稳定。
5. 选型看**硬件支持**：有 BF16 就用 BF16，否则 FP16+Scaler，精度敏感用 FP32。

# CUDA 内存管理、同步、性能计时

## 一、CUDA 内存管理：Caching Allocator

### 1.1 为什么 PyTorch 不直接调 `cudaMalloc`

CUDA 驱动层分配显存只有两个接口：`cudaMalloc` / `cudaFree`。它们的代价很高（要跟驱动做上下文交互、可能需要同步整个设备），如果每个张量都走一次，训练一个模型会死慢。

PyTorch 在底层内置了一个 **Caching Allocator（缓存分配器）**：

- **第一次分配时**：向驱动申请一大块显存，这块量叫 **reserved（保留量）**；
- **之后分配张量**：从已保留的大块里快速切一小块出来，几乎零开销，这部分叫 **allocated（实际占用量）**；
- **张量被释放时**：显存并不还给驱动，而是留在缓存池里给下一个张量复用。

所以你会看到两个数字永远不相等：

```python
import torch

x = torch.randn(1024, 1024, device="cuda")   # 触发首次分配，reserved 会暴涨
print("allocated:", torch.cuda.memory_allocated() / 1024**2, "MB")   # 实际被张量占用的
print("reserved :", torch.cuda.memory_reserved()  / 1024**2, "MB")   # 分配器从驱动扣住的

# 释放张量后：allocated 下降，reserved 基本不动
del x
print("after del, allocated:", torch.cuda.memory_allocated() / 1024**2, "MB")
print("after del, reserved :", torch.cuda.memory_reserved()  / 1024**2, "MB")
```

`torch.cuda.empty_cache()` 的作用是**把缓存池里空闲的块还给驱动**，`reserved` 会降下来。但注意：它不释放正在使用的张量，而且清空后下次分配又要重新申请，反而变慢。所以它是"给别的程序腾显存"用的，不是日常优化手段。

### 1.2 和你的 storage 知识呼应

还记得你之前学的 `storage` 吗？Tensor 的"壳"（shape/stride）和"数据"（storage）是分离的，显存管理作用于 **storage 这个真正的数据块**。多个 Tensor 可以共享同一个 storage（比如 `t.view()`），此时释放一个 Tensor 并不会真正释放显存——因为底层 storage 还被引用着。这也是显存"看着没释放"的常见原因之一。

### 1.3 常用诊断工具

```python
print(torch.cuda.memory_summary())   # 一页纸报告：分配块数、碎片、最大块等
print(torch.cuda.memory_allocated()) # 字节数
print(torch.cuda.memory_reserved())
```

### 1.4 显存"泄漏"的常见姿势（都是代码问题，不是真的泄漏）

```python
# 错误示范：循环里把中间结果都攒着
outs = []
for i in range(1000):
    outs.append(torch.randn(4096, 4096, device="cuda"))   # 全部常驻显存

# 正确做法：用完即丢，或用 inplace / 原地累加
```

还有一个要点：**Stream-Ordered Allocation（按流排序的分配）**。缓存分配器记住每个块是被哪个 CUDA stream 使用的，同一块显存可以跨 stream 复用而无需全局同步，靠事件（Event）来保证安全——这就引出第二部分的"同步"。

---

## 二、同步（Synchronization）：一切都是异步的

### 2.1 核心心智模型

CUDA 的模型是 **"提交-执行"分离**：

- 你写 `y = x * 2`，PyTorch 把内核**提交**到当前 stream 的队列里，**CPU 立刻返回**，继续跑下一行 Python；
- GPU 在后台排队执行这些内核。

所以整个程序的执行是"CPU 超前于 GPU"的（异步流水线）。大部分时候这是好事——CPU 在等 GPU 的时候可以提前提交更多工作，隐藏延迟。

### 2.2 什么操作会触发同步

一旦你需要**把数据从 GPU 拿回 CPU**，就必须等 GPU 干完活，于是发生隐式阻塞：

```python
y = x * 2
v = y.item()      # 阻塞：必须等 y 计算完成才能取值
arr = y.cpu()     # 阻塞：数据拷贝回 CPU
print(y)          # 阻塞：打印需要先读到数据
y.numpy()         # 阻塞（需要先 .cpu()）
```

还有**设备切换** `x.cuda()` / `.to("cuda")` 首次拷贝，也涉及同步。

### 2.3 显式同步

```python
torch.cuda.synchronize()   # 阻塞 CPU，直到当前设备上所有已提交工作完成
```

两条实践准则：

1. **调试时**：遇到莫名结果/时序问题，先在各步之间加 `torch.cuda.synchronize()` 定位；
2. **性能上**：不要随便加。它会把流水线打空（CPU 等待 GPU），吞吐掉得厉害。

### 2.4 Stream 与多流并发

默认所有内核都在 **default stream（当前流）** 里串行执行。想重叠两个互不依赖的计算，用多流：

```python
s1 = torch.cuda.Stream()
s2 = torch.cuda.Stream()

with torch.cuda.stream(s1):
    a = big_matmul(x, w)          # 提交到 s1
with torch.cuda.stream(s2):
    b = big_matmul(x2, w2)        # 提交到 s2，与 s1 并行执行

torch.cuda.synchronize()
```

如果流之间有依赖，用 **Event** 让 GPU 自己排队，而不是把 CPU 卡住：

```python
start_ev = torch.cuda.Event()
...
s2.wait_event(ev_on_s1)   # s2 等待 s1 的某个事件后再继续
```

---

## 三、性能计时：为什么 `time.time()` 是错的

### 3.1 经典错误

```python
import time

t0 = time.time()
y = big_matmul(x, w)      # 内核只是"提交"，没执行！
print(time.time() - t0)   # 测到的是提交开销，几乎是 0，完全没意义
```

由于异步，CPU 测到的时间跟 GPU 实际执行时间完全脱钩。

### 3.2 正确做法一：CUDA Event 计时（推荐）

```python
import torch

def bench(fn, iters=10):
    # 预热：把内核、cuDNN heuristics 都跑热
    fn()
    torch.cuda.synchronize()

    start = torch.cuda.Event(enable_timing=True)
    end   = torch.cuda.Event(enable_timing=True)

    start.record()                 # 在 GPU 时间线上打点
    for _ in range(iters):
        fn()
    end.record()
    torch.cuda.synchronize()       # 关键：等 GPU 全部完成

    return start.elapsed_time(end) / iters   # 单位毫秒，纯 GPU 时间

x = torch.randn(4096, 4096, device="cuda")
w = torch.randn(4096, 4096, device="cuda")

print(f"matmul avg: {bench(lambda: x @ w):.3f} ms")
```

Event 计时是在 **GPU 自己的时间线**上打点求差，测得的是真实的 GPU 执行时间，不受 CPU 调度噪声影响。

### 3.3 正确做法二：synchronize + time

```python
t0 = time.time()
y = x @ w
torch.cuda.synchronize()          # 先同步再取时间
print((time.time() - t0) * 1000, "ms")   # 包含 CPU 提交开销，适合测端到端
```

### 3.4 生产级工具：`torch.profiler`

逐算子级别的性能分析（哪一步最慢、内核占用率、显存分配）用 profiler：

```python
from torch.profiler import profile, ProfilerActivity

with profile(activities=[ProfilerActivity.CPU, ProfilerActivity.CUDA]) as prof:
    for _ in range(10):
        y = x @ w
    torch.cuda.synchronize()

print(prof.key_averages().table(
    sort_by="cuda_time_total", row_limit=10))
```

输出会按算子列出 CUDA 耗时、CPU 耗时、调用次数——这是定位瓶颈的正规工具。

# 自定义 C++ / CUDA 算子

## 一、什么是自定义算子

在深度学习框架（PyTorch / TensorFlow 等）里，**算子（Operator / Op）** 是构成计算图的最小单元，比如 `conv2d`、`matmul`、`relu`。

**自定义算子**就是框架官方没有提供、或官方实现满足不了你的需求，由你自己用 C++ / CUDA 写出来并注册进框架的算力单元。

典型组成：

| 层次       | 作用                            | 技术                               |
| ---------- | ------------------------------- | ---------------------------------- |
| 前端注册层 | 让 Python 能调用、接入 autograd | `torch.library`、`pybind11`        |
| 调度层     | 张量分发、类型/设备分发         | ATen、`AT_DISPATCH_FLOATING_TYPES` |
| 计算层     | 真正的数值计算                  | CUDA kernel / C++ 并行             |

---

## 二、为什么需要自定义算子

1. **性能**：官方算子通用但有开销。自定义可以做**算子融合**（如 `add + relu + layernorm` 合成一个 kernel），减少显存读写。
2. **框架支持不足**：新算子、科研中的特殊算法官方还没实现（如某些稀疏算子、量化算子）。
3. **算子融合与显存优化**：大模型推理中，KV-Cache、FlashAttention 这类都是高度定制 kernel。
4. **硬件特性**：用到 Tensor Core、`__shfl`、共享内存、TMA 等官方算子没用上的能力。

---

## 三、主流实现方式

### 1. `torch.utils.cpp_extension`（最常用，入门首选）

用 `load_inline` 快速试验，用 `CUDAExtension` 做正式工程化编译。

### 2. `torch.library` + C++（PyTorch 2.x 推荐）

新式注册 API，能更好地支持 `torch.compile`、FakeTensor、动态 shape。**现在的新项目推荐这条路。**

### 3. Triton（另一个赛道）

用 Python 写 kernel，编译器生成 PTX/SASS，比裸 CUDA 简单，性能接近手写。适合不想碰 CUDA C++ 的场景，但本文聚焦 C++/CUDA。

---

## 四、一个完整示例：自定义 ReLU（前置）CUDA 算子

### C++ 包装 + 绑定（`relu.cpp`）

```cpp
#include <torch/extension.h>
#include <cuda_runtime.h>

// CUDA kernel 声明
torch::Tensor relu_cuda_forward(torch::Tensor x);

// 前向：检查合法性 + 调用 CUDA
torch::Tensor relu_forward(torch::Tensor x) {
    TORCH_CHECK(x.is_cuda(), "x must be a CUDA tensor");
    TORCH_CHECK(x.scalar_type() == torch::kFloat32, "x must be float32");
    return relu_cuda_forward(x.contiguous());
}

// 前向/反向注册（这里只注册 forward）
PYBIND11_MODULE(TORCH_EXTENSION_NAME, m) {
    m.def("forward", &relu_forward, "ReLU forward (CUDA)");
}
```

### CUDA kernel（`relu_cuda.cu`）

```cpp
#include <torch/extension.h>
#include <cuda_runtime.h>

__global__ void relu_kernel(const float* __restrict__ in,
                            float* __restrict__ out,
                            int64_t n) {
    int64_t i = blockIdx.x * (int64_t)blockDim.x + threadIdx.x;
    if (i < n) out[i] = in[i] > 0.f ? in[i] : 0.f;
}

torch::Tensor relu_cuda_forward(torch::Tensor x) {
    auto out = torch::empty_like(x);
    int64_t n = x.numel();
    const int threads = 256;
    const int blocks = (n + threads - 1) / threads;
    relu_kernel<<<blocks, threads>>>(
        x.data_ptr<float>(), out.data_ptr<float>(), n);
    return out;
}
```

### 编译与调用（Python）

```python
from torch.utils.cpp_extension import load

relu = load(
    name="relu_ext",
    sources=["relu.cpp", "relu_cuda.cu"],
    extra_cuda_cflags=["-O3", "--use_fast_math"],
    verbose=True,
)

import torch
x = torch.randn(1 << 20, device="cuda")
y = relu.forward(x)
print(torch.allclose(y, torch.relu(x)))  # True
```

编译时你需要本机有 **CUDA Toolkit** 和 **nvcc**，`load()` 会自动调用 `ninja` / `setuptools` 构建。

---

## 五、接入反向传播（autograd）

自定义算子想被训练使用，必须提供反向。两种方式：

1. **`torch.autograd.Function`**：Python 里包一层，`forward` 调 C++、`backward` 也调 C++。
2. **`torch.library` 注册 + `torch.autograd` 公式**：现代方式，更契合 `torch.compile`。

以 `torch.library` 为例（PyTorch 2.x）：

```cpp
TORCH_LIBRARY(myops, m) {
    m.def("relu(Tensor x) -> Tensor");
}
TORCH_LIBRARY_IMPL(myops, CUDA, m) {
    m.impl("relu", &relu_cuda_forward);
}
```

反向可用 `torch.library.register_autograd` 或手写 `backward` 注册。

---

## 六、关键技术点与性能优化

| 技术点                   | 说明                                                         |
| ------------------------ | ------------------------------------------------------------ |
| `__restrict__` + `const` | 帮助编译器优化、避免寄存器复用错误                           |
| 合并访存（coalesced）    | 相邻线程读相邻地址，最大化显存带宽                           |
| 共享内存                 | 复用数据、减少全局显存访问（如矩阵分块）                     |
| 向量化读写               | 用 `float4` / `int4` 一次搬 16 字节                          |
| 减少分支发散             | warp 内分支一致，避免串行化                                  |
| 算子融合                 | 多个 elementwise 操作合成一个 kernel，减少 kernel launch 与显存往返 |
| 流（Stream）             | 用 CUDA stream 做异步与流水线                                |
| `cudaOccupancy`          | 根据寄存器/共享内存占用选 block size                         |

**瓶颈判断**：是 memory-bound（带宽瓶颈，如 elementwise）还是 compute-bound（算力瓶颈，如 matmul）。elementwise 类几乎一定 memory-bound，所以要尽量融入多个操作。

---

## 七、调试与验证工具

- `compute-sanitizer`（旧名 `cuda-memcheck`）：检测越界、未初始化访存。
- `nsys` / `ncu`（Nsight）：profiling，看 kernel 时间、占用率、带宽利用率。
- `CUDA_LAUNCH_BLOCKING=1`：让 kernel 同步执行，便于定位报错。
- 与官方实现对比：`torch.allclose` 验证数值一致性，注意浮点误差用 `rtol/atol`。

---

## 八、常见应用场景

- **大模型**：FlashAttention、PagedAttention（vLLM）、KV-Cache 管理、RoPE。
- **量化**：INT8/INT4 反量化、混合精度算子。
- **稀疏**：稀疏矩阵乘、稀疏注意力。
- **特殊激活 / 融合**：Fused MLP、Fused LayerNorm。
- **领域算子**：3D 点云、图神经网络、自定义损失函数。

---

## 小结

自定义 C++/CUDA 算子的核心公式是：

> **一个 CUDA kernel 负责算 + 一个 C++ 层负责张量/类型/设备检查 + 一层绑定让它能从 Python 调用并接入 autograd。**