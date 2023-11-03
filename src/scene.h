#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <json/json.hpp>
#include "object.h"
#include "camera.h"
#include "light.h"
#include <Eigen/Core>
#include "aliases.h"
#include "ray.h"
#include "intersection.h"
#include "bvh.h"

class Scene
{
public:
  Scene();
  static Scene fromJson(const nlohmann::json &json_data);

  void addObject(std::shared_ptr<Object> object);
  void addCamera(std::shared_ptr<Camera> camera);
  void addLight(std::shared_ptr<Light> light);
  void buildBVH();

  Color3f traceRay(const Ray ray, float minDepth, float maxDepth);
  Intersection intersect(const Ray ray);

private:
  Color3f background_color;
  std::vector<std::shared_ptr<Object>> objects;
  std::vector<std::shared_ptr<Light>> lights;

  std::optional<BVH> bvh;
};

#endif // SCENE_H
