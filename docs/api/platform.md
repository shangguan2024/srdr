# 平台抽象层 API

## 模块

`srdr_platform` 静态库，位于 `src/platform/`。

平台抽象层通过接口隔离平台相关代码。当前 Windows 平台基于 Win32 GDI 实现，其他平台可通过继承 `IWindow` 接口进行扩展，上层代码无需修改。

---

## IWindow

窗口抽象接口，定义平台无关的窗口操作。

### 头文件

```cpp
#include "IWindow.hpp"
```

### 接口定义

```cpp
class IWindow {
public:
    virtual ~IWindow() = default;

    virtual bool create(int width, int height, const char* title) = 0;
    virtual void destroy() = 0;

    virtual Vec2i getWindowSize() = 0;
    virtual void getWindowSize(int& width, int& height) = 0;

    virtual bool isRunning() = 0;
    virtual void drawFrame(const uint32_t* pixels) = 0;
};
```

### 方法说明

| 方法 | 描述 |
| --- | --- |
| `create(width, height, title)` | 创建窗口，成功返回 true |
| `destroy()` | 销毁窗口 |
| `getWindowSize()` | 返回窗口客户区尺寸 (Vec2i) |
| `getWindowSize(int&, int&)` | 通过输出参数获取窗口尺寸 |
| `isRunning()` | 返回窗口是否正在运行 (关闭后返回 false) |
| `drawFrame(pixels)` | 将像素缓冲区数据显示到窗口。`pixels` 为 `uint32_t` 数组，格式 `0xAARRGGBB`，长度 `width * height` |

---

## WindowFactory

窗口工厂类，封装平台特定窗口实例的创建过程。

### 头文件

```cpp
#include "WindowFactory.hpp"
```

### 定义

```cpp
class WindowFactory {
public:
    WindowFactory() = default;
    ~WindowFactory() = default;

    std::shared_ptr<IWindow> createWindow();
};
```

### 典型用法

```cpp
WindowFactory wf;
auto window = wf.createWindow();
if (!window->create(800, 600, "SRDR")) {
    return -1;
}

// 渲染循环
while (window->isRunning()) {
    // ... 渲染逻辑 ...
    window->drawFrame(framebuffer.data());
}
```

---

## 平台扩展指南

要添加新的平台支持，需实现以下组件：

1. 继承 `IWindow` 接口，实现所有纯虚方法
2. 在 `WindowFactory::createWindow()` 中返回新平台窗口实例

示例框架：

```cpp
// MyPlatformWindow.hpp
class MyPlatformWindow : public IWindow {
public:
    bool create(int width, int height, const char* title) override;
    void destroy() override;
    Vec2i getWindowSize() override;
    void getWindowSize(int& width, int& height) override;
    bool isRunning() override;
    void drawFrame(const uint32_t* pixels) override;
};
```

```cpp
// WindowFactory.cpp
std::shared_ptr<IWindow> WindowFactory::createWindow() {
#ifdef SRDR_SYSTEM_WINDOWS
    return std::make_shared<Win32Window>();
#elif defined(SRDR_SYSTEM_LINUX)
    return std::make_shared<MyPlatformWindow>();
#endif
}
```
