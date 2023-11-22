#pragma once

#include "surface.hpp"
#include "material.hpp"

class Sphere : public Surface {
public:
  Sphere(const glm::vec3& center, const float radius, std::shared_ptr<Material> material);

  virtual bool hit(const rt::Ray& ray, const float tMin, const float tMax, rt::rayHitRecord& record) const override;
private:
  float     m_radius;
  glm::vec3 m_center;

  std::shared_ptr<Material> m_material;
};
