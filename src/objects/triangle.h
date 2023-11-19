#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "object.h"
#include "../vector.h"

/**
 * @brief Represents a triangle object.
 */
class Triangle : public Object
{
public:
  Triangle(Point3f v0, Point3f v1, Point3f v2, std::optional<Material> material);
  static Triangle fromJson(const nlohmann::json &json_data);

  std::optional<Intersection> intersect(const Ray ray, float minDepth, float maxDepth) const override;

  Point3f v0;
  Point3f v1;
  Point3f v2;
};

#endif // TRIANGLE_H
