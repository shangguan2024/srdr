# DrawTriangle 示例

## 概述

DrawTriangle 是 SRDR 渲染管线的最小可用示例，演示如何定义顶点数据、提交绘制调用并完成一个完整的渲染帧。该示例绘制一个红绿蓝三色三角形，验证顶点加载、图元组装、光栅化、片元着色、输出合并等管线阶段的正确性。

## 运行效果

![DrawTriangle 示例](../../assets/examples/triangle.png)

运行后将显示一个 `800x600` 的窗口，窗口中心呈现一个彩色三角形，三个顶点分别为红、绿、蓝。

## 核心流程

```plaintext
[创建窗口] -> [创建渲染器] -> [定义顶点] -> [循环: beginScene -> draw -> endScene]
```

### 1. 创建渲染器

将窗口实例传递给 `Renderer` 构造函数，渲染器内部自动初始化管线各阶段对象：

```cpp
WindowFactory wf;
auto window = wf.createWindow();
window->create(800, 600, "Triangle");

Renderer device(window);
```

`Renderer` 构造函数中会调用 `init()`，依次创建以下管线阶段对象：

1. `VertexLoader` -- 从顶点/索引缓冲区提取顶点输入
2. `VertexShader` -- 执行顶点着色程序
3. `PrimitiveAssembler` -- 执行裁剪、透视除法和视口变换
4. `Rasterizer` -- 将图元转换为片元
5. `FragmentShader` -- 执行片元着色程序
6. `OutputMerger` -- 执行深度测试/混合并写入帧缓冲区

同时创建与窗口尺寸一致的 `FrameBuffer`。

### 2. 定义顶点数据

```cpp
std::vector<Vertex> tri(3);
std::vector<std::size_t> ind{ 0, 1, 2 };
tri[0].color = Color(1, 0, 0);   // 红色
tri[1].color = Color(0, 1, 0);   // 绿色
tri[2].color = Color(0, 0, 1);   // 蓝色
tri[0].position = { 0, 0, 0 };
tri[1].position = { 1, 1, 0 };
tri[2].position = { 0, 1, 0 };
```

`Vertex` 结构包含位置 (`position`)、法线 (`normal`)、颜色 (`color`)、纹理坐标 (`uv`) 四个属性。此处仅设置位置和颜色，法线和纹理坐标保持默认值。

顶点坐标定义在三维标准化空间中，渲染器内部通过默认顶点着色器直接传递这些坐标，再经由视口变换映射到屏幕像素坐标。

### 3. 渲染循环

```cpp
while (window->isRunning()) {
    device.beginScene();
    device.draw(tri, ind);
    device.endScene();
    std::this_thread::sleep_for(std::chrono::milliseconds(16));
}
```

每帧执行以下步骤：

1. `beginScene()` -- 清空所有内部缓存 (顶点缓冲、索引缓冲、各阶段输入输出缓存)
2. `draw()` -- 将顶点数据追加到内部顶点/索引缓冲区
3. `endScene()` -- 触发完整的管线执行 (`render()` 方法)

### 4. 管线执行

`render()` 方法按顺序执行管线各阶段：

```plaintext
VertexLoader::loadVertex      -- 根据索引组装 VertexInput
VertexShader::processVertices -- 执行顶点着色 (默认: 透传)
PrimitiveAssembler::assemblePrimitives -- 裁剪 + 视口变换
Rasterizer::rasterizePrimitives -- 光栅化生成片元
FragmentShader::processFragments -- 执行片元着色 (默认: 透传颜色)
OutputMerger::mergeOutputs   -- 写入帧缓冲区
```

## 关键技术要点

| 要点 | 说明 |
| --- | --- |
| 默认着色器 | 未设置自定义着色器时，使用默认透传着色器，不对顶点/片元数据做任何变换 |
| 坐标系 | 顶点坐标在标准化设备坐标系 (NDC) 中定义，范围 [-1, 1] |
| 图元类型 | 当前仅支持三角形图元，索引数组每 3 个元素构成一个三角形 |
| 帧同步 | 固定 16ms 延迟实现约 60 FPS 刷新率 |
