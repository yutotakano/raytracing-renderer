#include "cylinder.h"

Cylinder::Cylinder(Point3f center, Vector3f axis, float radius, float height, std::optional<Material> material) : center(center), axis(axis), radius(radius), height(height), Object(material)
{
}

Cylinder Cylinder::fromJson(const nlohmann::json &json_data)
{
  Point3f center = Point3f(0.f, 0.f, 0.f);
  Vector3f axis = Vector3f(0.f, 1.f, 0.f);
  float radius = 1.f;
  float height = 1.f;

  if (json_data.contains("center"))
  {
    center = json_data["center"];
  }
  if (json_data.contains("axis"))
  {
    axis = json_data["axis"];
  }
  if (json_data.contains("radius"))
  {
    radius = json_data["radius"];
  }
  if (json_data.contains("height"))
  {
    height = json_data["height"];
  }

  std::optional<Material> material;
  if (json_data.contains("material"))
  {
    material = Material::fromJson(json_data["material"]);
  }

  return Cylinder(center, axis, radius, height, material);
}
