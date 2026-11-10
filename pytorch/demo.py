# import torch

# t = torch.arange(1, 7).reshape(2, 3)
# # [[1, 2, 3],
# #  [4, 5, 6]]
# print(t.shape)
# print(t.stride())
# print(t.storage())


# class Block(nn.Module):
#     def __init__(self):
#         super().__init__()
#         self.weight = nn.Parameter(torch.ones(2,2))
#         self.register_buffer('scale', torch.tensor(2.0))
#         self.plain = torch.tensor(3.0)

#     def forward(self, x):
#         return (x @ self.weight) * self.scale

# b = Block()

# print([n for n, _ in b.named_parameters()])
# print([n for n, _ in b.named_buffers()])
# print(list(b.state_dict().keys()))
# print(len(list(b.parameters())))


# x = torch.tensor([1.0, 2.0, 3.0], dtype=torch.float32)
# x16 = x.half()
# xbf16 = x.bfloat16()

# print(torch.finfo(torch.float16))   # 查看 FP16 范围/精度信息
# print(torch.finfo(torch.bfloat16))

# import torch

# x = torch.randn(1024, 1024, device="cuda")   # 触发首次分配，reserved 会暴涨
# print("allocated:", torch.cuda.memory_allocated() / 1024**2, "MB")   # 实际被张量占用的
# print("reserved :", torch.cuda.memory_reserved()  / 1024**2, "MB")   # 分配器从驱动扣住的

# # 释放张量后：allocated 下降，reserved 基本不动
# del x
# print("after del, allocated:", torch.cuda.memory_allocated() / 1024**2, "MB")
# print("after del, reserved :", torch.cuda.memory_reserved()  / 1024**2, "MB")

import torch
import torch.nn.functional as F
import math

Q = torch.tensor([[1, 0, 1, 0], [0, 1, 0, 1], [1, 1, 0, 0]], dtype=torch.float32)

K = torch.tensor([[1, 1, 0, 0], [0, 0, 1, 1], [1, 0, 1, 0]], dtype=torch.float32)

V = torch.tensor([[1, 0, 0, 1], [0, 1, 1, 0], [1, 1, 0, 0]], dtype=torch.float32)

d_k = Q.size(-1)

scores = torch.matmul(Q, K.transpose(-2, -1))
print("注意力分数 QK^T", scores)

scaled_scores = scores / math.sqrt(d_k)
print("缩放后分数 \n", scaled_scores)

atten_weight = F.softmax(scaled_scores, dim=1)
print("注意力权重 \n", atten_weight)

output = torch.matmul(atten_weight, V)
print("最终输出 \n", output)