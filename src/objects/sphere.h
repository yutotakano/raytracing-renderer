#ifndef SPHERE_H
#define SPHERE_H

#include "object.h"
#include "../vector.h"

/**
 * @brief Represents a sphere object.
 */
class Sphere : public Object
{
public:
  Sphere(Point3f center, float radius, std::optional<Material> material);
  static Sphere fromJson(const nlohmann::json &json_data);

  Point3f center;
  float radius;
};

#endif // SPHERE_H
