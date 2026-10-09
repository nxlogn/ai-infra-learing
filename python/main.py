# if __name__ == "__main__":
#     print("直接运行才会执行")

# nums = [1, 2, 3]
# it = iter(nums)
# while True:
#     try:
#         x = next(it)
#         print(x)
#     except StopIteration:
#         break

# from functools import wraps
# def log(func):
#     @wraps(func)
#     def wrapper(*args, **kwargs):
#         print(f"调用 {func.__name__}")
#         result = func(*args, **kwargs)
#         print(f"结果为 {result}")
#         return result
#     return wrapper
# @log
# def add(a, b):
#     return a + b

# a = add(1,2)
# print(a)

# from functools import wraps
# import time

# def timed(func):                          # 装饰器：计时
#     @wraps(func)
#     def wrapper(*args, **kwargs):
#         start = time.perf_counter()
#         result = func(*args, **kwargs)
#         print(f"{func.__name__} 耗时 {time.perf_counter() - start:.4f}s")
#         print(f"result为 {result}")
#         return result
#     return wrapper

# @timed
# def consume(gen):                         # 接收生成器，惰性消费
#     total = 0
#     for x in gen:                         # for 自动走迭代器协议
#         total += x
#     return total

# consume(x * x for x in range(1_000_000))  # 生成器表达式 + 装饰器

# import json
# data = {"age": 12}
# with open("data2.json", "a", encoding="utf-8") as f:
#     json.dump(data, f, ensure_ascii = False, indent = 2)

import numpy as np

# a = np.array([1, 2, 3])
# b = np.array([4, 5, 6])
# print(a + b)
# print(a * 10)

print(np.array([1, 2.5]).dtype)