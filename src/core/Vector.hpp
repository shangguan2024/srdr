#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <tuple>
#include <type_traits>

namespace detail {

template<typename T, std::size_t N>
struct VectorStorage {};

template<typename T>
struct VectorStorage<T, 1> {
    VectorStorage() = default;

    template<typename... Args>
    VectorStorage(Args&&... args) requires(sizeof...(Args) == 1)
            : data{ static_cast<T>(std::forward<Args>(args))... } {}

    union {
        T x;
        std::array<T, 1> data;
    };
};

template<typename T>
struct VectorStorage<T, 2> {
    VectorStorage() = default;

    template<typename... Args>
    VectorStorage(Args&&... args) requires(sizeof...(Args) == 2)
            : data{ static_cast<T>(std::forward<Args>(args))... } {}

    // clang-format off
    union {
        struct { T x, y; };
        struct { T s, t; };
        std::array<T, 2> data;
    };
    // clang-format on
};

template<typename T>
struct VectorStorage<T, 3> {
    VectorStorage() = default;

    template<typename... Args>
    VectorStorage(Args&&... args) requires(sizeof...(Args) == 3)
            : data{ static_cast<T>(std::forward<Args>(args))... } {}

    // clang-format off
    union {
        struct { T x, y, z; };
        struct { T r, g, b; };
        std::array<T, 3> data;
    };
    // clang-format on
};

template<typename T>
struct VectorStorage<T, 4> {
    VectorStorage() = default;

    template<typename... Args>
    VectorStorage(Args&&... args) requires(sizeof...(Args) == 4)
            : data{ static_cast<T>(std::forward<Args>(args))... } {}

    // clang-format off
    union {
        struct { T x, y, z, w; };
        struct { T r, g, b, a; };
        struct { T s, t, p, q; };
        std::array<T, 4> data;
    };
    // clang-format on
};

template<typename T, std::size_t N>
requires(N > 4)
struct VectorStorage<T, N> {
    template<typename... Args>
    VectorStorage(Args&&... args) requires(sizeof...(Args) == N)
            : data{ static_cast<T>(std::forward<Args>(args))... } {}
    std::array<T, N> data;
};

} // namespace detail

namespace srdr {

template<typename T, std::size_t N>
class Vector : public detail::VectorStorage<T, N> {
public:
    Vector() = default;

    template<typename... Args>
    Vector(Args&&... args) requires(sizeof...(Args) == N);

    Vector(const Vector<T, N - 1>& vec, T val);
    Vector(const Vector<T, N + 1>& vec);

    using detail::VectorStorage<T, N>::data;

    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    Vector& operator*=(T value);

    Vector& operator+=(const Vector& vec);
    Vector& operator-=(const Vector& vec);
    Vector& operator*=(const Vector& vec);
    Vector& operator/=(const Vector& vec);
};

using Vec2 = Vector<float, 2>;
using Vec3 = Vector<float, 3>;
using Vec4 = Vector<float, 4>;

using Vec2f = Vector<float, 2>;
using Vec3f = Vector<float, 3>;
using Vec4f = Vector<float, 4>;

using Vec2i = Vector<int, 2>;
using Vec3i = Vector<int, 3>;
using Vec4i = Vector<int, 4>;

using Vec2d = Vector<double, 2>;
using Vec3d = Vector<double, 3>;
using Vec4d = Vector<double, 4>;

template<typename T, size_t N>
template<typename... Args>
Vector<T, N>::Vector(Args&&... args) requires(sizeof...(Args) == N)
        : detail::VectorStorage<T, N>(args...) {}

template<typename T, size_t N>
Vector<T, N>::Vector(const Vector<T, N - 1>& vec, T val) {
    for (size_t i = 0; i + 1 < N; ++i) {
        data[i] = vec[i];
    }
    data[N - 1] = val;
}

template<typename T, size_t N>
Vector<T, N>::Vector(const Vector<T, N + 1>& vec) {
    for (size_t i = 0; i < N; ++i) {
        data[i] = vec[i];
    }
}

template<typename T, size_t N>
T& Vector<T, N>::operator[](size_t index) {
    return data[index];
}

template<typename T, size_t N>
const T& Vector<T, N>::operator[](size_t index) const {
    return data[index];
}

template<typename T, size_t N>
Vector<T, N>& Vector<T, N>::operator*=(T value) {
    for (auto& elem: data) elem *= value;
    return *this;
}

template<typename T, size_t N>
Vector<T, N>& Vector<T, N>::operator+=(const Vector<T, N>& vec) {
    for (size_t i = 0; i < N; ++i) data[i] += vec[i];
    return *this;
}

template<typename T, size_t N>
Vector<T, N>& Vector<T, N>::operator-=(const Vector<T, N>& vec) {
    for (std::size_t i = 0; i < N; ++i) data[i] -= vec[i];
    return *this;
}

template<typename T, size_t N>
Vector<T, N>& Vector<T, N>::operator*=(const Vector<T, N>& vec) {
    for (size_t i = 0; i < N; ++i) data[i] *= vec[i];
    return *this;
}

template<typename T, size_t N>
Vector<T, N>& Vector<T, N>::operator/=(const Vector<T, N>& vec) {
    for (size_t i = 0; i < N; ++i) data[i] /= vec[i];
    return *this;
}

template<typename T, size_t N>
Vector<T, N> operator*(const Vector<T, N>& vector, T value) {
    Vector<T, N> res(vector);
    return res *= value;
}

template<typename T, size_t N>
Vector<T, N> operator+(const Vector<T, N>& a, const Vector<T, N>& b) {
    Vector<T, N> res(a);
    return res += b;
}

template<typename T, size_t N>
Vector<T, N> operator-(const Vector<T, N>& a, const Vector<T, N>& b) {
    Vector<T, N> res(a);
    return res -= b;
}

template<typename T, size_t N>
Vector<T, N> operator*(const Vector<T, N>& a, const Vector<T, N>& b) {
    Vector<T, N> res(a);
    return res *= b;
}

template<typename T, size_t N>
Vector<T, N> operator/(const Vector<T, N>& a, const Vector<T, N>& b) {
    Vector<T, N> res(a);
    return res /= b;
}

template<typename T, std::size_t N>
T dot(const Vector<T, N>& a, const Vector<T, N>& b) {
    T sum = T(0);
    for (std::size_t i = 0; i < N; ++i) {
        sum += a[i] * b[i];
    }
    return sum;
}

template<typename T>
Vector<T, 3> cross(const Vector<T, 3>& a, const Vector<T, 3>& b) {
    return Vector<T, 3>(a[1] * b[2] - a[2] * b[1], a[2] * b[0] - a[0] * b[2],
            a[0] * b[1] - a[1] * b[0]);
}

template<typename T, std::size_t N>
T length2(const Vector<T, N>& v) {
    return dot(v, v);
}

template<typename T, std::size_t N>
T length(const Vector<T, N>& v) {
    return std::sqrt(length2(v));
}

template<typename T, std::size_t N>
Vector<T, N> normalize(const Vector<T, N>& v) {
    return v * (T(1) / length(v));
}

template<std::size_t I, typename T, std::size_t N>
constexpr auto& get(Vector<T, N>& vec) noexcept {
    static_assert(I < N, "Index out of bounds");
    return vec[I];
}

template<std::size_t I, typename T, std::size_t N>
constexpr const auto& get(const Vector<T, N>& vec) noexcept {
    static_assert(I < N, "Index out of bounds");
    return vec[I];
}

template<std::size_t I, typename T, std::size_t N>
constexpr auto&& get(Vector<T, N>&& vec) noexcept {
    static_assert(I < N, "Index out of bounds");
    return std::move(vec[I]);
}

template<std::size_t I, typename T, std::size_t N>
constexpr const auto&& get(const Vector<T, N>&& vec) noexcept {
    static_assert(I < N, "Index out of bounds");
    return std::move(vec[I]);
}

} // namespace srdr

namespace std {

template<typename T, size_t N>
struct tuple_size<srdr::Vector<T, N>> : integral_constant<size_t, N> {};

template<size_t I, typename T, size_t N>
struct tuple_element<I, srdr::Vector<T, N>> {
    using type = T;
};

} // namespace std

#endif // VECTOR_HPP
