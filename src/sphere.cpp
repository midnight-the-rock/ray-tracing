#include "sphere.hpp"

Sphere::Sphere(const glm::vec3& center, const float radius, std::shared_ptr<Material> material) 
  : m_center(center), m_radius(radius), m_material(material) {}

bool Sphere::hit(const rt::Ray& ray, const float tmin, const float tmax, rt::rayHitRecord& record) const {
  glm::vec3 offset = ray.origin() - m_center;

  float a = glm::dot(ray.direction(), ray.direction());
  float b = 2.0f * glm::dot(offset, ray.direction());
  float c = glm::dot(offset, offset) - (m_radius * m_radius);

  float discriminant = (b * b) - (4 * a * c);

  if(discriminant < 0) {
    return false;
  }

  float cuadratic = (-b - sqrt(discriminant)) / (2 * a);

  if(cuadratic < tmin || cuadratic > tmax) {
    cuadratic = (-b + sqrt(discriminant)) / (2 * a);

    if(cuadratic < tmin || cuadratic > tmax) {
      return false;
    }
  }

  record.t = cuadratic;
  record.point  = ray.at(record.t); 

  glm::vec3 outwardNormal = (record.point - m_center) / m_radius; 
  record.setNormalFace(ray, outwardNormal);

  record.material = m_material;

  return true;
}
