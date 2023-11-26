#include "binary.h"
#include "../ray.h"
#include "../intersection.h"
#include "../scene.h"

Binary::Binary() : Tracer(1)
{
}

Binary Binary::fromJson(const nlohmann::json &json_data)
{
  return Binary();
}

Color3f Binary::traceRay(const Scene &scene, const Ray &ray, float minDepth, float maxDepth) const
{
  // Find closest intersection with an object in the scene
  std::optional<Intersection> intersection = scene.intersect(ray, minDepth, maxDepth);

  // If no intersection, return black
  if (!intersection.has_value())
  {
    return Color3f(0.f, 0.f, 0.f);
  }

  // Just return red if there was an intersection
  return Color3f(1.f, 0.f, 0.f);
}
