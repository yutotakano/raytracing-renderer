#include "scene.h"
#include <Eigen/Core>
#include <json/json.hpp>
#include "eigen_json.h"
#include "aliases.h"
#include "bvh.h"
#include "intersection.h"

Scene Scene::fromJson(const nlohmann::json &json_data)
{
  Scene scene = Scene();
  if (json_data.contains("background_color"))
  {
    scene.background_color = json_data["background_color"];
  }
  if (json_data.contains("shapes"))
  {
    for (auto &object : json_data["shapes"])
    {
      scene.addObject(std::make_shared<Object>(Object::fromJson(object)));
    }
  }
  if (json_data.contains("lightsources"))
  {
  for (auto &light : json_data["lightsources"])
    {
      scene.addLight(std::make_shared<Light>(Light::fromJson(light)));
    }
  }
  scene.buildBVH();
  return scene;
}

Scene::Scene()
{
  // Set default background color to black
  background_color = Color3f(0.f, 0.f, 0.f);
}

void Scene::addObject(std::shared_ptr<Object> object)
{
  objects.push_back(object);
}

void Scene::addLight(std::shared_ptr<Light> light)
{
  lights.push_back(light);
}

void Scene::buildBVH()
{
  // Build BVH acceleration structure for querying objects in the scene
  bvh = BVH(objects, lights);
}

Color3f Scene::traceRay(Ray ray, float minDepth, float maxDepth)
{
  // Find closest intersection with an object in the scene
  Intersection intersection = this->intersect(ray);

  // If no intersection, return background color with infinite depth
  if (!intersection.hit)
  {
    return background_color;
  }

  // If intersection is too close or too far, return background color
  if (intersection.distance < minDepth || intersection.distance > maxDepth)
  {
    return background_color;
  }

  // Calculate color at intersection point using Phong shading model
  // Color3f color = intersection.object->material->ambient * intersection.object->material->color;
  // for (const auto& light : lights_) {
  //   color += intersection.object->material->CalculatePhongShading(ray, intersection, *light, objects_);
  // }

  // // Calculate reflected color and add to current color
  // Ray reflected_ray = intersection.Reflect(ray);
  // Color reflected_color = TraceRay(reflected_ray, depth + 1);
  // color += intersection.object->material->specular * reflected_color;
  Color3f color = Color3f(0.f, 0.5f, 0.f);

  return color;
}

Intersection Scene::intersect(const Ray ray)
{
  // Find closest intersection with an object in the scene using BVH
  return Intersection();
}
