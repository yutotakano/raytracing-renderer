#include "light.h"
#include "pointlight.h"
#include "arealight.h"
#include "sunlight.h"

/**
 * @brief Construct a new Light object.
*/
Light Light::fromJson(const nlohmann::json &json_data)
{
  // Instantiate either a point light, an area light, or a sunlight based on
  // the type specified in the JSON file
  std::string type = json_data["type"];

  if (type == "pointlight")
  {
    return PointLight::fromJson(json_data);
  }
  else if (type == "arealight")
  {
    return AreaLight::fromJson(json_data);
  }
  else if (type == "sunlight")
  {
    return SunLight::fromJson(json_data);
  }
  else
  {
    throw std::runtime_error("Invalid light type specified in JSON file.");
  }
}
