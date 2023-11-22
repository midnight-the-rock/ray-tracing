#pragma once

#include "ray.hpp"

#include <memory>
#include <glm/glm.hpp>

class Surface {
public:
  virtual bool hit(const rt::Ray& ray, const float tMin, const float tMax, rt::rayHitRecord& record) const = 0;
};
