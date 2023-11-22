#include "scene.hpp"

void Scene::push(std::shared_ptr<Surface> object) {
  m_objects.push_back(object);
}

void Scene::clear() {
  m_objects.clear();
}

bool Scene::hit(const rt::Ray& ray, const float tmin, const float tmax, rt::rayHitRecord& record) const {
  bool   hitAnything  = false;
  float nearestHit   = tmax;
  rt::rayHitRecord temporalRecord;

  for(auto& object : m_objects) {
    if(object->hit(ray, tmin, nearestHit, temporalRecord)) {
      record = temporalRecord;

      hitAnything = true;
      nearestHit  = temporalRecord.t;
    }
  }

  return hitAnything;
}
