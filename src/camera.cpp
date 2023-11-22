#include "camera.hpp"

namespace rt {
  Camera::Camera(cameraCreateInfo* info) : m_info(info) {
    setOrientation();
    setViewportSize();
    setLowerLeftCorner();

    m_lensRadius = m_info->aperture / 2;
  } 

  auto Camera::at(const float u, const float v) const -> Ray {
    glm::vec3 radius = m_lensRadius * randomUnitDisk();
    glm::vec3 offset = (m_orientationU * radius.x) + (m_orientationV * radius.y);

    glm::vec3 origin = m_info->origin + offset;
    glm::vec3 direction = m_lowerLeftCorner + (u * m_horizontal) + (v * m_vertical) - m_info->origin - offset;
    
    return Ray(origin, direction);
  }
  
  auto Camera::setOrientation() noexcept -> void {
    m_orientationW = glm::normalize(m_info->origin - m_info->direction);
    m_orientationU = glm::normalize(glm::cross(m_info->up, m_orientationW));
    m_orientationV = glm::cross(m_orientationW, m_orientationU);
  }

  auto Camera::setViewportSize() noexcept -> void {
    float theta = glm::radians(m_info->fov);
    float height = tan(theta / 2);

    float viewportHeight = height * 2.0f;
    float viewportWidth  = m_info->aspectRatio * viewportHeight;
    
    m_vertical   = m_info->focusDistance * viewportHeight * m_orientationV;
    m_horizontal = m_info->focusDistance * viewportWidth  * m_orientationU;
  }

  auto Camera::setLowerLeftCorner() noexcept -> void {
    glm::vec3 halfVertical   = m_vertical / 2.0f;
    glm::vec3 halfHorizontal = m_horizontal / 2.0f;
    glm::vec3 focusDistance  = m_info->focusDistance * m_orientationW;

    m_lowerLeftCorner = m_info->origin - halfHorizontal - halfVertical - focusDistance;
  }
}
