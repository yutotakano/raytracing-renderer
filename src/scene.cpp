#include "scene.h"
#include <Eigen/Core>
#include <json/json.hpp>

Scene Scene::fromJson(const nlohmann::json& json_data) {
  Scene scene = Scene();
  for (auto &object : json_data["shapes"]) {
    scene.addObject(Object::FromJson(object));
  }
  for (auto &light : json_data["lights"]) {
    scene.addLight(Light::FromJson(light));
  }
  for (auto &camera : json_data["cameras"]) {
    scene.AddCamera(Camera::FromJson(camera));
  }
  scene.buildBVH();
  return scene;
}

Scene::Scene() {
  // Set default background color to black
  background_color_ = Color(0, 0, 0);
}

void Scene::addObject(std::shared_ptr<Object> object) {
  objects_.push_back(object);
}

void Scene::addLight(std::shared_ptr<Light> light) {
  lights_.push_back(light);
}

void Scene::buildBVH() {
  // Build BVH acceleration structure for querying objects in the scene
  bvh_ = BVH(objects_);
}

Color Scene::traceRay(const Ray& ray, int depth) const {
  // Find closest intersection with an object in the scene
  Intersection intersection = bvh_.Intersect(ray);

  // If no intersection, return background color
  if (!intersection.hit) {
    return background_color_;
  }

  // Calculate color at intersection point using Phong shading model
  Color color = intersection.object->material->ambient * intersection.object->material->color;
  for (const auto& light : lights_) {
    color += intersection.object->material->CalculatePhongShading(ray, intersection, *light, objects_);
  }

  // If maximum recursion depth has been reached, return current color
  if (depth == max_depth_) {
    return color;
  }

  // Calculate reflected color and add to current color
  Ray reflected_ray = intersection.Reflect(ray);
  Color reflected_color = TraceRay(reflected_ray, depth + 1);
  color += intersection.object->material->specular * reflected_color;

  return color;
}


