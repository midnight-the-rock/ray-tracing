#pragma once

#include <array>
#include <thread>
#include <future>
#include <vector>
#include <iostream>
#include <glm/glm.hpp>

#include "ray.hpp"
#include "camera.hpp"
#include "scene.hpp"
#include "sphere.hpp"
#include "utils.hpp"

struct RenderInfo {
  int32_t depth;
  int32_t width;
  int32_t heigth;
  int32_t samplesPP;

  Scene*  scene;
  rt::Camera* camera;
};

class Renderer {
public:
  Renderer(RenderInfo* info);

  void run();
private:
  RenderInfo*             m_info;
  std::vector<glm::vec3>  m_imageBuffer;

private:
  glm::vec3 rayColor(const rt::Ray& ray, const uint32_t depth) const;
};
