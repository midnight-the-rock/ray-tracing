#pragma once

#include <vector>
#include <memory>
#include <functional>
#include "surface.hpp" 

class Scene : public Surface {
public:
  void push(std::shared_ptr<Surface> object); 
  void clear();

  virtual bool hit(const rt::Ray& ray, const float tmin, const float tmax, rt::rayHitRecord& record) const override;

private:
  std::vector<std::shared_ptr<Surface>> m_objects;
};
