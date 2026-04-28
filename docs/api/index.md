# API 文档

## 命名空间

所有公共接口位于 `srdr` 命名空间下。`srdr::transform` 命名空间包含空间变换函数。

## 模块概览

| 模块 | 库目标 | 头文件目录 | 文档 |
| --- | --- | --- | --- |
| core | `srdr_core` | `src/core/` | [math.md](math.md) |
| platform | `srdr_platform` | `src/platform/` | [platform.md](platform.md) |
| renderer | `srdr_renderer` | `src/renderer/` | [renderer.md](renderer.md), [shader-interfaces.md](shader-interfaces.md), [scene.md](scene.md) |

## 模块依赖关系

```plaintext
application (srdr)
  |
  +-- renderer (srdr_renderer)
  |     |
  |     +-- core (srdr_core)
  |     +-- platform (srdr_platform)
  |
  +-- platform (srdr_platform)
  |     |
  |     +-- core (srdr_core)
  |
  +-- core (srdr_core)        (无外部依赖)
```

## 快速索引

| 类型/接口 | 所属模块 | 简要描述 |
| --- | --- | --- |
| `Renderer` | renderer | 渲染管线主控类 |
| `State` | renderer | 渲染状态枚举 (DEPTH_TEST, BLEND) |
| `VertexShaderProgram` | renderer | 顶点着色器类型别名 |
| `FragmentShaderProgram` | renderer | 片元着色器类型别名 |
| `Camera` | renderer/scene | 相机，封装视图与投影矩阵 |
| `DirectionalLight` | renderer/scene | 方向光数据结构 |
| `PointLight` | renderer/scene | 点光源数据结构 |
| `IWindow` | platform | 平台窗口抽象接口 |
| `WindowFactory` | platform | 窗口工厂类 |
| `Vec2`/`Vec3`/`Vec4` | core | 单精度浮点向量 |
| `Mat3`/`Mat4` | core | 单精度浮点矩阵 |
| `Color` | core | RGBA 颜色类型 |
| `transform::perspective` | core | 透视投影矩阵生成 |
| `transform::lookAt` | core | 视图矩阵生成 |
