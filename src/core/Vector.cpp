#include "Vector.hpp"
#include <cstddef>
#include <utility>

namespace srdr {

template<typename T, size_t N>
template<typename... Args>
    requires(sizeof...(Args) == N)
Vector<T, N>::Vector(Args&&... args)
        : m_data(static_cast<T>(std::forward<Args>(args))...) {}

} // namespace srdr
