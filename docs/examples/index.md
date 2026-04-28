# 示例文档

SRDR 提供 6 个示例程序，覆盖从基础窗口显示到完整 Phong 光照的渲染功能。所有示例通过主程序菜单选择运行。

## 示例列表

| 编号 | 示例名称 | 文件 | 核心概念 |
| --- | --- | --- | --- |
| 1 | [WindowTest](01-window-test.md) | `ExampleWindowTest` | 窗口创建、像素缓冲区操作、平台抽象层显示 |
| 2 | [DrawTriangle](02-draw-triangle.md) | `ExampleDrawTriangle` | 顶点数据定义、三角形绘制、渲染循环 |
| 3 | [DepthTest](03-depth-test.md) | `ExampleDepthTest` | 深度缓冲区、深度测试、片元遮挡 |
| 4 | [Blend](04-blend.md) | `ExampleBlend` | Alpha 混合、透明度合成、混合模式 |
| 5 | [PerspectiveProjection](05-perspective-projection.md) | `ExamplePerspectiveProjection` | 透视投影矩阵、视图变换、自定义着色器 |
| 6 | [PhongLighting](06-phong-lighting.md) | `ExamplePhongLighting` | 方向光与点光源、Phong 反射模型、逐片元光照 |

## 运行方式

编译项目后运行可执行文件，通过命令行菜单选择示例编号：

```powershell
./build/src/application/srdr.exe
```

控制台输出：

```plaintext
SRDR Examples
  1. Window Test
  2. Draw Triangle
  3. Depth Test
  4. Blend
  5. Perspective Projection
  6. Phong Lighting
  x. Exit
Select: _
```

输入 `1` 至 `6` 即可启动对应示例，按窗口关闭按钮返回菜单。
