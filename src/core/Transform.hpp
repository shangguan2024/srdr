#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "Matrix.hpp"
#include "Vector.hpp"

namespace srdr::transform {

Mat4 perspective(float fov, float aspect, float near, float far);

Mat4 lookAt(const Vec3& eye, const Vec3& center, const Vec3& up);

Mat4 translate(const Vec3& offset);

Mat4 translate(const Mat4& m, const Vec3& offset);

} // namespace srdr::transform

#endif // TRANSFORM_HPP
