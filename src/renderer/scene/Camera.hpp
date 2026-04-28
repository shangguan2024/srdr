#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Matrix.hpp"
#include "Vector.hpp"

namespace srdr {

class Camera {
public:
    Camera(const Vec3& position, const Vec3& target, const Vec3& up, float fov, float aspect,
            float z_near, float z_far);

    Mat4 getViewMatrix() const;
    Mat4 getProjectionMatrix() const;

    void setPosition(const Vec3& pos);
    void setTarget(const Vec3& target);
    void setUp(const Vec3& up);
    void setFov(float fov);
    void setAspect(float aspect);
    void setNear(float z_near);
    void setFar(float z_far);

private:
    Vec3 m_position;
    Vec3 m_target;
    Vec3 m_up;

    float m_fov;
    float m_aspect;
    float m_near;
    float m_far;
};

} // namespace srdr

#endif // CAMERA_HPP
