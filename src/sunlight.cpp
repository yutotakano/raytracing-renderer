#include "sunlight.h"
#include <json/json.hpp>
#include "eigen_json.h"

SunLight::SunLight(Point3f position, Color3f intensity)
{
  this->position = position;
  this->intensity = intensity;
}

SunLight SunLight::fromJson(const nlohmann::json &json_data)
{
  Point3f position = json_data["position"];
  Color3f intensity = json_data["intensity"];
  return SunLight(position, intensity);
}
