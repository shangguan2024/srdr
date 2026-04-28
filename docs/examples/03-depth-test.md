# DepthTest 示例

## 概述

DepthTest 示例演示深度测试 (Depth Test) 功能。当两个三角形在空间中出现重叠时，深度测试决定哪个片元最终显示在屏幕上。不启用深度测试时，后绘制的三角形会覆盖先绘制的三角形，导致错误的遮挡效果。启用深度测试后，片元的深度值与深度缓冲区中已存储的值进行比较，仅当新片元更接近相机时才更新颜色。

## 运行效果

![DepthTest 示例](../../assets/examples/depth_test.png)

示例绘制两个三角形，它们具有不同的深度值 (Z 坐标)，在投影空间中产生前后遮挡关系。红色/绿色/蓝色三角形位于 Z=0.3，黄色/青色/品红色三角形位于 Z=0.5 和 Z=0。由于深度测试启用，片元根据正确的深度关系决定可见性。

## 核心流程

### 1. 启用深度测试

```cpp
Renderer device(window);
device.enable(State::DEPTH_TEST);
```

`enable(State::DEPTH_TEST)` 通知 `OutputMerger` 在合并片元输出时执行深度测试。底层调用 `m_output_merger->enableDepthTest()`，该操作设置内部标志位 `m_depth_enabled = true`。

可使用 `disable(State::DEPTH_TEST)` 在运行时关闭深度测试。

### 2. 定义深度交错的顶点数据

```cpp
std::vector<Vertex> tris(6);
std::vector<std::size_t> ind{ 0, 1, 2, 3, 4, 5 };

// 三角形 1: Z = 0.3 (在另外两个三角形之间)
tris[0].position = { -0.3, -0.3, 0.3 };
tris[1].position = { 0.7, -0.3, 0.3 };
tris[2].position = { -0.3, 0.7, 0.3 };

// 三角形 2: Z = 0 和 Z = 0.5 (部分在前，部分在后)
tris[3].position = { 0.6, 0.6, 0 };
tris[4].position = { 0.3, -0.8, 0.5 };
tris[5].position = { -0.8, 0.3, 0.5 };
```

深度值 Z 的范围与 NDC 空间中的 Z 范围一致。在默认透传顶点着色器下，Z 值被直接传递到管线中。

### 3. 渲染循环

```cpp
while (window->isRunning()) {
    device.beginScene();
    device.draw(tris, ind);
    device.endScene();
    std::this_thread::sleep_for(std::chrono::milliseconds(16));
}
```

## 深度测试实现原理

SRDR 中的深度测试在 `OutputMerger` 阶段实现，核心逻辑如下：

### 深度缓冲区

`DepthAttachment` 类维护一个 `std::vector<float>` 数组，尺寸与窗口分辨率一致。每个像素位置存储一个浮点数表示的深度值。

```cpp
class DepthAttachment {
public:
    void write(int x, int y, float depth);
    bool test(int x, int y, float depth) const;
    bool testAndWrite(int x, int y, float depth);
    void clear();
};
```

- `clear()` -- 将所有深度值重置为 `1.0f` (远平面)
- `test(x, y, depth)` -- 比较 `depth < m_depths[y * width + x]`，更小的深度值表示更接近相机
- `testAndWrite(x, y, depth)` -- 先测试，通过后写入

### 输出合并阶段

`OutputMerger::mergeOutputs` 遍历所有片元输出，对每个片元：

```plaintext
if (depth_test_enabled) {
    if (!frame_buffer->testDepth(x, y, fragment_depth)) {
        discard fragment;  // 片元被深度值更大的已存片元遮挡
    }
    frame_buffer->writeDepth(x, y, fragment_depth);
}
frame_buffer->writeColor(0, x, y, fragment_color);
```

## 关键技术要点

| 要点 | 说明 |
| --- | --- |
| 深度比较 | 使用 Less 模式：新片元深度值小于已存储深度值时通过测试 |
| 初始化值 | 深度缓冲区初始化为 `1.0f` (远平面深度) |
| 精度 | 使用 `float` 单精度浮点数存储 |
| 清空时机 | `clearFrameBuffer()` 清空深度缓冲区，建议在 `beginScene` 前调用 |
