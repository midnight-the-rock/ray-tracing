#include "renderer.hpp"

Renderer::Renderer(RenderInfo* info) : m_info(info) {}

void Renderer::run() {
std::cout 
  << "P3" << '\n'
  << m_info->width  << ' '
  << m_info->heigth << ' ' 
  << "\n255\n"; 

  for(int32_t j = (m_info->heigth - 1); j >= 0; j--) {
    std::cerr << "\r> remaining [" << j << "]  " << std::flush;

    for(int32_t i = 0; i < m_info->width; i++) {
      glm::vec3 pixelColor(0.0f);

      for(int32_t samples = 0; samples < m_info->samplesPP; samples++) {
        float u = float(i + randomFloat()) / (m_info->width  - 1);
        float v = float(j + randomFloat()) / (m_info->heigth - 1);

        rt::Ray ray = m_info->camera->at(u, v);

        pixelColor += rayColor(ray, m_info->depth);
      }

      float scale = 1.0 / m_info->samplesPP;

      pixelColor = sqrt(scale * pixelColor);

      std::cout 
        << static_cast<uint16_t>(256 * clamp(pixelColor.x, 0.0, 0.999)) << ' '
        << static_cast<uint16_t>(256 * clamp(pixelColor.y, 0.0, 0.999)) << ' '
        << static_cast<uint16_t>(256 * clamp(pixelColor.z, 0.0, 0.999)) << '\n';      
    }
  }
}

glm::vec3 Renderer::rayColor(const rt::Ray& ray, const uint32_t depth) const {
  rt::rayHitRecord record;

  if(depth == 0) {
    return glm::vec3(0.0f);
  }

  if(m_info->scene->hit(ray, 0.0001f, std::numeric_limits<float>::infinity(), record)) {
    rt::Ray scattered;
    glm::vec3 attenuation;

    if(record.material->scatter(ray, record, attenuation, scattered)) {
      return attenuation * rayColor(scattered, depth - 1);
    }

    return glm::vec3(0.0f); 
  }

  float t = 0.5f * (glm::normalize(ray.direction()).y + 1.0f);

  glm::vec3 initialV = { 1.0f, 1.0f, 1.0f };
  glm::vec3 endV     = { 0.5f, 0.7f, 1.0f };

  return (1.0f - t) * initialV + (t * endV);
}
