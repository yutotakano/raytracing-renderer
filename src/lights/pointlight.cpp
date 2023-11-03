#include "pointlight.h"

PointLight::PointLight(Point3f position, Color3f intensity)
{
  this->position = position;
  this->intensity = intensity;
}

PointLight PointLight::fromJson(const nlohmann::json &json_data)
{
  Point3f position = json_data["position"];
  Color3f intensity = json_data["intensity"];
  return PointLight(position, intensity);
}
