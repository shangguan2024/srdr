#include "Vector.hpp"
#include <cstddef>
#include <utility>

namespace srdr {

template<typename T, size_t N>
template<typename... Args>
    requires(sizeof...(Args) == N)
Vector<T, N>::Vector(Args&&... args)
        : m_data(static_cast<T>(std::forward<Args>(args))...) {}

template<typename T, size_t N>
T& Vector<T, N>::operator[](size_t index) {
    return m_data[index];
}

template<typename T, size_t N>
const T& Vector<T, N>::operator[](size_t index) const {
    return m_data[index];
}

} // namespace srdr
