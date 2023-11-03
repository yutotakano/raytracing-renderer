#ifndef CYLINDER_H
#define CYLINDER_H

#include "object.h"
#include "../vector.h"

/**
 * @brief Represents a cylinder object.
 */
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

#endif // CYLINDER_H
