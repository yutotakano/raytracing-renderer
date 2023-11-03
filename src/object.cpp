#include "object.h"
#include "sphere.h"
#include "cylinder.h"
#include "triangle.h"
#include "eigen_json.h"

Object::Object(std::optional<Material> material) : material(material)
{
}

Object Object::fromJson(const nlohmann::json &json_data)
{
  std::string type = json_data["type"];

  if (type == "sphere")
  {
    return Sphere::fromJson(json_data);
  }
  else if (type == "cylinder")
  {
    return Cylinder::fromJson(json_data);
  }
  else if (type == "triangle")
  {
    return Triangle::fromJson(json_data);
  }
  else
  {
    throw std::runtime_error("Invalid object type specified in JSON file.");
  }
}
