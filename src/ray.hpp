#pragma once

#include <memory>
#include <glm/glm.hpp>

class Material;

namespace rt {
  class Ray {
  public:
    Ray();
    Ray(const glm::vec3& origin, const glm::vec3& direction);

    auto origin() const -> glm::vec3;
    auto direction() const -> glm::vec3;
    auto at(float t) const -> glm::vec3;

  private:
    glm::vec3 m_origin    {};
    glm::vec3 m_direction {};
  };

  struct rayHitRecord {
    float t = 0;
    bool  isFrontFace = false;

    glm::vec3 point;
    glm::vec3 normal;

    std::shared_ptr<Material> material;

    auto setNormalFace(const Ray& ray, const glm::vec3 outwardNormal) noexcept -> void;
  };
}
