#include "arealight.h"
#include <iostream>

AreaLight::AreaLight(Point3f position, Color3f intensity, std::shared_ptr<Object> shape) : Light(position, intensity), shape(shape)
{
}

AreaLight AreaLight::fromJson(const nlohmann::json &json_data)
{
  std::shared_ptr<Object> shape = Object::fromJson(json_data["shape"]);

  // Position is taken from the shape's position
  Point3f position = shape->getBoundingBox().getCenter();
  Color3f intensity = json_data["intensity"];

  return AreaLight(position, intensity, shape);
}
