#include "object.h"
#include "vector.h"

class Cylinder : public Object
{
public:
  Cylinder(Point3f center, Vector3f axis, float radius, float height, std::optional<Material> material);
  static Cylinder fromJson(const nlohmann::json &json_data);

  Point3f center;
  Vector3f axis;
  float radius;
  float height;
};
