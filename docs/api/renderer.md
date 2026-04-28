# 渲染器 API

## Renderer

渲染管线的主控类。管理所有管线阶段对象、帧缓冲、顶点/索引缓冲区，协调各阶段执行。

### 头文件

```cpp
#include "Renderer.hpp"
```

### 构造与窗口绑定

```cpp
explicit Renderer(std::shared_ptr<IWindow> window);
```

构造时自动调用 `init()`，创建管线各阶段对象和与窗口尺寸匹配的帧缓冲。

### 状态控制

```cpp
void enable(State state);
void disable(State state);
```

| 参数 | 说明 |
| --- | --- |
| `State::DEPTH_TEST` | 启用/禁用深度测试 |
| `State::BLEND` | 启用/禁用 Alpha 混合 |

### 着色器注入

```cpp
void setVertexShader(VertexShaderProgram vs);
void resetVertexShader();

void setFragmentShader(FragmentShaderProgram fs);
void resetFragmentShader();
```

- `setVertexShader` -- 注入自定义顶点着色器，覆盖默认透传着色器
- `resetVertexShader` -- 恢复默认顶点着色器
- `setFragmentShader` -- 注入自定义片元着色器，覆盖默认透传着色器
- `resetFragmentShader` -- 恢复默认片元着色器

### 帧生命周期

```cpp
void beginScene();
void endScene();
void clearFrameBuffer();
```

| 方法 | 行为 |
| --- | --- |
| `beginScene()` | 清空顶点缓冲区、索引缓冲区及各阶段输入输出缓存 |
| `endScene()` | 调用 `render()` 执行完整管线，输出到窗口 |
| `clearFrameBuffer()` | 清空颜色附件和深度附件 |

### 绘制调用

```cpp
void draw(const std::vector<Vertex>& vertices, const std::vector<std::size_t>& indices);
```

将顶点数据追加到内部顶点/索引缓冲区。每 3 个索引构成一个三角形图元。

---

## State

```cpp
enum class State : std::uint8_t {
    UNKNOWN,
    DEPTH_TEST,  // 深度测试
    BLEND,       // Alpha 混合
    STATE_COUNT,
};
```

---

## OutputMerger

输出合并阶段，负责深度测试与 Alpha 混合。

### 头文件

```cpp
#include "OutputMerger.hpp"
```

### 公共接口

| 方法 | 描述 |
| --- | --- |
| `enableDepthTest()` | 启用逐片元深度测试 |
| `disableDepthTest()` | 关闭深度测试 |
| `enableBlend()` | 启用 Alpha 混合 |
| `disableBlend()` | 关闭 Alpha 混合 |
| `setBlendFunction(BlendFunction)` | 设置自定义混合函数 |
| `resetBlendFunction()` | 恢复默认 Alpha 混合函数 |

默认 Alpha 混合公式：

```plaintext
output_color = src_color * src_alpha + dst_color * (1 - src_alpha)
```

自定义混合函数签名：

```cpp
using BlendFunction = std::function<Color(const Color& src, const Color& dst)>;
```

---

## FrameBuffer

帧缓冲，管理颜色附件与深度附件。

### 头文件

```cpp
#include "FrameBuffer.hpp"
```

### 构造

```cpp
FrameBuffer(int width, int height, int colorAttachmentCount = 1, bool hasDepth = true);
```

### 公共方法

| 方法 | 描述 |
| --- | --- |
| `enableDepth()` | 启用深度附件 |
| `writeColor(int index, int x, int y, const Color&)` | 写入颜色附件 |
| `writeColor(int index, int x, int y, uint32_t)` | 以 uint32 格式写入颜色 |
| `writeDepth(int x, int y, float)` | 写入深度值 |
| `testDepth(int x, int y, float)` | 测试深度值 (less 模式) |
| `testAndWriteDepth(int x, int y, float)` | 测试并写入深度值 |
| `getColor(int index, int x, int y)` | 读取颜色值 |
| `getDepth(int x, int y)` | 读取深度值 |
| `clearColor(int index)` | 清空指定颜色附件 |
| `clearColor()` | 清空所有颜色附件 |
| `clearDepth()` | 清空深度附件 |
| `getColorAttachmentData(int index)` | 获取颜色附件原始像素数据 |

---

## 内部管线阶段类

以下类由 `Renderer` 内部自动管理，通常无需直接使用。

| 类 | 头文件 | 功能 |
| --- | --- | --- |
| `VertexLoader` | `VertexLoader.hpp` | 根据索引从顶点缓冲区组装 `VertexInput` |
| `VertexShader` | `VertexShader.hpp` | 执行顶点着色器程序 |
| `PrimitiveAssembler` | `PrimitiveAssembler.hpp` | 裁剪、透视除法、视口变换 |
| `Rasterizer` | `Rasterizer.hpp` | 将图元光栅化为片元 |
| `FragmentShader` | `FragmentShader.hpp` | 执行片元着色器程序 |
| `OutputMerger` | `OutputMerger.hpp` | 深度测试、混合、帧缓冲写入 |
