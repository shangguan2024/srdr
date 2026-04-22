#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <array>
#include <cstddef>
#include <tuple>
#include <type_traits>

namespace srdr {

template<typename T, std::size_t N>
class Vector {
public:
    Vector() = default;

    template<typename... Args>
        requires(sizeof...(Args) == N)
    Vector(Args&&... args);

    T& operator[](size_t index);
    const T& operator[](size_t index) const;

private:
    std::array<T, N> m_data;
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
    requires(sizeof...(Args) == N)
Vector<T, N>::Vector(Args&&... args)
        : m_data{ static_cast<T>(std::forward<Args>(args))... } {}

template<typename T, size_t N>
T& Vector<T, N>::operator[](size_t index) {
    return m_data[index];
}

template<typename T, size_t N>
const T& Vector<T, N>::operator[](size_t index) const {
    return m_data[index];
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
    return vec[I];
}

template<std::size_t I, typename T, std::size_t N>
constexpr const auto&& get(const Vector<T, N>&& vec) noexcept {
    static_assert(I < N, "Index out of bounds");
    return vec[I];
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
