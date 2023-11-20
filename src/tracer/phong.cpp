#include "phong.h"
#include "../ray.h"
#include "../intersection.h"
#include "../scene.h"

Phong::Phong(int bounces) : Tracer()
{
}

Phong Phong::fromJson(const nlohmann::json &json_data)
{
  // By default just once bounce
  int nbounces = 1;
  if (json_data.contains("nbounces"))
  {
    nbounces = json_data["nbounces"];
  }

  return Phong(nbounces);
}

Color3f Phong::traceRay(const Scene scene, Ray ray, float minDepth, float maxDepth) const
{
  // Find closest intersection with an object in the scene
  std::optional<Intersection> intersection = scene.intersect(ray, minDepth, maxDepth);

  // If no intersection, return background color with infinite depth
  if (!intersection.has_value())
  {
    return scene.getBackgroundColor();
  }

  // Calculate color at intersection point using Phong shading model
  Color3f color = intersection->object->material->diffuseColor;
  // for (const auto& light : lights_) {
  //   color += intersection.object->material->CalculatePhongShading(ray, intersection, *light, objects_);
  // }

  // // Calculate reflected color and add to current color
  // Ray reflected_ray = intersection.Reflect(ray);
  // Color reflected_color = TraceRay(reflected_ray, depth + 1);
  // color += intersection.object->material->specular * reflected_color;
  // Color3f color = Color3f(0.f, 0.5f, 0.f);

  return color;
}
