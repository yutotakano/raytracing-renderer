#include "arealight.h"

AreaLight::AreaLight(Point3f position, Color3f intensity)
{
  this->position = position;
  this->intensity = intensity;
}

AreaLight AreaLight::fromJson(const nlohmann::json &json_data)
{
  Point3f position = json_data["position"];
  Color3f intensity = json_data["intensity"];
  return AreaLight(position, intensity);
}
