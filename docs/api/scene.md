# 场景管理 API

## Camera

### 头文件

```cpp
#include "Camera.hpp"
```

### 构造

```cpp
Camera(const Vec3& position, const Vec3& target, const Vec3& up,
       float fov, float aspect, float z_near, float z_far);
```

| 参数 | 类型 | 描述 |
| --- | --- | --- |
| `position` | `const Vec3&` | 相机位置 (世界空间) |
| `target` | `const Vec3&` | 目标点 (世界空间) |
| `up` | `const Vec3&` | 上方向向量 |
| `fov` | `float` | 垂直视场角 (弧度) |
| `aspect` | `float` | 宽高比 (width / height) |
| `z_near` | `float` | 近裁剪面 |
| `z_far` | `float` | 远裁剪面 |

### 公共方法

| 方法 | 描述 |
| --- | --- |
| `getViewMatrix() const` | 返回视图矩阵 (4x4) |
| `getProjectionMatrix() const` | 返回透视投影矩阵 (4x4) |
| `setPosition(const Vec3&)` | 设置相机位置 |
| `setTarget(const Vec3&)` | 设置目标点 |
| `setUp(const Vec3&)` | 设置上方向 |
| `setFov(float)` | 设置视场角 |
| `setAspect(float)` | 设置宽高比 |
| `setNear(float)` | 设置近裁剪面 |
| `setFar(float)` | 设置远裁剪面 |

### 典型用法

```cpp
Camera camera(
    Vec3(0, -1, 2),       // 相机位置
    Vec3(0, 0, 0),        // 看向原点
    Vec3(0, 1, 0),        // Y 轴向上
    1.0472f,              // 60度视场角
    float(width) / float(height),  // 宽高比
    0.1f,                 // 近裁剪面
    100.0f                // 远裁剪面
);

// 在自定义顶点着色器中使用
Mat4 mvp = camera.getProjectionMatrix() * camera.getViewMatrix() * modelMatrix;
```

---

## Light

### 头文件

```cpp
#include "Light.hpp"
```

### DirectionalLight

方向光，模拟来自无限远方向的光源 (如太阳光)。

```cpp
struct DirectionalLight {
    Vec3 direction;    // 光照方向 (从光源指向物体)
    Color color;       // 光颜色
    float intensity;   // 光照强度
};
```

### PointLight

点光源，模拟从空间一点向所有方向均匀发光的源。

```cpp
struct PointLight {
    Vec3 position;     // 光源位置 (世界空间)
    Color color;       // 光颜色
    float intensity;   // 光照强度
    float constant;    // 衰减常数项
    float linear;      // 衰减一次项
    float quadratic;   // 衰减二次项
};
```

点光源衰减公式：

```plaintext
attenuation = 1.0 / (constant + linear * distance + quadratic * distance * distance)
```

### SpotLight (预留)

```cpp
struct SpotLight {
    // TODO
};
```

聚光灯类型已预留，尚未实现。
