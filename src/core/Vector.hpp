#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <array>
#include <cstddef>

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

} // namespace srdr

#endif // VECTOR_HPP
