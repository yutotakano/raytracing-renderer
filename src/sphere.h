#include "object.h"
#include "aliases.h"

class Sphere : public Object
{
public:
  Sphere(Point3f center, float radius, std::optional<Material> material);
  static Sphere fromJson(const nlohmann::json &json_data);

  Point3f center;
  float radius;
};
