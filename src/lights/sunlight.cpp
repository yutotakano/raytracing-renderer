#include "sunlight.h"

SunLight::SunLight(Point3f position, Color3f intensity) : Light(position, intensity)
{
}

SunLight SunLight::fromJson(const nlohmann::json &json_data)
{
  Point3f position = json_data["position"];
  Color3f intensity = json_data["intensity"];
  return SunLight(position, intensity);
}
