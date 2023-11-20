#include "scene.h"
#include <iostream>

Scene Scene::fromJson(const nlohmann::json &json_data)
{
  Scene scene = Scene();
  if (json_data.contains("backgroundcolor"))
  {
    scene.background_color = json_data["backgroundcolor"];
  }
  if (json_data.contains("shapes"))
  {
    for (auto &object : json_data["shapes"])
    {
      scene.addObject(Object::fromJson(object));
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
  // bvh = BVH(objects, lights);
}

std::optional<Intersection> Scene::intersect(const Ray ray, float minDepth, float maxDepth) const
{
  // Find closest intersection with an object in the scene
  if (!bvh.has_value())
  {
    // If no BVH, loop through all objects in the scene
    std::optional<Intersection> closest_intersection;

    for (const auto &object : objects)
    {
      std::optional<Intersection> intersection = object->intersect(ray, minDepth, maxDepth);
      if (intersection.has_value())
      {
        // This was an intersection, so check if it's the closest one compared
        // to the previous closest intersection (if any)
        if (!closest_intersection.has_value() || intersection->distance < closest_intersection->distance)
        {
          intersection->object = object;
          closest_intersection = intersection;
        }
      }
    }

    return closest_intersection;
  }
  return Intersection();
}

Color3f Scene::getBackgroundColor() const
{
  return background_color;
}
