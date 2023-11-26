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
  Triangle(Point3f v0, Point3f v1, Point3f v2, Point3f uv0, Point3f uv1, Point3f uv2, std::optional<Material> material);
  Triangle(Point3f v0, Point3f v1, Point3f v2, Point3f uv0, Point3f uv2, Point3f uv3, Vector3f n0, Vector3f n1, Vector3f n2, std::optional<Material> material);
  static Triangle fromJson(const nlohmann::json &json_data);

  std::optional<Intersection> intersect(const Ray ray, float minDepth, float maxDepth) const override;

private:
  Point3f v0;
  Point3f v1;
  Point3f v2;
  std::optional<Point3f> uv0;
  std::optional<Point3f> uv1;
  std::optional<Point3f> uv2;
  std::optional<Vector3f> n0;
  std::optional<Vector3f> n1;
  std::optional<Vector3f> n2;
};

#endif // TRIANGLE_H
