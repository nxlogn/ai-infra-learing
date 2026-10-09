import torch

t = torch.arange(1, 7).reshape(2, 3)
# [[1, 2, 3],
#  [4, 5, 6]]
print(t.shape)
print(t.stride()) 
print(t.storage())