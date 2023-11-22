#include "ray.hpp"

namespace rt {
  Ray::Ray() = default; 

  Ray::Ray(const glm::vec3& origin, const glm::vec3& direction) 
    : m_origin(origin), m_direction(direction) {}

  auto Ray::origin() const -> glm::vec3 {
    return m_origin;
  }

  auto Ray::direction() const -> glm::vec3 {
    return m_direction;
  }

  auto Ray::at(float t) const -> glm::vec3 {
    return m_origin + (t * m_direction);
  }

  auto rayHitRecord::setNormalFace(const Ray& ray, const glm::vec3 outwardNormal) noexcept -> void {
    isFrontFace = glm::dot(ray.direction(), outwardNormal) < 0.0f; 

    isFrontFace ? normal = outwardNormal : normal = -outwardNormal;
  }
}
