# import torch

# t = torch.arange(1, 7).reshape(2, 3)
# # [[1, 2, 3],
# #  [4, 5, 6]]
# print(t.shape)
# print(t.stride()) 
# print(t.storage())

import torch
import torch.nn as nn

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

import torch

x = torch.randn(1024, 1024, device="cuda")   # 触发首次分配，reserved 会暴涨
print("allocated:", torch.cuda.memory_allocated() / 1024**2, "MB")   # 实际被张量占用的
print("reserved :", torch.cuda.memory_reserved()  / 1024**2, "MB")   # 分配器从驱动扣住的

# 释放张量后：allocated 下降，reserved 基本不动
del x
print("after del, allocated:", torch.cuda.memory_allocated() / 1024**2, "MB")
print("after del, reserved :", torch.cuda.memory_reserved()  / 1024**2, "MB")

