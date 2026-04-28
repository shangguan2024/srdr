#include "Camera.hpp"
#include "Matrix.hpp"
#include "Transform.hpp"

namespace srdr {

Camera::Camera(const Vec3& position, const Vec3& target, const Vec3& up, float fov, float aspect,
        float z_near, float z_far)
        : m_position(position),
          m_target(target),
          m_up(up),
          m_fov(fov),
          m_aspect(aspect),
          m_near(z_near),
          m_far(z_far) {}

Mat4 Camera::getViewMatrix() const { return transform::lookAt(m_position, m_target, m_up); }

Mat4 Camera::getProjectionMatrix() const {
    return transform::perspective(m_fov, m_aspect, m_near, m_far);
}

void Camera::setPosition(const Vec3& pos) { m_position = pos; }

void Camera::setTarget(const Vec3& target) { m_target = target; }

void Camera::setUp(const Vec3& up) { m_up = up; }

void Camera::setFov(float fov) { m_fov = fov; }

void Camera::setAspect(float aspect) { m_aspect = aspect; }

void Camera::setNear(float z_near) { m_near = z_near; }

void Camera::setFar(float z_far) { m_far = z_far; }

} // namespace srdr
