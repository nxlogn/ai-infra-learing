**1. C / C++**

- [x] 指针、引用、const、对象生命周期
- [x] RAII、智能指针、内存管理
- [x] 拷贝语义、移动语义
- [x] STL 容器与算法
- [x] 模板、函数对象、Lambda
- [x] 数据结构与算法

- 多线程、互斥锁、条件变量、原子操作
- 内存布局、对齐、缓存局部性
- CMake、GDB、AddressSanitizer

**2. Python**

- 基本语法、内置类型、容器
- 切片、解包、推导式
- 函数、参数、作用域、闭包
- 类、继承、特殊方法
- 可变对象、引用、浅拷贝与深拷贝
- 模块、包、虚拟环境、依赖管理
- 异常处理、上下文管理器
- 迭代器、生成器、装饰器
- 类型标注、dataclass
- 文件操作、JSON、日志、命令行参数
- pytest、断点调试
- asyncio、多线程、多进程
- NumPy

**3. PyTorch**

- Tensor、shape、dtype、device
- 广播、索引、矩阵乘法
- stride、连续性、view、reshape、transpose
- nn.Module、Parameter、buffer
- 常用网络层与算子
- autograd、训练与推理模式
- state_dict、模型保存与权重加载
- FP32、FP16、BF16、混合精度
- CUDA 内存管理、同步、性能计时
- PyTorch Profiler
- 自定义 C++ / CUDA 算子

**4. Linux 开发**

- Shell、文件权限、环境变量
- 进程、线程、信号
- 虚拟内存、动态库
- 编译、链接、构建
- Git
- GDB、perf、日志分析
- SSH、远程开发
- Docker 基础

**5. 计算机体系结构与并行计算**

- CPU / GPU / NPU / DSA 架构
- 寄存器、Cache、主存、显存、片上 SRAM
- 指令流水线、指令级并行
- SIMD、SIMT、线程级并行
- 内存带宽、访问延迟、数据复用
- DMA、数据搬运、计算与传输重叠
- 计算密集型与访存密集型任务
- 算术强度、Roofline 模型
- 算子分块、数据布局、并行调度

**6. Transformer 与大模型结构**

- Tokenization、Embedding
- Q / K / V、Self-Attention、Causal Mask
- MHA、MQA、GQA
- RoPE
- LayerNorm、RMSNorm
- FFN / MLP、SiLU、SwiGLU
- 残差连接
- Softmax、采样、逐 token 生成
- Prefill、Decode
- MoE、专家路由、MLA
- Qwen、Llama、DeepSeek 的结构与算子差异

**7. LLM 核心推理技术**

- KV Cache
- PagedAttention
- Continuous Batching
- Chunked Prefill
- Prefix Caching
- FlashAttention
- Speculative Decoding
- 算子融合
- 内存复用与显存管理
- CUDA Graph
- 权重、激活、KV Cache 量化
- FP8、INT8、INT4
- AWQ、GPTQ、SmoothQuant
- TTFT、ITL、吞吐、峰值显存、性能分析

**8. 推理框架源码：至少深入一种**

- vLLM
- TensorRT-LLM
- SGLang
- ONNX Runtime

需要理解的模块：

- 模型加载与权重转换
- 模型执行流程
- 请求调度与批处理
- KV Cache 管理
- 算子注册、分发与后端选择
- 内存分配与复用
- 并行执行与通信
- 新模型、新算子、新硬件适配
- 正确性测试与性能测试

**9. C++ Runtime 与芯片适配**

- Tensor 表示：shape、dtype、stride、layout
- Buffer、内存池、资源生命周期
- 计算图表示与执行计划
- 算子接口、注册与分发
- Device / Backend 抽象
- Host / Device 内存传输
- 执行队列、异步执行、事件与同步
- 编译器生成算子的接入
- ABI、参数传递、内存布局约定
- 动态 shape
- 模型数值对齐与误差分析
- 硬件不支持算子的处理
- 系统级性能定位

**10. 加分项：CUDA**

- Grid、Block、Thread、Warp、SM
- Global / Shared / Register Memory
- 合并访存、Bank Conflict
- Warp Shuffle、并行归约
- 同步、原子操作
- Stream、Event、异步拷贝
- Tensor Core
- GEMM、归一化、Attention 算子优化
- Nsight Systems、Nsight Compute
- Triton、CUTLASS

**11. 加分项：AI 编译器**

- MLIR / TVM / XLA / Glow，选择一种
- 编译器前端、模型导入
- IR、计算图、类型与 shape 推导
- Pass、图变换、算子融合
- 常量折叠、死代码消除
- Layout 变换、内存规划
- Lowering、代码生成
- 编译产物与 Runtime 对接

**12. 加分项：多卡推理与自研 NPU**

- 张量并行、流水线并行、数据并行、专家并行
- All-Reduce、All-Gather、Reduce-Scatter、All-to-All
- NCCL / HCCL
- 通信与计算重叠
- PCIe、NVLink、RDMA / RoCE
- RISC-V 指令集基础
- NPU / ASIC 架构与 SDK
- NPU 算子开发、模型适配、Runtime 开发
