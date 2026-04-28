# PhongLighting 示例

## 概述

PhongLighting 示例是 SRDR 功能最完整的示例，综合运用自定义顶点着色器与片元着色器，实现基于 Phong 反射模型的逐片元光照。场景包含一个旋转的立方体，受方向光 (Directional Light) 和点光源 (Point Light) 的联合照明，展示漫反射、高光反射和环境光的合成效果。

## 运行效果

![PhongLighting 示例](../../assets/examples/phong_lighting.png)

渲染结果包含以下光照分量：

- **环境光** (Ambient) -- 恒定微弱照明，防止背光面完全黑暗
- **漫反射** (Diffuse) -- 方向光与点光源的漫反射分量，基于 Lambert 模型
- **高光反射** (Specular) -- Blinn-Phong 高光模型，光泽度系数 32

## 核心流程

### 1. 创建渲染器并启用深度测试

```cpp
Renderer device(window);
device.enable(State::DEPTH_TEST);
```

### 2. 创建相机

```cpp
Camera camera(Vec3(0, -1, 2), Vec3(0, 0, 0), Vec3(0, 1, 0),
              1.0472f, float(width) / float(height), 0.1f, 100.0f);
```

### 3. 定义自定义顶点着色器

```cpp
device.setVertexShader([&camera, &angle](const VertexInput& in) {
    Mat4 model = transform::rotate(angle, { 0.0f, 1.0f, 0.0f });
    Mat4 mvp = camera.getProjectionMatrix() * camera.getViewMatrix() * model;

    Vec4 clip = mvp * Vec4(in.a_position, 1.0f);
    VertexOutput out;
    out.v_position = clip;                                    // 裁剪坐标
    out.v_normal = Vec3(model * Vec4(in.a_normal, 0.0f));     // 法线变换到世界空间
    out.v_color = in.a_color;
    out.v_world_position = model * Vec4(in.a_position, 1.0f); // 世界坐标
    return out;
});
```

关键点：法线使用模型矩阵的 3x3 部分变换 (齐次坐标 w=0 忽略平移)，世界坐标通过模型矩阵变换 (w=1 包含平移)。

### 4. 定义光源

```cpp
DirectionalLight dl{
    normalize(Vec3(-0.5f, -0.8f, 1.0f)),   // 方向
    Color(1.0f, 0.95f, 0.9f),              // 暖色光
    0.8f                                   // 强度
};

PointLight pl{
    Vec3(0.7f, -0.7f, 0.3f),               // 位置
    Color(0.3f, 0.0f, 0.6f),               // 紫色光
    0.8f,                                  // 强度
    1.0f,                                  // 衰减常数项
    0.09f,                                 // 衰减一次项
    0.032f                                 // 衰减二次项
};
```

### 5. 定义自定义片元着色器

```cpp
Vec3 camera_pos(0, -1, 2);

device.setFragmentShader([&dl, &pl, &camera_pos](const FragmentInput& in) {
    FragmentOutput out;
    out.o_position = in.f_position;

    Vec3 N = normalize(in.v_normal);                                  // 法线
    Vec3 V = normalize(camera_pos - Vec3(in.v_world_position));       // 视线方向

    float shininess = 32.0f;
    float ks = 0.5f;

    Vec3 rgb(0.08f, 0.08f, 0.08f);  // 环境光

    // ---- 方向光计算 ----
    Vec3 L = normalize(dl.direction);
    Vec3 H = normalize(L + V);                                         // 半程向量
    float diff_d = std::max(dot(N, L), 0.0f);
    float spec_d = std::pow(std::max(dot(N, H), 0.0f), shininess);
    rgb += dl.color.rgb() * dl.intensity * (diff_d + ks * spec_d);

    // ---- 点光源计算 ----
    Vec3 Lp = normalize(pl.position - Vec3(in.v_world_position));
    Vec3 Hp = normalize(Lp + V);
    float dist = length(pl.position - Vec3(in.v_world_position));
    float att = 1.0f / (pl.constant + pl.linear * dist + pl.quadratic * dist * dist);
    float diff_p = std::max(dot(N, Lp), 0.0f);
    float spec_p = std::pow(std::max(dot(N, Hp), 0.0f), shininess);
    rgb += pl.color.rgb() * pl.intensity * (diff_p + ks * spec_p) * att;

    out.o_color = Color(rgb * in.v_color.rgb(), in.v_color.a);
    return out;
});
```

## Phong 光照模型详解

### 光照方程

```cpp
output = ambient + diffuse + specular
```

### 环境光 (Ambient)

```cpp
Vec3 rgb(0.08f, 0.08f, 0.08f);
```

恒定低强度照明，模拟场景中的间接光照，防止背光面完全黑色。

### 漫反射 (Diffuse) -- Lambert 模型

```cpp
float diff = std::max(dot(N, L), 0.0f);
```

漫反射强度与法线 `N` 和光线方向 `L` 的夹角余弦成正比。`std::max` 确保背光面结果为 0。

### 高光反射 (Specular) -- Blinn-Phong 模型

```cpp
Vec3 H = normalize(L + V);
float spec = std::pow(std::max(dot(N, H), 0.0f), shininess);
```

Blinn-Phong 使用半程向量 `H` 代替反射向量，计算效率更高。`shininess` 控制高光区域的大小：值越大，高光越集中。

### 点光源衰减

```cpp
float att = 1.0f / (constant + linear * dist + quadratic * dist * dist);
```

点光源的光照强度随距离衰减，使用二次衰减模型模拟物理上的平方反比规律。

## 立方体几何构建

```cpp
void ExamplePhongLighting::getCube(std::vector<Vertex>& verts, std::vector<std::size_t>& idx) {
    // 8 个顶点位置
    std::vector<Vec3> v{
        { -0.5f, -0.5f, -0.5f },  // 0
        { -0.5f, -0.5f,  0.5f },  // 1
        { -0.5f,  0.5f, -0.5f },  // 2
        { -0.5f,  0.5f,  0.5f },  // 3
        {  0.5f, -0.5f, -0.5f },  // 4
        {  0.5f, -0.5f,  0.5f },  // 5
        {  0.5f,  0.5f, -0.5f },  // 6
        {  0.5f,  0.5f,  0.5f },  // 7
    };

    auto add = [&](int a, int b, int c, int d) {
        std::size_t base = verts.size();
        Vec3 normal = normalize(cross(v[b] - v[a], v[d] - v[a]));
        Color color(1, 1, 1, 1);
        verts.push_back({ v[a], normal, color, {} });
        verts.push_back({ v[b], normal, color, {} });
        verts.push_back({ v[c], normal, color, {} });
        verts.push_back({ v[d], normal, color, {} });
        idx.emplace_back(base + 0);
        idx.emplace_back(base + 1);
        idx.emplace_back(base + 2);
        idx.emplace_back(base + 2);
        idx.emplace_back(base + 3);
        idx.emplace_back(base + 0);
    };

    add(0b000, 0b100, 0b101, 0b001);
    add(0b000, 0b010, 0b110, 0b100);
    add(0b000, 0b001, 0b011, 0b010);
    add(0b111, 0b101, 0b100, 0b110);
    add(0b111, 0b011, 0b001, 0b101);
    add(0b111, 0b110, 0b010, 0b011);
}
```

每个面使用 4 个顶点构成 2 个三角形，每个顶点包含通过叉积计算的法线。此处每个面的 4 个顶点的法线相同，属于平面着色法 (Flat Shading)，但由于片元着色器执行逐片元光照，渲染结果依然呈现平滑的光照过渡。

## 渲染循环

```cpp
while (window->isRunning()) {
    auto start = std::chrono::high_resolution_clock::now();

    device.clearFrameBuffer();
    device.beginScene();
    device.draw(verts, idx);
    device.endScene();

    angle += 0.025f;

    auto end = std::chrono::high_resolution_clock::now();
    int duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::this_thread::sleep_for(std::chrono::milliseconds(16 - duration));
}
```

此示例使用精确帧时间控制：计算渲染耗时后，用剩余时间补齐到 16ms (约 60 FPS)，避免固定延迟导致的帧率不稳定。

## 关键技术要点

| 要点 | 说明 |
| --- | --- |
| 着色器组合 | 自定义顶点着色器 + 自定义片元着色器协同工作，顶点着色器输出法线和世界坐标供片元使用 |
| 法线变换 | 法线使用模型矩阵 3x3 部分变换 (w=0)，不能包含平移 |
| 多光源叠加 | 方向光和点光源的贡献在片元着色器中累加，实现多光源联合照明 |
| 逐片元光照 | 法线和位置经过光栅化插值后，在片元着色器中逐像素计算光照，比逐顶点光照更平滑 |
| 帧时间控制 | 动态计算渲染耗时，精确控制帧率至约 60 FPS |
