#include "object.h"
#include "sphere.h"
#include "cylinder.h"
#include "triangle.h"
#include "mesh.h"

Object::Object(std::optional<Material> material) : material(material)
{
}

std::unique_ptr<Object> Object::fromJson(const nlohmann::json &json_data)
{
  std::string type = json_data["type"];

  if (type == "sphere")
  {
    return std::make_unique<Sphere>(Sphere::fromJson(json_data));
  }
  else if (type == "cylinder")
  {
    return std::make_unique<Cylinder>(Cylinder::fromJson(json_data));
  }
  else if (type == "triangle")
  {
    return std::make_unique<Triangle>(Triangle::fromJson(json_data));
  }
  else if (type == "mesh")
  {
    return std::make_unique<Mesh>(Mesh::fromJson(json_data));
  }
  else
  {
    throw std::runtime_error("Invalid object type specified in JSON file.");
  }
}
