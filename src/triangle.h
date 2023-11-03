#include "object.h"
#include "vector.h"

class Triangle : public Object
{
public:
  Triangle(Point3f v0, Point3f v1, Point3f v2, std::optional<Material> material);
  static Triangle fromJson(const nlohmann::json &json_data);

  Point3f v0;
  Point3f v1;
  Point3f v2;
};
