#ifndef MESH_H
#define MESH_H

#include "object.h"
#include "../vector.h"
#include "triangle.h"
#include "../bvh/bvh.h"

/**
 * @brief Represents a 3D mesh loaded from an OBJ file.
 */
class Mesh : public Object
{
public:
  Mesh(Point3f center, std::vector<Triangle> triangles, std::optional<Material> material);
  static Mesh fromJson(const nlohmann::json &json_data);

  std::optional<Intersection> intersect(const Ray &ray, float minDepth, float maxDepth) const override;

  BoundingBox getBoundingBox() const override;

private:
  Point3f center;
  std::vector<std::shared_ptr<Object>> triangles;

  std::optional<BVH> bvh;
};

#endif // MESH_H
