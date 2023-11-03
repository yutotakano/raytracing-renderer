#include "light.h"
#include "vector.h"

class SunLight : public Light
{
public:
  SunLight(Point3f position, Color3f intensity);
  static SunLight fromJson(const nlohmann::json &json_data);
};
