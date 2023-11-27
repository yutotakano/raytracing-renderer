#include "arealight.h"

AreaLight::AreaLight(Point3f position, Color3f intensity, std::shared_ptr<Object> shape) : Light(position, intensity), shape(shape)
{
}

AreaLight AreaLight::fromJson(const nlohmann::json &json_data)
{
  Point3f position = json_data["position"];
  Color3f intensity = json_data["intensity"];

  std::shared_ptr<Object> shape = Object::fromJson(json_data["shape"]);

  return AreaLight(position, intensity, shape);
}
