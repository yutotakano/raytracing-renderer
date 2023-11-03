#include "light.h"
#include "aliases.h"

class SunLight : public Light
{
public:
  SunLight(Point3f position, Color3f intensity);
  static SunLight fromJson(const nlohmann::json &json_data);
};
