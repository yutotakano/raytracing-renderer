#include "light.h"
#include "aliases.h"

class PointLight : public Light
{
public:
  PointLight(Point3f position, Color3f intensity);
  static PointLight fromJson(const nlohmann::json &json_data);
};
