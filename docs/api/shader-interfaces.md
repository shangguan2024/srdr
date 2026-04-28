# 着色器接口 API

## 着色器类型别名

### 头文件

```cpp
#include "VertexShader.hpp"    // VertexShaderProgram
#include "FragmentShader.hpp"  // FragmentShaderProgram
```

### 定义

```cpp
using VertexShaderProgram = std::function<VertexOutput(VertexInput)>;
using FragmentShaderProgram = std::function<FragmentOutput(FragmentInput)>;
```

通过 `std::function` 实现可编程着色器。用户以 lambda 表达式或函数对象的形式注入自定义着色器逻辑。

---

## 顶点数据结构

### 头文件

```cpp
#include "Vertex.hpp"
```

### Vertex (用户级顶点)

在应用程序中定义顶点数据时使用的结构。

| 字段 | 类型 | 描述 |
| --- | --- | --- |
| `position` | `Vec3` | 顶点位置 (模型空间或世界空间) |
| `normal` | `Vec3` | 顶点法线 |
| `color` | `Color` | 顶点颜色 (RGBA) |
| `uv` | `Vec2` | 纹理坐标 (当前未使用) |

### VertexInput (顶点着色器输入)

顶点加载阶段从顶点缓冲区组装后传递给顶点着色器的数据。

| 字段 | 类型 | 描述 |
| --- | --- | --- |
| `a_position` | `Vec3` | 顶点位置 |
| `a_normal` | `Vec3` | 顶点法线 |
| `a_color` | `Color` | 顶点颜色 |
| `a_uv` | `Vec2` | 纹理坐标 |

### VertexOutput (顶点着色器输出)

顶点着色器的输出，经过光栅化插值后传递给片元着色器。

| 字段 | 类型 | 描述 |
| --- | --- | --- |
| `v_position` | `Vec4` | 裁剪坐标系位置 |
| `v_normal` | `Vec3` | 法线 (经插值) |
| `v_color` | `Color` | 颜色 (经插值) |
| `v_uv` | `Vec2` | 纹理坐标 (经插值) |
| `v_world_position` | `Vec4` | 世界空间位置 (经插值) |

### ClipVertex

```cpp
using ClipVertex = VertexOutput;
```

裁剪阶段使用的顶点类型，与 `VertexOutput` 一致。

### ScreenVertex

图元组装阶段经透视除法和视口变换后的屏幕空间顶点。

| 字段 | 类型 | 描述 |
| --- | --- | --- |
| `position` | `Vec3` | 屏幕坐标 (x, y, z) |
| `inv_w` | `float` | 1/w，用于透视校正插值 |
| `v_normal` | `Vec3` | 法线 |
| `v_color` | `Color` | 颜色 |
| `v_uv` | `Vec2` | 纹理坐标 |
| `v_world_position` | `Vec4` | 世界空间位置 |

---

## 片元数据结构

### 头文件

```cpp
#include "Fragment.hpp"
```

### FragmentInput (片元着色器输入)

光栅化阶段生成的片元数据，包含经透视校正插值后的顶点属性。

| 字段 | 类型 | 描述 |
| --- | --- | --- |
| `f_position` | `Vec4` | 片元位置 (裁剪坐标) |
| `v_normal` | `Vec3` | 插值后的法线 |
| `v_color` | `Color` | 插值后的颜色 |
| `v_uv` | `Vec2` | 插值后的纹理坐标 |
| `v_world_position` | `Vec4` | 插值后的世界空间位置 |

### FragmentOutput (片元着色器输出)

片元着色器的计算结果，传递给输出合并阶段。

| 字段 | 类型 | 描述 |
| --- | --- | --- |
| `o_position` | `Vec3` | 片元位置 |
| `o_color` | `Color` | 片元最终颜色 |

---

## 图元数据结构

### 头文件

```cpp
#include "Primitive.hpp"
```

### Primitive

光栅化阶段的内部图元表示，包含三个屏幕空间顶点及其用于插值的平面方程。

| 字段 | 类型 | 描述 |
| --- | --- | --- |
| `vertices` | `std::array<ScreenVertex, 3>` | 三个屏幕空间顶点 |
| `aabb` | `AABB<int, 2>` | 图元的轴对齐包围盒 |
| `area` | `float` | 三角形面积 (用于重心坐标计算) |
| `edges` | `std::array<EdgeEquation, 3>` | 三条边的直线方程 |
| `depth_plane` | `PlaneEquation` | 深度插值平面 |
| `inv_w_plane` | `PlaneEquation` | 1/w 插值平面 |
| `rgba_plane` | `std::array<PlaneEquation, 4>` | RGBA 颜色分量插值平面 |
| `normal_plane` | `std::array<PlaneEquation, 3>` | 法线 XYZ 插值平面 |
| `uv_plane` | `std::array<PlaneEquation, 2>` | UV 插值平面 |
| `world_pos_plane` | `std::array<PlaneEquation, 4>` | 世界坐标 XYZW 插值平面 |

### EdgeEquation

继承自 `PlaneEquation`，表示三角形边的直线方程，用于判断片元是否在三角形内部。

---

## 颜色附件与深度附件

### 头文件

```cpp
#include "ColorAttachment.hpp"
#include "DepthAttachment.hpp"
```

### ColorAttachment

管理颜色缓冲区，存储 `uint32_t` 格式的像素数据 (0xAARRGGBB)。

| 方法 | 描述 |
| --- | --- |
| `ColorAttachment(int width, int height)` | 构造指定尺寸的颜色附件 |
| `write(int x, int y, uint32_t color)` | 写入像素 |
| `read(int x, int y) const` | 读取像素 |
| `getData()` | 获取原始像素数据指针 |
| `clear()` | 清空为黑色 |

### DepthAttachment

管理深度缓冲区，存储 `float` 格式的深度值。

| 方法 | 描述 |
| --- | --- |
| `DepthAttachment(int width, int height)` | 构造指定尺寸的深度附件 |
| `write(int x, int y, float depth)` | 写入深度值 |
| `test(int x, int y, float depth) const` | 测试深度值 (depth < 已存储值 返回 true) |
| `testAndWrite(int x, int y, float depth)` | 测试并写入 |
| `getData()` | 获取原始深度数据指针 |
| `clear()` | 清空为 1.0f (远平面) |
