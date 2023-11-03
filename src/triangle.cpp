#include "triangle.h"
#include <json/json.hpp>
#include "eigen_json.h"

Triangle::Triangle(Point3f v0, Point3f v1, Point3f v2, std::optional<Material> material) : v0(v0), v1(v1), v2(v2), Object(material)
{
}

Triangle Triangle::fromJson(const nlohmann::json &json_data)
{
  Point3f v0 = Point3f(0.f, 0.f, 0.f);
  Point3f v1 = Point3f(0.f, 0.f, 0.f);
  Point3f v2 = Point3f(0.f, 0.f, 0.f);

  if (json_data.find("v0") != json_data.end())
  {
    v0 = json_data["v0"];
  }
  if (json_data.find("v1") != json_data.end())
  {
    v1 = json_data["v1"];
  }
  if (json_data.find("v2") != json_data.end())
  {
    v2 = json_data["v2"];
  }

  std::optional<Material> material;
  if (json_data.contains("material"))
  {
    material = Material::fromJson(json_data["material"]);
  }

  return Triangle(v0, v1, v2, material);
}
