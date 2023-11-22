#include "material.hpp"

Lambertian::Lambertian(const glm::vec3& color) 
  : m_albedo(color) {}

bool Lambertian::scatter(const rt::Ray& ray, const rt::rayHitRecord& record, glm::vec3& attenuation, rt::Ray& scattered) const {
  glm::vec3 scatteredDirection = record.normal + randomUnitVector();

  bool nearZero = 
    (fabs(scatteredDirection.x) < 1e-8) &&
    (fabs(scatteredDirection.y) < 1e-8) &&
    (fabs(scatteredDirection.z) < 1e-8);

  if(nearZero) {
    scatteredDirection = record.normal;
  }

  scattered   = rt::Ray(record.point, scatteredDirection);
  attenuation = m_albedo;

  return true;
}

Metal::Metal(const glm::vec3& color, const float fuzzy) 
  : m_albedo(color), m_fuzzy(fuzzy) {}

bool Metal::scatter(const rt::Ray& ray, const rt::rayHitRecord& record, glm::vec3& attenuation, rt::Ray& scattered) const {
  glm::vec3 fuzziness = m_fuzzy * randomUnitVector();
  glm::vec3 reflected = glm::reflect(glm::normalize(ray.direction()), record.normal);

  scattered = rt::Ray(record.point, reflected + fuzziness);
  attenuation = m_albedo;

  return glm::dot(scattered.direction(), record.normal) > 0;
}

Dieletric::Dieletric(const glm::vec3& albedo, const float refractionIndex)
  : m_albedo(albedo), m_refractionIndex(refractionIndex) {}

bool Dieletric::scatter(const rt::Ray& ray, const rt::rayHitRecord& record, glm::vec3& attenuation, rt::Ray& scattered) const {
  attenuation = m_albedo;

  float refractionRatio = record.isFrontFace ? (1.0/m_refractionIndex) : m_refractionIndex;

  glm::vec3 unitDirection = glm::normalize(ray.direction());

  float cosineTheta = fmin(glm::dot(-unitDirection, record.normal), 1.0f);
  float sineTheta   = sqrt(1.0f - (cosineTheta * cosineTheta));

  bool cannotRefract = refractionRatio * sineTheta > 1.0f;

  glm::vec3 refracted;

  if(cannotRefract || reflectance(cosineTheta, refractionRatio) > randomFloat()) {
    refracted = glm::reflect(unitDirection, record.normal); 
  }
  else {
    refracted = glm::refract(unitDirection, record.normal, refractionRatio); 
  }

  scattered = rt::Ray(record.point, refracted); 

  return true;
}

float Dieletric::reflectance(const float cosine, const float refractionRatio) const {
  float r0 = (1 - refractionRatio) / (1 + refractionRatio);

  r0 = r0 * r0;

  return r0 + (1 - r0) * pow((1 - cosine), 5);
}
