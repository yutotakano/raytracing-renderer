#include "scene.h"

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

Color3f Scene::traceRay(Ray ray, float minDepth, float maxDepth, bool binary) const
{
  // Find closest intersection with an object in the scene
  std::optional<Intersection> intersection = this->intersect(ray, minDepth, maxDepth);

  // If no intersection, return background color with infinite depth
  if (!intersection.has_value())
  {
    return background_color;
  }

  // If intersection is too close or too far, return background color
  // TODO: shouldn't this be within the intersect() function so we get the
  // next closest intersection if it's below minDepth?
  if (intersection->distance < minDepth || intersection->distance > maxDepth)
  {
    return background_color;
  }

  // If binary mode is enabled, don't do any shading calculation, just return
  // red if there was an intersection
  if (binary)
  {
    return Color3f(1.f, 0.f, 0.f);
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
          closest_intersection = intersection;
        }
      }
    }

    return closest_intersection;
  }
  return Intersection();
}
