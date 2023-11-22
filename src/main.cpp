#include "renderer.hpp"

Scene genRandomScene() {
  Scene scene;

  auto floor = std::make_shared<Lambertian>(glm::vec3(0.5f));

  scene.push(std::make_shared<Sphere>(glm::vec3(0.0f, -1000.0f, 0.0f), 1000.0f, floor));

  for(int32_t i = -11; i < 11; i++) {
    for(int32_t j = -11; j < 11; j++) {
      float randomMaterial = randomFloat();

      glm::vec3 center(i + 0.9 * randomFloat(), 0.2, j + 0.9f * randomFloat());

      if((center - glm::vec3(4.0f, 0.2f, 0)).length() > 0.9f) {
        std::shared_ptr<Material> sphereMaterial;

        if(randomMaterial < 0.8f) {
          glm::vec3 albedo = randomVec3() * randomVec3(); 

          sphereMaterial = std::make_shared<Lambertian>(albedo);
          scene.push(std::make_shared<Sphere>(center, 0.2f, sphereMaterial));
        }
        else if(randomMaterial < 0.95f) {
          float fuzz = randomFloat(0.0f, 0.5f);
          glm::vec3 albedo = randomVec3(0.5, 1.0f); 

          sphereMaterial = std::make_shared<Metal>(albedo, fuzz);
          scene.push(std::make_shared<Sphere>(center, 0.2f, sphereMaterial));
        }
        else {
          glm::vec3 albedo = randomVec3(); 

          sphereMaterial = std::make_shared<Dieletric>(albedo, 1.5f);
          scene.push(std::make_shared<Sphere>(center, 0.2f, sphereMaterial));
        }
      }
    }
  }

  auto material1 = std::make_shared<Dieletric>(glm::vec3(0.6f), 1.5f);
  auto material2 = std::make_shared<Lambertian>(glm::vec3(0.4f, 0.2f, 0.1f));
  auto material3 = std::make_shared<Metal>(glm::vec3(0.7f, 0.6f, 0.5f), 0.0f);

  scene.push(std::make_shared<Sphere>(glm::vec3(0.0f, 1.0f, 0.0f), 1.0f, material1));
  scene.push(std::make_shared<Sphere>(glm::vec3(-4.0f, 1.0f, 0.0f), 1.0f, material2));
  scene.push(std::make_shared<Sphere>(glm::vec3(4.0f, 1.0f, 0.0f), 1.0f, material3));

  return scene;
}

int main() {
  Scene scene = genRandomScene();

  float aspectRatio = 16.0f / 9.0f;

  rt::cameraCreateInfo cInfo;
  cInfo.up            = glm::vec3(0.0f, 1.0f, 0.0f);
  cInfo.origin        = glm::vec3(13.0f, 2.0f, 3.0f);
  cInfo.direction     = glm::vec3(0.0f, 0.0f, 0.0f);

  cInfo.fov           = 20.0f;
  cInfo.aperture      = 0.1f;
  cInfo.aspectRatio   = aspectRatio;

  cInfo.focusDistance = 10.0f;

  rt::Camera camera(&cInfo);

  RenderInfo rinfo;
  rinfo.width  = 1080;
  rinfo.heigth = 1080 / aspectRatio;
  rinfo.depth  = 16;
  rinfo.scene  = &scene;
  rinfo.camera = &camera;
  rinfo.samplesPP = 100;

  Renderer renderer(&rinfo);

  renderer.run();

  return 0;
}
