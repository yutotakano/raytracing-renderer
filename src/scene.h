#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <json/json.hpp>
#include "object.h"
#include "camera.h"
#include "light.h"
#include <Eigen/Core>

class Scene {
public:
  Scene();
  static Scene fromJson(const nlohmann::json& json_data);

  void addObject(Object* object);
  void addCamera(Camera* camera);
  void addLight(Light* light);

  Eigen::Vector3f traceRay();

private:
  std::vector<Object*> objects;
  std::vector<Camera*> cameras;
  std::vector<Light*> lights;
};

#endif // SCENE_H
