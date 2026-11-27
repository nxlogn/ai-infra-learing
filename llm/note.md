# 大模型原理学习笔记

## Q：为什么梯度可以流过百层网络？和残差连接的关系是什么？

残差连接正是"深度可训练"的核心发明。分四步：先看没有残差时梯度为什么必死，再看残差如何改写链式法则，然后说清楚它为什么还不是全部。

### 1. 问题根源：链式法则把梯度变成"连乘"

普通网络 $x_{l+1} = f_l(x_l)$，反向传播时：

$$\frac{\partial L}{\partial x_l} = \frac{\partial L}{\partial x_N} \cdot \prod_{i=l}^{N-1} \frac{\partial f_i}{\partial x_i}$$

梯度是每层雅可比矩阵的**连乘**。连乘对"每层的增益"极端敏感：

- 每层典型增益 0.9 → $0.9^{100} \approx 2.7\times10^{-5}$，梯度消失；
- 每层典型增益 1.1 → $1.1^{100} \approx 13780$，梯度爆炸。

100 层意味着要把增益精确控制在 1 附近，而饱和激活（sigmoid 导数最大 0.25）、随机初始化的权重矩阵都会把增益往下拉。**深层网络不是"学不好"，是浅层根本收不到学习信号。**

### 2. 残差连接：把连乘改写成"带 1 的乘积"

残差块 $x_{l+1} = x_l + F_l(x_l)$，雅可比变成：

$$\frac{\partial x_{l+1}}{\partial x_l} = I + J_{F_l}$$

于是：

$$\frac{\partial L}{\partial x_l} = \frac{\partial L}{\partial x_N} \prod_{i=l}^{N-1}(I + J_{F_i}) = \frac{\partial L}{\partial x_N}\Big(\underbrace{I}_{\text{恒等直通}} + \sum_i J_{F_i} + \sum_{i<j} J_{F_j}J_{F_i} + \cdots\Big)$$

展开后关键就在那个 **$I$**：它代表一条**不经过任何权重矩阵、从 loss 直达第 $l$ 层的高速公路**。哪怕所有分支的雅可比都趋于 0，梯度也至少原样传回——消失的下界被钉死了。

两个推论：

- **梯度从"一条长链的乘积"变成"指数多条路径的求和"**（$2^{N-l}$ 条）。Veit et al. 2016 发现其中**短路径贡献占主导**——ResNet 行为上更像"浅层网络的集成"，这解释了为什么删掉 ResNet 的单个块几乎无损，而删掉 VGG 的一层直接崩溃。
- 爆炸也被缓解：分支初始化得小，$I + J_F \approx I$，增益天然贴近 1。

### 3. 前向视角：学"修正量"比学"完整变换"容易

He et al. 提出 ResNet 的原始动机是**退化问题**：56 层普通网络的*训练*误差比 20 层还高（不是过拟合）。理论上深层网络只要把多出的层学成恒等映射就不该更差，但 SGD 找不到这个解。

残差结构把恒等映射变成了**默认值**：想让一层"什么都不做"，只需 $F_l \approx 0$（权重压向 0 即可）；而普通层要学恒等，得让一整堆非线性层精确拟合 $y=x$，极难。所以深层网络从"接近恒等"出发，每层只学一点修正——优化难度骤降。

这也是机制可解释性里"残差流（residual stream）"视角的由来：整条网络是一条共享总线，每层往上读信息、写一点增量。

### 4. 但残差不是全部：百层 LLM 的完整配方

严格说，"恒等高速公路"论证要求残差路径上**没有任何东西**。原始 Transformer 是 **Post-LN**（LayerNorm 加在残差相加*之后*），高速公路上横着一个 LN 的雅可比，深层照样难训、必须小心 warmup。现代 LLM 全部改用 **Pre-LN**（LN 放在分支*内部*）：

$$x_{l+1} = x_l + F_l(\text{LN}(x_l))$$

残差路径是纯恒等，高速公路完全干净——这才是 GPT/LLaMA 能堆到 80~100+ 层的直接原因。

其余配套缺一不可：

- **非饱和激活**（ReLU/GELU/SwiGLU）：避免 sigmoid 那种导数 ≤ 0.25 的天然衰减；
- **缩放初始化**：如 GPT-2 把每个分支的输出投影按 $1/\sqrt{2N}$ 缩放，保证初始时所有分支贡献加起来方差可控，网络起点接近恒等；
- **Warmup + Adam**：前者避开训练初期大步长破坏残差平衡，后者按参数自适应缩放梯度，缓解病态条件数；
- **梯度裁剪**：兜底防爆炸。

**一句话总结：残差把梯度的"连乘"改写成"含恒等项的求和"，Pre-LN 保住这条恒等通路，初始化和激活函数保证分支增益温和——三者合起来才让百层可训。**

### 联系推理方向

残差相加本身是逐元素操作，计算量近乎为零但**纯访存**。所以 vLLM / TensorRT-LLM 的标准优化是把 `residual add + RMSNorm` 融合成一个 kernel——否则每层都要为这两个小操作各读写一遍 HBM，decode 阶段这种"碎访存"累积起来相当可观。vLLM 的 `fused_add_rms_norm` kernel 对应的正是上面那条公式。

## Q：为什么 Transformer 用 LayerNorm 而不是 BatchNorm？

核心一句话：**BN 的统计量依赖"别的样本"，LN 的统计量只依赖"当前 token 自己"**。自回归语言模型的三个特性——变长序列、因果性、decode 时 batch 任意小——把 BN 的前提全部打碎了。

### 1. 归一化的轴不同

设激活张量形状为 $(B, T, d)$（batch × 序列长 × 隐藏维）：

- **BatchNorm**：对每个特征通道 $c$，跨 batch（和时间）求统计量：

$$\mu_c = \frac{1}{BT}\sum_{b,t} x_{b,t,c}, \qquad \hat{x}_{b,t,c} = \gamma_c\frac{x_{b,t,c}-\mu_c}{\sqrt{\sigma_c^2+\epsilon}}+\beta_c$$

- **LayerNorm**：对每个 token $(b,t)$，跨隐藏维 $d$ 求统计量：

$$\mu_{b,t} = \frac{1}{d}\sum_c x_{b,t,c}, \qquad \hat{x}_{b,t,c} = \gamma_c\frac{x_{b,t,c}-\mu_{b,t}}{\sqrt{\sigma_{b,t}^2+\epsilon}}+\beta_c$$

BN 问的是"这个特征在整个数据集里 typical 值是多少"，LN 问的是"这个 token 的激活向量自己长什么样"。

### 2. BN 在 CNN 里成立的前提，NLP 全不满足

BN 在视觉里好用，是因为一个 channel 的语义在空间上**平稳**（比如"边缘检测器"在图像任何位置分布都差不多），跨 batch 估计的均值方差是稳定、有意义的。NLP 里：

- **分布非平稳 + 变长**：第 1 个 token 和第 500 个 token 的分布完全不同；batch 内序列长短不齐，padding 位置混进统计量。同一 channel 跨 batch×time 的统计量剧烈波动——Shen et al. 2020（PowerNorm）实测 Transformer 里 BN 的 batch 统计量方差远大于 CNN，训练因此不稳。
- **训练/推理不一致**：BN 推理时用训练期累积的 running mean/var。但自回归解码一次生成一个 token，生成分布和训练分布不同、batch 可能只有 1，running 统计量根本不可靠。LN 每个 token 现算，**训练和推理的计算完全一致**，没有任何跨样本状态。
- **因果性**：若沿时间轴归一化，统计量会用到未来 token——对 causal LM 是直接的信息泄漏。即使只跨 batch，也让同 batch 样本的梯度互相耦合，破坏"每条序列独立"的语义。
- **小 batch**：LLM 长序列极吃显存，per-device micro-batch 往往很小，BN 统计量噪声大。

### 3. LN 为什么恰好合适

- **per-token 自包含**：不依赖 batch 里其他序列、不依赖其他位置 → 天然兼容变长、padding、流式解码、任意 batch size；
- **稳定残差流**：把每个 token 的激活向量拉回可控尺度，和 Pre-LN 结构（见上一篇）配合，保住恒等高速公路；
- **无状态**：没有 running statistics，训练/推理零差异，也方便张量并行（统计量只在 hidden 维内部，不跨样本）。

### 4. 再进一步：现代 LLM 连 LN 都简化成了 RMSNorm

LN 做两件事：re-centering（减均值）+ re-scaling（除标准差）。实验发现减均值基本不必要，于是 RMSNorm 只保留缩放：

$$y = \frac{x}{\sqrt{\frac{1}{d}\sum_i x_i^2+\epsilon}}\odot g$$

少算一次均值、少一次减法，效果几乎不变。LLaMA / Qwen / GPT-NeoX 全用 RMSNorm。

### 联系推理方向

一个有趣的反转：**BN 推理时是固定仿射变换，可以折叠进前面的线性层权重（BN folding），推理零开销；LN/RMSNorm 的统计量依赖当前输入，无法折叠，每层必须在线计算**。所以 LN 是"训练语义上赢、推理计算上输"的选择——但输掉的这点计算是纯访存：

- RMSNorm 是对 hidden 维的 row-wise reduction，算术强度极低，典型 memory-bound 小算子；
- 这正是上一篇 `fused_add_rms_norm` 的动机：residual add + RMSNorm 融合，省一遍 HBM 读写；
- serving 端 continuous batching 让 batch 组成每一步都在变，任何依赖 batch 统计量的算子都与之根本不兼容——这也是推理引擎里见不到 BN 的原因。

**一句话总结：BN 假设"跨样本的特征分布平稳"，这在自回归、变长、因果的语言模型里不成立；LN 把归一化收缩到单个 token 内部，换来了 batch 无关、训练推理一致、因果安全——代价是推理时一个无法折叠的 memory-bound 小算子，于是有了 RMSNorm 简化和 fused kernel 优化。**

## Q：Post-LN 和 Pre-LN 的区别是什么？

区别只有一个：**LayerNorm 放在残差相加的"外面"还是"里面"**。但这一位置之差，决定了梯度高速公路上有没有路障，进而决定了网络能堆多深、训练要不要小心翼翼。

### 1. 公式与结构

每个 sublayer（attention 或 MLP）各配一个 LN，两种放法：

- **Post-LN**（原始 Transformer 2017、BERT）：先相加，再归一化——LN 骑在主干上：

$$x_{l+1} = \text{LN}\big(x_l + F_l(x_l)\big)$$

- **Pre-LN**（GPT-2 起，GPT/LLaMA/Qwen 全系）：先归一化，再进分支——LN 藏在分支内部，主干是纯恒等：

$$x_{l+1} = x_l + F_l\big(\text{LN}(x_l)\big)$$

Pre-LN 网络末端还要补一个 **final norm**（LM head 之前），原因见第 3 节。

### 2. 梯度视角：高速公路上有没有路障

接上一篇残差笔记的推导，对 $x_l$ 求导：

- **Pre-LN**：$\frac{\partial x_{l+1}}{\partial x_l} = I + J_{F_l}J_{\text{LN}}$，连乘展开后仍有干净的 $I$ 项——loss 到任意浅层有一条**不经过任何权重和 LN** 的直通路径，梯度下界钉死。
- **Post-LN**：$\frac{\partial x_{l+1}}{\partial x_l} = J_{\text{LN}}\,(I + J_{F_l})$，于是

$$\frac{\partial L}{\partial x_l} = \frac{\partial L}{\partial x_N}\prod_{i=l}^{N-1} J_{\text{LN}_i}(I + J_{F_i})$$

**每一层都横着一个 LN 的雅可比**。LN 不是恒等：它投影掉均值/尺度方向、再按 $1/\sigma$ 缩放，奇异值偏离 1。100 个这样的矩阵连乘，又回到了"增益必须精确控制在 1 附近"的老问题——高速公路被切成了 N 段收费站。

Xiong et al. 2020（*On Layer Normalization in the Transformer Architecture*）的理论分析：Post-LN 在初始化时**靠近输出的层梯度异常大**，一步大学习率就能把网络打飞，所以必须 warmup（先用极小学习率让 LN 统计量稳定下来）；Pre-LN 各层梯度天然温和，warmup 可以很短甚至去掉，深层照样稳。

### 3. 前向视角：各自的代价

天下没有免费的午餐，Pre-LN 的稳定性是用别的东西换的：

- **Post-LN**：每层输出都被重新归一化，残差流幅度始终受控；训练调好之后，同等层数下最终效果 often 略好（机器翻译界长期有这个观察）。代价是**难训**：深了必炸，warmup、学习率、初始化一个都不能马虎。
- **Pre-LN**：分支输出不断往主干上加，残差流方差随深度近似线性增长（$\text{Var}(x_l)\approx l\cdot v$）。而分支内部先过 LN，输出幅度基本恒定——于是**越深的分支，相对主干的贡献越小**（$\sim 1/\sqrt{l}$），深层块趋近恒等映射。这呼应 Veit 的"浅层集成"视角：Pre-LN 稳是稳，但**有效深度打了折**。另外末端激活幅度随深度涨，所以必须加 final norm 收口。

**折中方案 DeepNorm**（GLM-130B 采用）：$x_{l+1} = \text{LN}(\alpha x_l + F_l(x_l))$，主干乘 $\alpha>1$、分支初始化按 $\beta<1$ 缩小，理论上把每层更新幅度钉住——兼具 Post-LN 的"每层都被认真使用"和 Pre-LN 的稳定，论文里训到了 1000 层。但工业界主流仍是 Pre-LN + RMSNorm：简单、皮实、够用。

### 4. 现状一览

| 模型 | 方案 |
|---|---|
| 原始 Transformer / BERT | Post-LN |
| GPT-2/3、LLaMA、Qwen、Mistral | Pre-LN（现代版为 Pre-RMSNorm）+ final norm |
| GLM-130B | DeepNorm |

### 联系推理方向

- **kernel 融合形态由 LN 位置决定**：Pre-LN 里"上一层分支输出 + 残差相加"和"下一分支输入的 RMSNorm"天然相邻，vLLM 的 `fused_add_rms_norm(hidden_states, residual)` 一个 kernel 同时产出**新残差**（未归一化，继续流）和**归一化后的分支输入**——残差流全程保持纯累加，不被 norm 污染。Post-LN 的"add 后 norm"也能融合，但残差本身被归一化了，语义不同。
- **数值精度**：Pre-LN 残差流幅度随深度增长，fp16（最大值 65504）下深层有溢出风险，这是大模型推理偏爱 **bf16**（指数位与 fp32 相同，动态范围大）的原因之一；final norm 负责在进 LM head 前把尺度收回来。
- 两种方案的 norm 算子数量相同，推理 FLOPs 几乎无差——**区别在训练动力学，不在推理成本**。

**一句话总结：Post-LN 把 LN 骑在残差主干上，每层都重新收口幅度，但梯度连乘里塞进 N 个 LN 雅可比，深了难训、必须 warmup；Pre-LN 把 LN 藏进分支，主干纯恒等、梯度有直通下界，随便堆深，代价是残差流方差随深度膨胀、深层贡献衰减，需要 final norm 收口——现代 LLM 全选后者。**

## Q：什么是教师强制（Teacher Forcing）？

### 1. 定义

训练自回归模型时，每一步的输入用**真实的前缀**（ground truth），而不是模型自己上一步的预测：

$$\mathcal{L} = -\sum_{t=1}^{T} \log p_\theta(x_t \mid x_1, \dots, x_{t-1})$$

条件里的 $x_{<t}$ 全部来自训练数据——哪怕模型在位置 $t-1$ 预测错了，位置 $t$ 的输入依然是正确的 $x_{t-1}$。"教师"（数据）每一步都强行把学生拽回正确轨道。实现上就是 **shift by one**：输入 `x[0:T-1]`，标签 `x[1:T]`。

### 2. 为什么必须这么训：并行性

对比另一种训法——**free-running**（自回归展开）：把模型自己的输出喂回输入。

| | Teacher Forcing | Free-running |
|---|---|---|
| 一条长度 T 的序列 | **1 次前向**，causal mask 保证每个位置只看见自己的前缀，T 个预测任务同时算 | T 次串行前向，无法并行 |
| 梯度 | 干净地流过 T 个并行的交叉熵 | 要穿过采样（不可导）或 T 步展开图 |
| 错误 | 每步独立，互不污染 | 一步错、步步错，训练信号被自己的噪声淹没 |

**Teacher forcing + causal mask = 把 T 步串行生成变成 1 次并行矩阵运算**。这是 Transformer 训练效率的根基，没有它就没有"用万亿 token 训模型"这回事。

### 3. 代价：Exposure Bias（暴露偏差）

训练时模型永远见到正确前缀，推理时却只能见到**自己生成的、可能带错的前缀**——训练/推理分布不一致，错误会复利式累积。缓解手段：scheduled sampling（Bengio et al. 2015，训练中以一定概率喂自己的预测）、序列级 RL 训练等。实践中规模和数据量上去后这个问题相当温和，RLHF/RLVR 阶段部分地在"自己的输出分布"上训练，也算一种补救。

### 联系推理方向

**训练 ≈ 对整条真实序列做一次 prefill**（并行、compute-bound）；**推理 decode = free-running**（串行、每步一个 token、memory-bound）。推理时没有教师可强制，这个不对称正是全部推理优化工作的根源：KV cache（缓存过去避免重算）、speculative decoding（用小模型草稿并行验证多个 token，把 decode 往 prefill 的形态上掰）、continuous batching 等，都是在弥补"推理无法 teacher forcing"的代价。

**一句话总结：教师强制 = 训练时每步喂真实前缀而非自己的预测，配合 causal mask 把 T 步生成压成一次并行前向；代价是 exposure bias，而推理端没有教师，于是有了 KV cache 和投机解码这一整套优化。**

## Q：三种架构中，为什么仅解码器（Decoder-only）胜出？

先摆清三个候选：

| 架构 | 代表 | 注意力 | 预训练目标 | 擅长 |
|---|---|---|---|---|
| Encoder-only | BERT | 双向 | MLM（完形填空） | 理解：分类、检索、抽取 |
| Encoder-Decoder | T5、BART、原始 Transformer | 编码器双向 + 解码器因果 + cross-attn | span corruption / seq2seq | 输入→输出边界清晰的任务 |
| Decoder-only | GPT 系、LLaMA、Qwen | 纯因果 | next-token prediction | 一切皆续写 |

### 1. 任务接口的统一性：一切皆续写

Decoder-only 只有一个接口：**给前缀，续写**。分类、翻译、问答、写代码、多轮对话、agent 轨迹——全部能表述成"文本续写"，不需要任务专用 head，不需要预先划定"哪段是输入、哪段是输出"。

- Encoder-only 天生不能生成，每个下游任务要接 head 微调；
- Encoder-decoder 要求输入/输出边界清晰，翻译很合适，但开放式对话、续写、agent 场景里这个边界根本不存在；
- **In-context learning 是决定性一击**：GPT-3 证明 few-shot 示例直接塞进前缀就行，"prompt 即前缀、答案即续写"与 decoder-only 的结构完全同构。指令微调和 ChatGPT 的多轮对话只是把这一范式产品化。

### 2. 训练信号密度与算力效率

- **每个 token 都是监督信号**：一条长度 T 的序列提供 T 个预测任务；MLM 只 mask ~15%，其余位置的算力花在"陪跑"上。
- **因果 mask 让注意力计算约减半**（下三角 vs 全矩阵）。
- 没有 cross-attention、没有两套栈，参数和 FLOPs 全部花在刀刃上。同等算力预算下，decoder-only 榨出的监督最多。

### 3. 简单性 → 可扩展性

一个栈、一个 loss、一种并行方式。Encoder-decoder 要处理两套栈的流水线依赖、cross-attn 的 KV、编码器/解码器不同的 batch 形态——在 100B+ 规模上，每一点结构复杂度都会被放大成工程灾难。**预训练 → SFT → RLHF 全流程共用同一结构**，数据管线和训练基建只需建一次。BigScience 的架构对比实验（Wang et al. 2022）也给出实证：经过多任务/指令式训练后，decoder-only + causal LM 的零样本泛化最好。

### 4. 推理生态的飞轮（联系推理方向）

因果性有一条极其值钱的性质：**新增 token 不改变过去任何位置的表示** → 过去的 K/V 永远有效 → **KV cache 成立**。

- 双向编码器加一个 token，所有位置的表示全变，增量缓存无从谈起；
- prefill/decode 分离、prefix caching、PagedAttention、continuous batching、投机解码——整个现代推理栈（vLLM/TensorRT-LLM）都建立在"单一因果栈 + KV cache"之上；
- GPT-3/ChatGPT 验证配方后，数据、人才、kernel 优化、serving 基建全部向 decoder-only 集中，飞轮自强化：结构越主流，优化越深，越主流。

### 5. 边界：胜出的是"通用生成式 LLM"这个赛道

- Encoder-decoder 在**边界固定的 seq2seq**（翻译、摘要）和中小规模上仍有竞争力（Flan-T5）；双向编码源文本理论上更充分。
- Encoder-only 至今统治 **embedding / reranker**（BGE 等检索模型仍是 BERT 系）——理解任务不需要生成，双向注意力反而是优势。

**一句话总结：decoder-only 用"一切皆续写"统一了任务接口（ICL/对话天然同构），每个 token 都产生监督、结构最简单最好扩展，而因果性带来的 KV cache 有效性又让它独占整个推理优化生态——任务通用性 × 训练效率 × 工程简单性 × 推理飞轮，四个因素叠加，另外两种架构输得心服口服。**

## Q：为什么 Q、K 算出的权重去乘 V，就能拿到上下文内容？

把问题拆成两半：**① 为什么 QK 的点积能表达"谁和谁相关"？② 为什么乘的是 V，"内容"就被搬过来了？** 答案的核心：attention 是一次**可微的软查字典**——Q/K 是寻址系统，V 才是被搬运的货。

### 1. 先看输出到底是什么：V 向量的凸组合

位置 $i$ 的输出：

$$o_i = \sum_j \alpha_{ij}\, v_j, \qquad \alpha_{ij} = \frac{\exp(q_i \cdot k_j / \sqrt{d})}{\sum_{j'} \exp(q_i \cdot k_{j'} / \sqrt{d})}$$

$\alpha_{ij} \ge 0$ 且对 $j$ 求和为 1——所以 $o_i$ 是**所有位置 V 向量的加权平均**。"拿到上下文"不是比喻：token $i$ 的新表示里，字面上混入了其他 token 的信息，权重由相关性决定。再经残差相加 $x_i \leftarrow x_i + o_i W_O$，这些外来信息就永久写进了 token $i$ 的残差流。

### 2. 三个投影 = 三种角色，这是全部关键

Q、K、V 是**同一个** $x$ 的三个**不同**线性投影：

$$q_i = x_i W_Q, \qquad k_j = x_j W_K, \qquad v_j = x_j W_V$$

- **Q（query）**：我在找什么信息？
- **K（key）**：我凭什么被检索到？（索引/标签）
- **V（value）**：如果我被选中，我实际交出什么内容？

类比图书馆：Q 是你的检索需求，K 是书脊上的标签，V 是书的内容。**索引不必等于内容**——K 和 V 解耦，让"凭什么被找到"和"找到后给什么"可以分别优化。如果只有一套投影（比如直接用 $x$ 自己点自己），"想找什么"和"能提供什么"就被绑死了，表达力大打折扣。

### 3. 为什么点积能表达"相关"：学出来的双线性形式

$$q_i \cdot k_j = x_i \, W_Q W_K^T \, x_j^T$$

这是一个**可学习的双线性相似度**。$W_Q W_K^T$ 不是人设计的，是梯度下降端到端学出来的：**只要"把 token $j$ 的 V 搬给 token $i$"能降低 loss，反传就会强化这种模式下 Q、K 的匹配度**。训练亿万次之后，网络学会了诸如"代词的 Q 去找先行词名词的 K""动词的 Q 去找主语的 K"这类检索规则。

具体例子：*The animal didn't cross the street because it was too tired.*

- `it` 的 Q 发出"找一个可指代的动物名词"的查询；
- `animal` 的 K 与之高度匹配，`street` 的 K 匹配度低 → $\alpha$ 集中在 animal 上；
- `animal` 的 V 携带其语义内容，加权求和后 `it` 的表示吸收了"animal"的信息 → 下一层/LM head 就能正确理解 it 指什么。

机制可解释性已经找到真实存在的这类回路：**induction head**（Olsson et al. 2022，"见过 A B … A，就预测 B"的两层注意力回路）就是"QK 寻址 + V 搬运"的最小实例。

### 4. 两个工程细节为什么长这样

- **除以 $\sqrt{d}$**：若 q、k 各分量近似独立、方差 1，点积方差为 $d$。$d$ 大时 logits 极端 → softmax 饱和到接近 one-hot → 梯度消失。缩放把方差拉回 1，保持 softmax 在"软"的区域。
- **softmax**：把分数变成概率分布 → 输出是凸组合（幅度不爆炸）、可微、且近似 winner-take-most 的稀疏检索。

### 5. 本质视角：权重由输入自己决定

MLP 的权重是**静态**的：不管输入什么，变换都一样。Attention 的"权重" $\alpha$ 是**从当前输入现算的**——输入自己决定信息如何路由。这正是"上下文相关"的来源：同一个词在不同句子里表示不同，因为每次的 $\alpha$ 都随上下文重算。Attention = **data-dependent 的动态连接**，V 是货，QK 是每单现算的物流路线。

### 联系推理方向

这套"查字典"结构直接决定了推理形态：

- **KV cache 缓存的就是本题的 K（索引）和 V（内容）**：因果性保证过去 token 的 K/V 不变，图书馆建一次就能反复查；Q 是当前 token 的查询，每步现算。
- **decode 为什么 memory-bound**：每步只有 1 个新 query，却要把整个图书馆（全部历史 KV）从 HBM 读一遍——算术强度极低。KV cache 是显存大头、带宽瓶颈，根源就在这。
- **MQA/GQA**：多个 Q head 共享同一组 K/V——查询可以有很多，图书馆只留一份（或几份），直接砍 KV cache 的显存和读带宽。角色分离（Q 易变、KV 可共享）正是它成立的前提。
- **FlashAttention**：$\alpha$ 矩阵只是瞬时路由，不需要物化 $T\times T$ 存下来——分块在线 softmax，算完即弃。

**一句话总结：Q/K/V 是同一表示的三个投影，分别扮演"找什么/凭什么被找到/交出什么"；QK 点积是端到端学出来的相似度，softmax 把它变成检索分布，乘 V 就是按相关度把别人的内容凸组合进自己的表示——寻址与内容解耦、权重由输入现算，这就是"上下文"的全部机制；而 K/V 作为可缓存的"图书馆"，正是 KV cache 与整个 decode 优化体系的物理基础。**

## Q：什么是旋转位置编码（RoPE）？为什么它能编码相对位置？

### 1. 背景：为什么需要位置编码

Attention 是**置换等变**的：把输入 token 打乱顺序，输出只是跟着打乱，内容完全不变——模型天生不知道词序。"猫追狗"和"狗追猫"在纯 attention 眼里一样，必须人为注入位置信息。三条路线：

| 路线 | 做法 | 代表 |
|---|---|---|
| 绝对位置编码 | 位置向量**加**到输入 embedding 上 | 原始 Transformer sinusoidal、GPT-2 learned |
| 相对位置偏置 | 在 attention 分数上**加**一个只依赖 $m-n$ 的偏置 | T5 bias、Transformer-XL |
| 旋转位置编码 | 用位置相关的旋转矩阵**乘** Q 和 K | RoPE（Su et al. 2021），LLaMA/Qwen/GPT-NeoX 全系 |

### 2. RoPE 的做法：用"旋转"携带位置

把每个 head 的 $q/k$ 向量（维度 $d$）拆成 $d/2$ 个二维子空间，第 $i$ 对在位置 $m$ 处旋转角度 $m\theta_i$：

$$
\begin{pmatrix} q'_{2i} \\ q'_{2i+1} \end{pmatrix} = \begin{pmatrix} \cos m\theta_i & -\sin m\theta_i \\ \sin m\theta_i & \cos m\theta_i \end{pmatrix} \begin{pmatrix} q_{2i} \\ q_{2i+1} \end{pmatrix}
$$

其中 $\theta_i = 10000^{-2i/d}$：低维对转得快（编码近距离），高维对转得慢（编码远距离）——和 sinusoidal 编码同一套频谱。

等价复数视角：把每对分量看作一个复数，旋转就是乘单位复数 $q'_i = q_i e^{im\theta_i}$。

三个关键性质：

- **只动 Q 和 K，不动 V**：位置只影响"谁和谁相关"（寻址），不污染被搬运的内容；
- **旋转是正交变换，不改变向量模长**：只改方向、不改幅度，语义能量不被位置缩放破坏；
- **零可学习参数**：纯函数式，任何位置现算。

### 3. 核心推导：为什么内积只剩相对位置

二维情形，记旋转矩阵为 $R(\alpha)$。位置 $m$ 的 query 和位置 $n$ 的 key 做内积：

$$
\begin{aligned}
\langle R(m\theta)q,\ R(n\theta)k \rangle &= q^T R(m\theta)^T R(n\theta)\, k \\
&= q^T R(-m\theta)\, R(n\theta)\, k \\
&= q^T R\big((n-m)\theta\big)\, k
\end{aligned}
$$

只用了旋转矩阵的两条性质：

1. $R(\alpha)^T = R(-\alpha)$（正交，转置 = 反向旋转）；
2. $R(\alpha)R(\beta) = R(\alpha+\beta)$（旋转可加，三角恒等式）。

**绝对位置 $m$、$n$ 在乘积中抵消，只剩差 $n-m$**。复数视角一行看穿：$q e^{im\theta}$ 与 $k e^{in\theta}$ 的内积含因子 $e^{i(m-n)\theta}$，只依赖差值。全维度是各二维对的块对角叠加，每对都只依赖 $m-n$，求和依然只依赖 $m-n$。

这就是 RoPE 的精髓：**用绝对位置的形式，实现相对位置的效果**——每个 token 只需知道自己的位置就能完成旋转（per-token 操作，可并行、可缓存），而任意两个 token 的注意力分数自动只取决于相对距离。对比：

- 加性绝对编码 $(x+p_m)$ 的内积展开出 $x^T p_n$、$p_m^T x$ 等交叉项，**单独依赖 $m$ 或 $n$**，相对性被破坏；
- T5 式相对偏置要为每对 $(m,n)$ 显式查表/计算偏置，RoPE 免费获得。

### 4. 附赠性质与外推问题

- **远程衰减**：内积是多个不同频率振荡项之和，$|m-n|$ 越大相位越分散、求和越趋向抵消——天然带"距离越远注意力越弱"的归纳偏置（论文给出随距离衰减的上界，非严格单调）。
- **外推是软肋**：频谱 $\theta_i$ 训练时固定，推理长度超过训练长度时，慢转的高维对会遇到**从未见过的角度**，效果崩坏。长上下文扩展的主流方案全在改频谱：
  - **PI（Position Interpolation）**：把位置线性压缩回训练范围内，全部频率一起"降速"；
  - **NTK-aware scaling**：改 base（$10000 \to$ 更大），高频几乎不动、低频多插值，保住局部分辨率；
  - **YaRN**：NTK-by-parts（按频段分治）+ attention 温度修正，LLaMA/Qwen 长上下文版的主流配方。

### 联系推理方向

- **RoPE 在写入 KV cache 之前施加**：cache 里存的是旋转后的 K。decode 时新 token 位置 $m$ 递增，只需按自己的绝对位置旋转一次，与所有缓存 K 的内积自动得到正确相对角度——**历史 KV 一个字节都不用动**。这是 RoPE 与 KV cache 完美兼容的原因（某些相对位置方案每步要重算偏置，做不到这点）。
- **kernel 形态**：rotary embedding 是逐元素的 cos/sin 乘加，纯访存小算子；cos/sin 表预计算缓存，vLLM 有专门的 `rotary_embedding` kernel，常与 QKV projection 融合或 in-place 执行。
- **部署坑**：长上下文模型 serving 时必须带上对应的 scaling 配置（YaRN/NTK 参数），否则超过原生长度后 perplexity 直接爆炸——推理引擎里这是常见事故点。

**一句话总结：RoPE 把 Q/K 的每对分量按"位置 × 频率"旋转，利用旋转矩阵"转置即反旋转、相乘即角相加"的性质，让 QK 内积中的绝对位置精确抵消、只剩相对差——以 per-token 的绝对操作实现了相对位置编码，不改模长、零参数、不动 V，且旋转后的 K 可直接进 KV cache 永不重算；代价是频谱固定导致外推差，于是有了 PI/NTK/YaRN 这一整条长上下文扩展技术线。**

## Q：为什么预测下一个词能学到知识？

直觉上的困惑：next-token prediction 看起来只是个"统计接龙"，怎么就学出了事实、推理、甚至世界模型？答案分四层：**目标浅、任务深；压缩即理解；知识有物理载体；以及这个目标的真实边界**。

### 1. 目标看起来浅，但"预测得准"这个要求无限深

关键换位：**文本不是随机符号串，它是世界运行过程投下的影子**。要把下一个词预测准，就必须建模"产生这段文本的那个世界"。看几个预测任务实际要求什么：

| 待预测的文本 | 想预测对，必须会什么 |
|---|---|
| "法国的首都是 ___" | 地理事实 |
| "37 × 24 = ___" | 执行乘法算法 |
| "奖杯放不进手提箱，因为它太 ___" | 物理常识 + 指代消解（Winograd 模式） |
| 侦探小说最后一句"凶手是 ___" | 追踪全书情节、动机、伏笔 |
| 一段代码的下一行 | 建模程序语义和数据流 |

梯度下降不在乎你"怎么"降 loss——**只要某种内部结构（事实表、算术回路、因果模型）能降低预测误差，它就会被学出来**。Ilya Sutskever 的表述：预测下一个 token 预测得足够好，就意味着理解了产生这个 token 的背后现实。

### 2. 信息论视角：压缩即理解

交叉熵损失有精确的信息论含义——**用模型给语料编码时的平均码长**：

$$\mathcal{L} = -\frac{1}{T}\sum_t \log p_\theta(x_t \mid x_{<t}) \quad \text{(nats/token)}$$

最小化 loss = 最优压缩这份语料。而 Shannon 告诉我们：最优码长由数据的真实分布决定，想逼近它，就必须捕获数据里**一切可预测的结构**——语法、语义、事实、逻辑、因果，一个都逃不掉。

再往深一层是 MDL / Solomonoff 归纳：**对数据最好的压缩，是找到生成它的最短程序**。语料万亿 token、参数相对有限，死记硬背的"描述长度"远高于学会规则——压缩压力天然偏向"学规律"而非"背答案"。这就是为什么一个看似简单的目标能逼出通用能力：**它是所有可计算任务的通用容器**（接上一篇 decoder-only 笔记：任何任务都能表述成续写，于是任何能降 loss 的能力都会被顺带学出来）。

### 3. 知识学在哪、怎么学出来：有实证

- **事实存在 MLP 里**：Geva et al. 2021 证明 FFN 层是 key-value 记忆——第一层权重是"模式检测器"（key），第二层是"输出分布"（value）。ROME/MEMIT 知识编辑正是直接改某层 MLP 权重就能改掉"埃菲尔铁塔在巴黎"这条事实。
- **算法是慢慢"顿悟"的**：grokking 现象——算术任务先死记硬背（训练 loss 降、泛化差），继续训很久后突然切换到真正的算法回路，泛化率跳变到接近 100%。压缩压力最终赢了记忆。
- **世界模型的真实证据**：Othello-GPT（Li et al. 2023）——只喂棋谱序列做 next-token 预测，探针发现内部涌现出**棋盘状态表示**；干预这个表示，模型的后续预测随之改变。模型为了预测落子，真的学会了"棋盘长什么样"，而不只是棋谱的 n-gram。

### 4. 边界：学到的是文本分布，不是真理

诚实地说，这个目标有三条结构性缺陷：

- **目标是"像人写的"，不是"是真的"**：模型优化的是 plausibility（可信度），不是 truth。幻觉不是 bug，是目标函数的自然产物——RLHF/RLVR 是在事后给"真"补奖励。
- **文本是世界的有损投影**：没人把"水往低处流"写一亿遍，隐性知识、物理直觉、具身经验在语料里极度稀疏——符号接地问题。模型的世界模型是"二手的"。
- **知识有保质期且难以定位**：参数化知识冻结在训练截止日，改一条事实要么重训要么做知识编辑。

"随机鹦鹉"之争的准确答案在中间：预测目标**确实**逼出了远超 n-gram 的内部结构（第 3 节的实证），但这个结构服务于"预测文本"，与"理解世界"之间隔着投影损失和目标错位。

### 联系推理方向

- **两种记忆对应两种推理资源**：参数化知识在权重里（"长期记忆"，读权重 = decode 的带宽大头），上下文知识在 KV cache 里（"工作记忆"）。RAG / 长上下文本质是**把知识从权重搬到激活**——绕开知识保质期和幻觉问题，代价是 KV cache 显存和 prefill 算力。
- **量化/剪枝会伤事实**：知识以分布式 key-value 形式存于 MLP，激进量化对长尾事实的损伤大于对"流畅度"的损伤——评测 perplexity 看不出知识丢失，要跑知识类 benchmark。
- **预训练给"直觉"，推理时计算给"深思"**：next-token 预训练学出的是单步直觉（System 1），o1/R1 式 RL + 长思维链是在推理时把计算展开成多步（System 2）——test-time scaling 这条线正是承认"单步预测学不尽推理"后的补丁。

**文本是世界投下的影子，next-token prediction 的 loss 就是压缩这份影子的码长——想把码长压到极限，就必须学会产生影子的那个世界的规律；压缩压力让"学规则"胜过"背答案"，事实落进 MLP 的 key-value、算法经 grokking 涌现、世界模型被 Othello-GPT 实证；但目标终究是"像人写的"而非"是真的"，幻觉与接地缺陷由此而来，RAG 和 test-time scaling 都是在给这个目标打补丁。**

## Q：训练算力公式 $C = 6ND$ 是怎么来的？

$N$ = 模型参数量（不含 embedding），$D$ = 训练 token 数，$C$ = 总 FLOPs。系数 6 不是拟合出来的经验数，是**数出来的**：前向 2 + 反向 4。

### 1. 前向：每个参数每个 token 用一次，$2N$

Transformer 的算力几乎全在线性层。一个矩阵乘 $y = xW$，$W \in \mathbb{R}^{m \times n}$ 有 $mn$ 个参数；对**每个 token**，每个参数参与一次乘法和一次加法：

$$\text{FLOPs}_{\text{forward}} = \underbrace{mn}_{\text{乘}} + \underbrace{mn}_{\text{加}} = 2mn = 2 \times \text{参数量}$$

所有线性层加起来：**每 token 前向 $\approx 2N$ FLOPs**。激活函数、norm、softmax 都是 $O(d)$ 的逐元素操作，对比矩阵乘的 $O(d^2)$ 可忽略。

### 2. 反向：一个矩阵乘变两个，$4N$

设上游梯度 $g = \partial L / \partial y$，反向要算**两个**同样规模的矩阵乘：

$$\frac{\partial L}{\partial x} = g W^T \quad (2mn \text{ FLOPs，传给前面的层})$$

$$\frac{\partial L}{\partial W} = x^T g \quad (2mn \text{ FLOPs，交给优化器更新权重})$$

每个参数对应 $2 + 2 = 4$ FLOPs：**每 token 反向 $\approx 4N$**。反向恰好是前向的 2 倍，不是巧合——链式法则对矩阵乘的两个操作数各求一次导，各是一个同尺寸 matmul。

### 3. 合计

$$C = \underbrace{2N}_{\text{前向}} + \underbrace{4N}_{\text{反向}} \ \text{每 token} \quad \Longrightarrow \quad C = 6ND$$

### 4. 这个公式忽略了什么（修正项）

- **Attention 的序列长度项**：$QK^T$ 和 $\alpha V$ 的算力依赖 $T$ 而不含参数，不在 $N$ 里。每层每 token 前向约 $4Td_{\text{model}}$ FLOPs；而每层参数约 $12d_{\text{model}}^2$（QKV+O 共 $4d^2$，MLP 共 $8d^2$），相对修正 $\approx T / (6d_{\text{model}})$。$T=4\text{k}, d=8\text{k}$ 时约 8%，可忽略；**长上下文 $T=128\text{k}$ 时 attention 反超，6ND 严重低估**。
- **Embedding / LM head**：Kaplan 惯例不计入 $N$；词表很大时（LLaMA-3 的 128k）输出投影每 token $2Vd$ FLOPs，不可忽略。
- **激活重计算（checkpointing）**：省显存换算力，反向时重跑一遍前向 → 系数变 **8**。
- **MoE**：算力只由**激活参数**决定，$C \approx 6N_{\text{active}}D$；总参数决定的是显存，不是 FLOPs。
- **计数惯例**：一次乘加算 1 FLOP（MAC 惯例）则公式是 $3ND$；业界统一按 2 计，看到 3 别慌。

### 5. 它有什么用

- **Scaling laws 的换算桥梁**：Kaplan / Chinchilla 把算力预算 $C$ 换成 $(N, D)$ 组合。Chinchilla 结论：计算最优时 $N \propto C^{0.5}$、$D \propto C^{0.5}$，约 **20 token/参数**——给定 $C=6ND$ 才能解出这个分配。
- **MFU 的定义**：$\text{MFU} = 6ND \,/\, (\text{GPU 峰值 FLOPS} \times \text{时间} \times \text{卡数})$，衡量训练把硬件用得多满。
- **预算估算**：LLaMA-7B 训 1T token：$6 \times 7\times10^9 \times 10^{12} = 4.2\times10^{22}$ FLOPs。A100 bf16 峰值 312 TFLOPS、按 50% MFU 算，约 **3100 A100·天**（千卡集群 3 天量级）。

### 联系推理方向

- **推理只有前向：每 token $\approx 2N$ FLOPs**，没有那个 4。prefill 一次算整段，$2NT$ FLOPs 摊在大量 token 上，compute-bound；decode 每步只算 1 个 token 的 $2N$ FLOPs，却要把 $2N$ 字节（bf16 权重）从 HBM 读一遍——**算术强度 $\approx 1$ FLOP/byte**，远低于 A100 的 ridge point（$\approx 150$），这就是 decode memory-bound 的定量根源。
- 所以 decode 阶段看 MFU 没意义（必然极低），要看 **MBU**（带宽利用率）；continuous batching 的本质是把 batch 内多个 token 的 $2N$ 计算摊到同一次权重读取上，算术强度随 batch 线性涨。
- MoE 的推理优势同一公式：读进显存的是总参数，但每 token 只算 $2N_{\text{active}}$——不过 decode 时专家权重的读取并不随激活比例减少，带宽收益要看 batch 和专家命中率。

**系数 6 = 前向 2（每参数一次乘加）+ 反向 4（对输入和权重各一个同尺寸 matmul），逐 token 数 FLOPs 数出来的；attention 长度项、重计算、MoE、词表投影是四大修正项；它既是 scaling law 和 MFU 的地基，也反衬出推理端"只有 2N、且被带宽卡死"的 decode 本质。**
