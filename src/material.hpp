#pragma once

#include "utils.hpp"
#include "ray.hpp"

class Material {
public:
  virtual bool scatter(const rt::Ray& ray, const rt::rayHitRecord&, glm::vec3& attenuation, rt::Ray& scattered) const = 0;
};

class Lambertian : public Material {
public:
  Lambertian(const glm::vec3& color);

  virtual bool scatter(const rt::Ray& ray, const rt::rayHitRecord&, glm::vec3& attenuation, rt::Ray& scattered) const override;
private:
  glm::vec3 m_albedo;
};

class Metal : public Material {
public:
  Metal(const glm::vec3& color, const float fuzzy);

  virtual bool scatter(const rt::Ray& ray, const rt::rayHitRecord&, glm::vec3& attenuation, rt::Ray& scattered) const override;
private:
  float     m_fuzzy;
  glm::vec3 m_albedo;
};

class Dieletric : public Material {
public:
  Dieletric(const glm::vec3& color, const float refractionIndex);

  virtual bool scatter(const rt::Ray& ray, const rt::rayHitRecord&, glm::vec3& attenuation, rt::Ray& scattered) const override;
private:
  float     m_refractionIndex;
  glm::vec3 m_albedo;

private:
  float reflectance(const float cosine, const float refractionRatio) const;
};
