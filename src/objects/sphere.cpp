#include "sphere.h"

Sphere::Sphere(Point3f center, float radius, std::optional<Material> material) : Object(material), center(center), radius(radius)
{
}

Sphere Sphere::fromJson(const nlohmann::json &json_data)
{
  Point3f center = Point3f(0.f, 0.f, 0.f);
  float radius = 1.f;

  if (json_data.contains("center"))
  {
    center = json_data["center"];
  }
  if (json_data.contains("radius"))
  {
    radius = json_data["radius"];
  }

  std::optional<Material> material;
  if (json_data.contains("material"))
  {
    material = Material::fromJson(json_data["material"]);
  }

  return Sphere(center, radius, material);
}
