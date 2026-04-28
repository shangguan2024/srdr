# SRDR - Soft Renderer

SRDR (Soft Renderer) 是一个基于 CPU 软件光栅化实现的 3D 图形渲染器，使用 C++20 标准编写，无第三方依赖。项目通过 `IWindow` 接口抽象窗口系统，Windows 下基于 Win32 GDI 实现窗口像素显示，该接口可扩展至其他平台。项目以学习为目的，完整实现了现代图形管线的主要阶段，适用于学习渲染管线原理和计算机图形学基础。

## 功能特性

- **可编程着色器管线**：支持用户自定义顶点着色器 (`VertexShaderProgram`) 和片元着色器 (`FragmentShaderProgram`)，以 `std::function` 形式注入渲染管线。
- **完整渲染管线**：实现了顶点加载 (Vertex Loading)、顶点着色 (Vertex Shading)、图元组装 (Primitive Assembling)、光栅化 (Rasterization)、片元着色 (Fragment Shading)、输出合并 (Output Merging) 等完整阶段。
- **深度测试**：支持基于逐片元的深度测试 (Depth Test)，可启用或关闭。
- **Alpha 混合**：支持透明片元的 Alpha 混合 (Blend)，可启用或关闭。
- **透视投影**：内建透视投影矩阵与视图矩阵生成，支持 `Camera` 类管理视口变换。
- **光照模型**：内置方向光 (`DirectionalLight`) 和点光源 (`PointLight`) 数据结构，配合自定义片元着色器可实现 Phong 光照模型。
- **数学库**：包含 `Vec2`/`Vec3`/`Vec4` 向量、`Mat3`/`Mat4` 矩阵、`Color` 颜色、`Transform` 空间变换等基础数学组件。
- **多种示例**：提供 6 个示例程序，覆盖窗口测试、三角形绘制、深度测试、混合、透视投影、Phong 光照，详见 [示例文档](docs/examples/index.md)。

## 系统要求

| 项目 | 要求 |
| -------- | ------------------------- |
| 操作系统 | Windows 7 及以上 (x86/x64)，其他平台待扩展 |
| 编译器 | 支持 C++20 的编译器 |
| 构建工具 | CMake 3.7 及以上 |
| 运行时 | Windows 下依赖 Windows GDI (系统自带)，平台抽象层支持扩展 |

## 安装步骤

### 1. 克隆仓库

```powershell
git clone https://github.com/shangguan2024/srdr.git
cd srdr
```

### 2. 配置构建

```powershell
cmake -B build -S src
```

### 3. 编译项目

```powershell
cmake --build build
```

编译完成后，可执行文件位于 `build/application/Debug/srdr.exe` (Debug 模式) 或 `build/application/Release/srdr.exe` (Release 模式)。

### 4. 运行示例

```powershell
build\application\Debug\srdr.exe
```

运行后将显示交互式菜单，输入数字选择示例程序。

## 配置说明

### CMake 配置选项

项目通过 CMake 管理构建，所有配置在 `src/CMakeLists.txt` 中定义：

- `CMAKE_CXX_STANDARD`：固定为 `20`，需要编译器支持 C++20。
- 平台宏定义：Windows 平台自动定义 `SRDR_SYSTEM_WINDOWS` 预处理宏。
- 输出目录结构：
  - `srdr_core`：静态库，基础数学与数据结构。
  - `srdr_platform`：静态库，平台窗口抽象层。
  - `srdr_renderer`：静态库，渲染管线核心。
  - `srdr`：可执行文件，主程序入口与示例。

### 编译选项

项目使用 `.clang-format` 配置文件统一代码风格（基于 LLVM 风格定制）。建议在提交代码前运行格式化工具。

详细的 API 文档请参阅以下页面：

- [API 总览](docs/api/index.md) -- 模块依赖关系与快速索引
- [渲染器核心](docs/api/renderer.md) -- `Renderer`、`OutputMerger`、`FrameBuffer`
- [着色器接口](docs/api/shader-interfaces.md) -- `Vertex`、`Fragment`、`Primitive` 数据结构
- [数学库](docs/api/math.md) -- `Vector`、`Matrix`、`Color`、`Transform`、`Geometry`
- [场景管理](docs/api/scene.md) -- `Camera`、`DirectionalLight`、`PointLight`
- [平台抽象层](docs/api/platform.md) -- `IWindow`、`WindowFactory`

## 使用示例

以下代码展示了使用 SRDR 绘制一个红色三角形的完整流程：

```cpp
#include "Color.hpp"
#include "Renderer.hpp"
#include "Vertex.hpp"
#include "WindowFactory.hpp"
#include <thread>
#include <vector>

int main() {
    // 1. 创建窗口
    srdr::WindowFactory wf;
    auto window = wf.createWindow();
    if (!window->create(800, 600, "Triangle")) {
        return -1;
    }

    // 2. 创建渲染器
    srdr::Renderer device(window);

    // 3. 准备顶点数据
    std::vector<srdr::Vertex> tri(3);
    std::vector<std::size_t> ind{ 0, 1, 2 };
    tri[0].color = srdr::Color(1, 0, 0);   // 红色
    tri[1].color = srdr::Color(0, 1, 0);   // 绿色
    tri[2].color = srdr::Color(0, 0, 1);   // 蓝色
    tri[0].position = { 0, 0, 0 };
    tri[1].position = { 1, 1, 0 };
    tri[2].position = { 0, 1, 0 };

    // 4. 渲染循环
    while (window->isRunning()) {
        device.beginScene();
        device.draw(tri, ind);
        device.endScene();
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    return 0;
}
```

## 目录结构

```plaintext
srdr/
├── .clang-format              # 代码风格配置文件
├── .gitignore                 # Git 忽略规则
├── LICENSE                    # MIT 许可证
├── README.md                  # 本文件
├── assets/                    # 资源
├── docs/                      # 文档
└── src/
    ├── CMakeLists.txt         # 顶层 CMake 构建入口
    ├── core/                  # 核心数学与数据结构库 (srdr_core)
    │   ├── CMakeLists.txt
    │   ├── Color.hpp/cpp      # RGBA 颜色类型
    │   ├── Vector.hpp         # Vec2/Vec3/Vec4 向量模板
    │   ├── Matrix.hpp         # Mat3/Mat4 矩阵模板
    │   ├── Transform.hpp/cpp  # 空间变换 (透视/视图/旋转/平移)
    │   └── Geometry.hpp/cpp   # 平面方程、AABB 等几何工具
    ├── platform/              # 平台抽象层 (srdr_platform)
    │   ├── CMakeLists.txt
    │   ├── IWindow.hpp           # 窗口接口
    │   ├── Win32Window.hpp/cpp   # Windows 平台实现 (Win32 GDI)
    │   └── WindowFactory.hpp/cpp # 窗口工厂
    ├── renderer/                 # 渲染管线 (srdr_renderer)
    │   ├── CMakeLists.txt
    │   ├── Renderer.hpp/cpp   # 渲染器主类
    │   ├── stage/             # 渲染管线各阶段
    │   │   ├── VertexLoader.hpp/cpp       # 顶点加载
    │   │   ├── VertexShader.hpp/cpp       # 顶点着色器
    │   │   ├── PrimitiveAssembler.hpp/cpp # 图元组装 (裁剪/视口变换)
    │   │   ├── Rasterizer.hpp/cpp         # 光栅化
    │   │   ├── FragmentShader.hpp/cpp     # 片元着色器
    │   │   └── OutputMerger.hpp/cpp       # 输出合并 (深度/混合)
    │   ├── shader_interfaces/ # 着色器接口数据结构
    │   │   ├── Vertex.hpp     # Vertex/VertexInput/VertexOutput
    │   │   ├── Fragment.hpp   # FragmentInput/FragmentOutput
    │   │   ├── Primitive.hpp  # Primitive/ScreenVertex/EdgeEquation
    │   │   ├── FrameBuffer.hpp/cpp     # 帧缓冲
    │   │   ├── ColorAttachment.hpp/cpp # 颜色附件
    │   │   └── DepthAttachment.hpp/cpp # 深度附件
    │   └── scene/             # 场景管理
    │       ├── Camera.hpp/cpp # 相机 (视图/投影矩阵)
    │       └── Light.hpp      # 光源类型 (方向光/点光)
    └── application/           # 应用程序与示例 (srdr)
        ├── CMakeLists.txt
        ├── app.cpp            # 主程序入口与菜单
        └── examples/          # 示例程序
            ├── ExampleWindowTest.hpp/cpp
            ├── ExampleDrawTriangle.hpp/cpp
            ├── ExampleDepthTest.hpp/cpp
            ├── ExampleBlend.hpp/cpp
            ├── ExamplePerspectiveProjection.hpp/cpp
            └── ExamplePhongLighting.hpp/cpp
```

## 测试命令

项目目前以示例程序作为功能验证手段。编译完成后运行可执行文件并选择对应示例编号即可进行验证：

```powershell
build\application\Debug\srdr.exe
```

可用示例：

| 编号 | 示例名称 | 文档 | 验证内容 |
| --- | --- | --- | --- |
| 1 | WindowTest | [文档](docs/examples/01-window-test.md) | 窗口创建与像素显示 |
| 2 | DrawTriangle | [文档](docs/examples/02-draw-triangle.md) | 基础三角形绘制 |
| 3 | DepthTest | [文档](docs/examples/03-depth-test.md) | 深度测试功能 |
| 4 | Blend | [文档](docs/examples/04-blend.md) | Alpha 混合功能 |
| 5 | PerspectiveProjection | [文档](docs/examples/05-perspective-projection.md) | 透视投影与矩阵变换 |
| 6 | PhongLighting | [文档](docs/examples/06-phong-lighting.md) | 自定义着色器与 Phong 光照 |

## 构建与部署

### Debug 构建

```powershell
cmake -B build -S src -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

### Release 构建

```powershell
cmake -B build -S src -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

### 清理构建

```powershell
rm -r build
```

### 部署说明

SRDR 为纯 CPU 光栅化渲染器，运行时无需 GPU 或图形 API (DirectX/OpenGL/Vulkan) 支持。当前 Windows 平台依赖系统 GDI 进行窗口像素显示，接口层支持扩展至其他平台，详见[平台抽象层 API 文档](docs/api/platform.md)。

## 贡献指南

1. Fork 本仓库并创建特性分支 (`git checkout -b feature/your-feature`)。
2. 确保代码风格符合 `.clang-format` 配置，建议在提交前运行 `clang-format -i src/**/*.cpp src/**/*.hpp`。
3. 提交变更 (`git commit -m "feat: add your feature"`)。
4. 推送到分支 (`git push origin feature/your-feature`)。
5. 创建 Pull Request。

### 编码规范

- 遵循 `.clang-format` 中定义的代码风格（基于 LLVM，缩进 4 空格，列宽 100）。
- **命名空间**：小写，嵌套使用 `::` 连接（`srdr`、`srdr::transform`、`detail`）。
- **类与结构体**：PascalCase（`Renderer`、`Color`、`VertexShader`）。
- **方法与自由函数**：camelCase（`getViewMatrix`、`enableDepthTest`、`perspective`）。
- **成员变量**：`m_` 前缀 + snake_case（`m_window`、`m_vertex_buffer`）。
- **宏**：UPPER_CASE（`SRDR_SYSTEM_WINDOWS`）。
- 所有公共接口位于 `srdr` 命名空间下。
- 使用 C++20 标准特性，避免平台相关 API 泄漏至公共接口。

## 许可证

本项目基于 [MIT License](LICENSE) 开源。

```plaintext
MIT License

Copyright (c) 2026 sg

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

## 作者及联系方式

- 作者：sg
- 项目地址：[https://github.com/shangguan2024/srdr](https://github.com/shangguan2024/srdr)
