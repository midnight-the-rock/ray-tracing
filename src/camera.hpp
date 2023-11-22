#pragma once

#include <glm/glm.hpp>

#include "ray.hpp"
#include "utils.hpp"

namespace rt {
  struct cameraCreateInfo {
    float fov           = 0;
    float aperture      = 0;
    float aspectRatio   = 0;
    float focusDistance = 0;

    glm::vec3 up        {};
    glm::vec3 origin    {};
    glm::vec3 direction {};
  };

  class Camera {
  public:
    explicit Camera(cameraCreateInfo* info);

    auto at(const float u, const float v) const -> rt::Ray;

  private:
    float m_lensRadius = 0;

    glm::vec3 m_orientationW {};
    glm::vec3 m_orientationU {};
    glm::vec3 m_orientationV {};

    glm::vec3 m_vertical   {};
    glm::vec3 m_horizontal {};
    glm::vec3 m_lowerLeftCorner {};

    cameraCreateInfo* m_info;

  private:
    inline auto setOrientation() noexcept -> void;
    inline auto setViewportSize() noexcept -> void;
    inline auto setLowerLeftCorner() noexcept -> void;
  };
}
