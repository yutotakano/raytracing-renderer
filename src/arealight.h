#include "light.h"
#include "vector.h"

class AreaLight : public Light
{
public:
  AreaLight(Point3f position, Color3f intensity);
  static AreaLight fromJson(const nlohmann::json &json_data);
};
