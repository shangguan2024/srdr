#include "Transform.hpp"
#include "Matrix.hpp"
#include "Vector.hpp"

namespace srdr::transform {

Mat4 perspective(float fov, float aspect, float z_near, float z_far) {
    float tanHalfFov = std::tan(fov * 0.5f);
    Mat4 m = Mat4::zero();
    m(0, 0) = 1.0f / (aspect * tanHalfFov);
    m(1, 1) = 1.0f / tanHalfFov;
    m(2, 2) = (z_far + z_near) / (z_near - z_far);
    m(2, 3) = 2.0f * z_near * z_far / (z_near - z_far);
    m(3, 2) = -1.0f;
    return m;
}

Mat4 lookAt(const Vec3& eye, const Vec3& center, const Vec3& up) {
    Vec3 f = normalize(center - eye);
    Vec3 s = normalize(cross(f, up));
    Vec3 u = cross(s, f);

    Mat4 m = Mat4::identity();
    m(0, 0) = s.x;
    m(0, 1) = s.y;
    m(0, 2) = s.z;
    m(0, 3) = -dot(s, eye);
    m(1, 0) = u.x;
    m(1, 1) = u.y;
    m(1, 2) = u.z;
    m(1, 3) = -dot(u, eye);
    m(2, 0) = -f.x;
    m(2, 1) = -f.y;
    m(2, 2) = -f.z;
    m(2, 3) = dot(f, eye);
    m(3, 3) = 1.0f;
    return m;
}

Mat4 translate(const Vec3& offset) {
    Mat4 m = Mat4::identity();
    m(0, 3) = offset.x;
    m(1, 3) = offset.y;
    m(2, 3) = offset.z;
    return m;
}

Mat4 translate(const Mat4& m, const Vec3& offset) {
    Mat4 result = m;
    result(0, 3) = m(0, 0) * offset.x + m(0, 1) * offset.y + m(0, 2) * offset.z + m(0, 3);
    result(1, 3) = m(1, 0) * offset.x + m(1, 1) * offset.y + m(1, 2) * offset.z + m(1, 3);
    result(2, 3) = m(2, 0) * offset.x + m(2, 1) * offset.y + m(2, 2) * offset.z + m(2, 3);
    result(3, 3) = m(3, 0) * offset.x + m(3, 1) * offset.y + m(3, 2) * offset.z + m(3, 3);
    return result;
}

} // namespace srdr::transform
