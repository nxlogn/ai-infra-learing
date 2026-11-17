# 推理优化学习路线：先云端就业，后端侧扩展

> 制定时间：2026-11-17
> 配套清单：[infralearn.md](infralearn.md)（本文档按阶段重新排定其优先级）
> 总策略：**Phase 1 云端冲刺拿 offer（2026-11 ~ 2027-02）→ 春招投递 → Phase 2 入职后端侧扩展（第二曲线）**

---

## 一、为什么是这个顺序

### 1.1 技能迁移不对称

| 方向 | 迁移成本 | 说明 |
|---|---|---|
| 云端 → 端侧 | 低 | 量化、KV cache、算子融合、roofline、C++ runtime 全部复用，只需补 ARM/DSP/NPU 工具链 |
| 端侧 → 云端 | 高 | RKNN/MNN 经验在云端面试几乎不加分，CUDA、分布式、vLLM 调度需从头补 |

先学覆盖面大的技能栈，是占优策略。

### 1.2 三个终端方向的真实技术栈

| 终端 | 主流硬件/栈 | 云端技能复用度 | 端侧增量 |
|---|---|---|---|
| **车载** | NVIDIA Orin/Thor：CUDA + TensorRT | **~80%，几乎直接覆盖** | DriveOS、车规安全、实时性 |
| **手机** | 高通 QNN/Hexagon DSP、联发科 APU；ExecuTorch、MNN | ~50%（量化、图优化、runtime 原理） | ARM NEON、DSP 工具链、Android 集成 |
| **眼镜/IoT** | RKNN、MCU/DSP、Ambiq 等超低功耗平台 | ~40%（原理层） | NPU SDK、极限内存/功耗优化 |

结论：车载方向基本被 Phase 1 覆盖；手机/眼镜是 Phase 2 的真正增量。

### 1.3 风险与修正

- **端侧岗位量目前远少于云端**，集中在芯片厂（高通/联发科/瑞芯微）、手机厂、车厂/Tier1。
  端侧适合作为入职后的第二曲线，不作为第一份工作的赌注。
- **拿到 offer 前不双线并行**。llama.cpp 可当睡前读物，但不投项目时间。
- 端侧 LLM 仍在早期，当前端侧岗位大头仍是传统 CV/语音推理，Phase 2 要两条腿都看。

---

## 二、Phase 1：云端冲刺（2026-11 ~ 2027-02，约 3.5 个月）

目标：**2027 年 2 月项目出数据，3 月赶上春招投递。**

### 2.1 infralearn.md 优先级重排

| infralearn 章节 | 原定位 | Phase 1 定位 |
|---|---|---|
| 1 C/C++ | 已完成 | 维持，leetcode 不停（面试硬门槛） |
| 2 Python | 未完成 | **必修**，vLLM 源码是 Python，2 周内补完核心项 |
| 3 PyTorch | 未完成 | **必修**，重点：Profiler、混合精度、自定义 C++/CUDA 算子 |
| 4 Linux | 未完成 | **必修**，重点：SSH 远程开发、Docker、perf |
| 5 体系结构 | 未完成 | **必修**，重心放 GPU（SM/warp/显存带宽/roofline），CPU 部分已有基础 |
| 6 Transformer | 未完成 | **必修，最高优先级**，面试核心 |
| 7 LLM 推理技术 | 未完成 | **必修，最高优先级**，逐项能画图讲清 |
| 8 框架源码 | 四选一 | **vLLM 深入 + SGLang 对比**；TensorRT-LLM 了解 trade-off；ONNX Runtime 移到 Phase 2 |
| 9 C++ Runtime | 未完成 | 半必修：读 vLLM/llama.cpp 的 C++ 部分时顺带覆盖，不必单独攻 |
| **10 CUDA** | **加分项** | **改为必修核心**——云端岗与端侧岗的最大区别，绕不过去 |
| 11 AI 编译器 | 加分项 | 延后，除非目标 TVM/MLIR 团队 |
| 12 多卡/NPU | 加分项 | 多卡（TP/PP/NCCL）第 4 个月补原理；NPU/RISC-V 整体移到 Phase 2 |

工具替换：valgrind → **Nsight Systems + Nsight Compute + torch.profiler**（py-spy、perf 保留）。

### 2.2 月度安排

**第 1 个月（2026-11 中 ~ 12 中）：原理 + CUDA 入门 + 环境**
- [ ] Transformer / prefill-decode / KV cache 原理过一遍，能手画 attention 数据流
- [ ] PMPP 前 8 章 + 手写 reduce、softmax、naive GEMM（仓库已有 cuda/ 目录，直接用）
- [ ] 租卡（AutoDL 4090，约 1–2 元/小时），vLLM 部署 Qwen2.5-7B，跑通 benchmark
- [ ] 学会测 TTFT / ITL / 吞吐 / 峰值显存，理解每个指标的含义
- [ ] Python 核心项补完（infralearn 第 2 节）

**第 2 个月（12 中 ~ 1 中）：vLLM 源码 + 项目启动**
- [ ] vLLM 主链路源码：scheduler → KV cache manager（PagedAttention）→ continuous batching → chunked prefill / prefix caching
- [ ] Nsight Systems / Compute 上手，对自己写的 kernel 做 roofline 分析
- [ ] 选定项目路线（见 2.3）并搭好骨架
- [ ] FlashAttention 论文 + 实现读懂

**第 3 个月（1 中 ~ 2 中）：项目做深 + 量化 + 对比**
- [ ] 项目出可量化数据（加速比 / 吞吐差距 + 源码级归因）
- [ ] 量化：FP8、AWQ/GPTQ、W4A16（Marlin kernel），在租的卡上实测精度/速度 trade-off
- [ ] SGLang 部署同一模型，对比 RadixAttention 与 vLLM prefix caching 的行为差异
- [ ] 整理成 GitHub README + 1~2 篇技术博客

**第 4 个月（2 中 ~ 3 月）：补漏 + 投递**
- [ ] 分布式原理：TP/PP、NCCL、All-Reduce（单卡即可学原理）
- [ ] 八股整理：第 6/7 节每一项准备 3 分钟口述版
- [ ] leetcode 保持每天 1–2 题（C++）
- [ ] **2 月底开始投递，不等"学完"**；有余力给 vLLM/SGLang 提实质性 PR

### 2.3 项目三选一（贴 C++ 背景优先 A）

| 路线 | 内容 | 产出 |
|---|---|---|
| **A 手写 mini 引擎（推荐）** | paged KV cache + continuous batching，跑通小模型，与 vLLM 对比 | 吞吐差距 + "为什么差"的源码级分析 |
| B kernel 优化 | Triton/CUDA 写 fused kernel 或 W4A16 GEMM | Nsight 剖析 + roofline + 加速比 |
| C 系统基准 | vLLM vs SGLang 多负载基准（长输入/高并发/多轮 prefix 命中）或 speculative decoding 收益实验 | TTFT/TPOT/吞吐报告 + 归因 |

注意："用 vLLM 部署了个模型"不算项目，人人都会；区分度来自**能解释为什么快/慢**。

预算：租卡几百元足够全程（7B 模型单张 4090 够用）。

---

## 三、Phase 2：端侧扩展（入职后，约 2027 年中启动，6~12 个月）

原则：**用业余时间推进，服务长期方向（手机/眼镜/车载），不与主业冲突。**
此时已有工资和云端工程经验，学端侧是"补工具链"而不是"从零学推理"。

### 3.1 复用与增量

直接复用（Phase 1 已覆盖）：
- Transformer/LLM 推理原理、KV cache、量化原理（INT4/INT8）
- 算子融合、内存规划、roofline、性能分析方法论
- C++ runtime 能力（infralearn 第 9 节此时正式补全）
- 车载方向：CUDA + TensorRT 基本即战力

需要新补：
- [ ] ARM 体系结构：NEON/SVE、大小核、移动端内存层次
- [ ] llama.cpp 源码精读（量化格式、KV cache、CPU/CUDA 后端抽象——C++ 背景的最佳切入点）
- [ ] MNN 或 ExecuTorch 源码选一个深入（手机端推理 runtime）
- [ ] ONNX Runtime：EP 机制、模型转换链路（云端/端侧通用胶水）
- [ ] NPU 工具链实操：RKNN-Toolkit 模型转换、量化、板端部署

### 3.2 按目标方向选修

| 方向 | 补什么 | 实践载体 |
|---|---|---|
| 车载 | TensorRT 深入（Phase 1 只到了解级）、DriveOS、实时性/确定性 | Orin Nano 开发板（或继续租云 GPU） |
| 手机 | 高通 QNN SDK、Hexagon DSP 概念、ExecuTorch/MNN 的 Android 集成 | 自己的手机跑 llama.cpp / MNN LLM demo |
| 眼镜/IoT | RKLLM、MCU 级推理（TFLite Micro 概念）、极限功耗优化 | **RK3588 开发板（几百元）**，跑 RKLLM 小模型 |

推荐第一个硬件投入：**RK3588 板子**——便宜、覆盖 NPU 全流程（转换→量化→部署→profiling），
且瑞芯微生态岗位在端侧里相对多。手机方向零成本（用自己的手机）。

### 3.3 Phase 2 项目建议

- [ ] llama.cpp 在 RK3588 / 手机上的部署 + 量化精度/速度评测报告
- [ ] 给 llama.cpp 或 MNN 提 PR（ARM NEON kernel 优化、新模型支持）
- [ ] 同一个模型在 云 GPU / Orin / RK3588 / 手机 四个平台的横向推理评测（独家素材，云端+端侧双背景才做得出）

### 3.4 长期定位

云端 + 端侧双栈 → **端云协同推理**方向（云端大模型 + 端侧小模型路由、speculative decoding 的端云变体、
模型分级部署）。这是纯云端或纯端侧工程师都做不了的位置，也是"先云端后端侧"路线的最终红利。

---

## 四、里程碑检查点

| 时间 | 检查点 | 未达标动作 |
|---|---|---|
| 2026-12 中 | 手写 GEMM 达到 cuBLAS 30%+ 性能；vLLM 跑通并会 benchmark | 砍掉周边内容，保 CUDA + 原理 |
| 2027-01 中 | 能脱稿讲清 vLLM scheduler + PagedAttention 全流程 | 项目降级为路线 C（工作量最小） |
| 2027-02 底 | 项目有数据、README 完整、博客 ≥1 篇 | 直接投递，面试倒逼补漏 |
| 2027-03 | 春招投递中，leetcode 累计 ≥200 题 | — |
| 入职 +3 月 | 主业站稳，Phase 2 启动（llama.cpp 精读） | 延后，主业优先 |
| 入职 +9 月 | 端侧第一个硬件项目完成 | — |

## 五、资源清单

- CUDA：PMPP（*Programming Massively Parallel Processors*）；NVIDIA 官方 CUDA C++ Programming Guide
- LLM 推理：vLLM / SGLang 官方文档与源码；FlashAttention、PagedAttention 论文
- kernel：Triton 官方 tutorials；CUTLASS（进阶）
- 端侧：llama.cpp / MNN / ExecuTorch 源码；RKNN-Toolkit2 文档；高通 QNN SDK
- 性能：Nsight Systems / Compute 官方 guide；Brendan Gregg《Systems Performance》（perf 部分）
