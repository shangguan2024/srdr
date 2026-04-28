# 数学库 API

## 模块

`srdr_core` 静态库，位于 `src/core/`。

---

## Vector

### 头文件

```cpp
#include "Vector.hpp"
```

### 模板签名

```cpp
template<typename T, std::size_t N>
class Vector : public detail::VectorStorage<T, N>;
```

### 类型别名

| 别名 | 实际类型 | 分量访问 |
| --- | --- | --- |
| `Vec2` / `Vec2f` | `Vector<float, 2>` | `.x`, `.y` / `.s`, `.t` |
| `Vec3` / `Vec3f` | `Vector<float, 3>` | `.x`, `.y`, `.z` / `.r`, `.g`, `.b` |
| `Vec4` / `Vec4f` | `Vector<float, 4>` | `.x`, `.y`, `.z`, `.w` / `.r`, `.g`, `.b`, `.a` |
| `Vec2i` | `Vector<int, 2>` | `.x`, `.y` |
| `Vec3i` | `Vector<int, 3>` | `.x`, `.y`, `.z` |
| `Vec4i` | `Vector<int, 4>` | `.x`, `.y`, `.z`, `.w` |
| `Vec2d` | `Vector<double, 2>` | `.x`, `.y` |
| `Vec3d` | `Vector<double, 3>` | `.x`, `.y`, `.z` |
| `Vec4d` | `Vector<double, 4>` | `.x`, `.y`, `.z`, `.w` |

### 构造

```cpp
Vector() = default;                               // 零初始化
Vector(Args&&... args);                            // 逐分量初始化 (N 个参数)
Vector(const Vector<T, N-1>& vec, T val);          // 低维向量 + 尾元素
Vector(const Vector<T, N+1>& vec);                 // 从高维向量截取 (丢弃最后一个分量)
```

### 运算符

| 运算符 | 描述 |
| --- | --- |
| `operator[](size_t)` | 分量索引访问 |
| `operator*=(T)` | 标量乘法 |
| `operator+=(Vector)` | 逐分量加法 |
| `operator-=(Vector)` | 逐分量减法 |
| `operator*=(Vector)` | 逐分量乘法 (Hadamard 积) |
| `operator/=(Vector)` | 逐分量除法 |
| `operator*(Vector, T)` | 标量乘法 (自由函数) |

### 辅助函数 (定义于全局命名空间)

`Vector.hpp` 通过 `using namespace` 或 ADL 提供以下常见向量运算 (需根据实际头文件确认)：

```cpp
// 示例 (非完整列表，以头文件为准)
float dot(const Vec3& a, const Vec3& b);
Vec3 cross(const Vec3& a, const Vec3& b);
float length(const Vec3& v);
Vec3 normalize(const Vec3& v);
```

---

## Matrix

### 头文件

```cpp
#include "Matrix.hpp"
```

### 模板签名

```cpp
template<typename T, std::size_t N, std::size_t M>
class Matrix;
```

- `N` -- 行数
- `M` -- 列数
- 内部存储为 `std::array<Vector<T, M>, N>`，行主序

### 类型别名

| 别名 | 实际类型 |
| --- | --- |
| `Mat3` | `Matrix<float, 3, 3>` |
| `Mat4` | `Matrix<float, 4, 4>` |

### 静态工厂方法

```cpp
static Matrix identity();  // 单位矩阵
static Matrix zero();      // 零矩阵
```

### 运算符

| 运算符 | 描述 |
| --- | --- |
| `operator()(row, col)` | 元素访问 (双索引) |
| `operator[](row)` | 行向量访问 |
| `transposed()` | 返回转置矩阵 |
| `operator*(Matrix, Vector)` | 矩阵乘列向量 |
| `operator*(Matrix, Matrix)` | 矩阵乘法 |

### 矩阵乘法

```cpp
// 矩阵 * 列向量: NxM * M = N
template<typename T, std::size_t N, std::size_t M>
Vector<T, N> operator*(const Matrix<T, N, M>& mat, const Vector<T, M>& vec);

// 矩阵 * 矩阵: NxK * KxM = NxM
template<typename T, std::size_t N, std::size_t K, std::size_t M>
Matrix<T, N, M> operator*(const Matrix<T, N, K>& a, const Matrix<T, K, M>& b);
```

---

## Color

### 头文件

```cpp
#include "Color.hpp"
```

### 定义

```cpp
struct Color {
    union {
        struct { float r, g, b, a; };
        std::array<float, 4> data;
    };
};
```

### 构造

```cpp
Color();                              // 零初始化
Color(float r, float g, float b);     // RGB，Alpha 默认为 1.0
Color(float r, float g, float b, float a);
Color(const Vec4f& color);            // 从 Vec4 构造
Color(const Vec3f& rgb, float a);
Color(uint32_t argb);                 // 从 0xAARRGGBB 构造
```

### 公共方法

| 方法 | 描述 |
| --- | --- |
| `rgb() const` | 返回 `Vec3(r, g, b)` |
| `red() const` | 返回 `uint8_t` 格式的 R 分量 (0-255) |
| `green() const` | 返回 `uint8_t` 格式的 G 分量 |
| `blue() const` | 返回 `uint8_t` 格式的 B 分量 |
| `alpha() const` | 返回 `uint8_t` 格式的 A 分量 |
| `toUint32() const` | 返回 `0xAARRGGBB` 格式的 `uint32_t` |
| `operator*=(float)` | 标量乘法 |

### 自由函数

```cpp
Color operator+(const Color& c1, const Color& c2);  // 颜色加法
Color operator*(const Color& color, float value);     // 标量乘法
```

---

## Transform

### 头文件

```cpp
#include "Transform.hpp"
```

### 命名空间

```cpp
namespace srdr::transform;
```

### 函数

```cpp
// 透视投影矩阵
// fov: 垂直视场角 (弧度)
// aspect: 宽高比 (width / height)
// z_near: 近裁剪面
// z_far: 远裁剪面
Mat4 perspective(float fov, float aspect, float z_near, float z_far);

// 视图矩阵 (LookAt)
// eye: 相机位置
// center: 目标点
// up: 上方向
Mat4 lookAt(const Vec3& eye, const Vec3& center, const Vec3& up);

// 平移矩阵
Mat4 translate(const Vec3& offset);

// 平移矩阵 (复合)
Mat4 translate(const Mat4& m, const Vec3& offset);

// 旋转矩阵
// angle: 旋转角度 (弧度)
// axis: 旋转轴 (单位向量)
Mat4 rotate(float angle, const Vec3& axis);
```

---

## Geometry

### 头文件

```cpp
#include "Geometry.hpp"
```

### PlaneEquation

平面方程 `f(x, y) = A * x + B * y + C`，用于光栅化阶段的属性插值。

```cpp
struct PlaneEquation {
    PlaneEquation();
    PlaneEquation(float A, float B, float C);
    PlaneEquation(float x0, float y0, float f0,
                  float x1, float y1, float f1,
                  float x2, float y2, float f2);  // 从三点拟合平面

    float A, B, C;

    static PlaneEquation computePlane(float x0, float y0, float f0,
                                      float x1, float y1, float f1,
                                      float x2, float y2, float f2);

    float stepX() const;   // 返回 A (x 方向步进)
    float stepY() const;   // 返回 B (y 方向步进)
    float evaluate(float x, float y) const;  // 计算 f(x, y)
};
```

### AABB

轴对齐包围盒模板。

```cpp
template<typename T, std::size_t N>
struct AABB {};

// 2D AABB
template<typename T>
struct AABB<T, 2> {
    T min_x, max_x;
    T min_y, max_y;
};

// 3D AABB
template<typename T>
struct AABB<T, 3> {
    T min_x, max_x;
    T min_y, max_y;
    T min_z, max_z;
};
```
