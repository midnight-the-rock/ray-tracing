#pragma once

#include <cstdlib>
#include <glm/glm.hpp>

static float randomFloat() {
  return rand() / (RAND_MAX + 1.0);
}

static float randomFloat(const float min, const float max) {
  return min + (max-min) * randomFloat();
}

static float clamp(const float x, const float min, const float max) {
  if(x < min) {
    return min;
  }
  if(x > max) {
    return max;
  }

  return x;
}

static glm::vec3 randomVec3() {
  return glm::vec3(randomFloat(), randomFloat(), randomFloat()); 
}

static glm::vec3 randomVec3(const float min, const float max) {
  return glm::vec3(randomFloat(min, max), randomFloat(min, max), randomFloat(min, max));
}

static glm::vec3 rejection() {
  while(true) {
    glm::vec3 point = randomVec3(-1.0f, 1.0f);

    float squared = (point.x * point.x) + (point.y + point.y) + (point.z + point.z);
    if(squared >= 1.0f) {
      continue;
    }

    return point;
  }
}

static glm::vec3 randomUnitVector() {
  return glm::normalize(rejection());
}

static glm::vec3 randomUnitDisk() {
  while(true) {
    glm::vec3 point = glm::vec3(randomFloat(-1.0, 1.0f), randomFloat(-1.0, 1.0f), 0);

    float squared = (point.x * point.x) + (point.y + point.y) + (point.z + point.z);
    if(squared >= 1.0f) {
      continue;
    }

    return point;
  }
}
