#ifndef BVH_H
#define BVH_H

#include "../objects/object.h"
#include "../lights/light.h"
#include "bvhnode.h"

/**
 * @brief Represents a bounding volume hierarchy.
 */
class BVH {
public:
  BVH(std::vector<std::shared_ptr<Object>> objects,
      std::vector<std::shared_ptr<Light>> lights);
  
  std::shared_ptr<BVHNode> constructBVHTree(std::vector<std::shared_ptr<BVHNode>> &nodes, int start, int end);

  std::optional<Intersection> intersect(const Ray &ray, float minDepth, float maxDepth) const;

  BoundingBox getBoundingBox() const;
                                          
private:
  std::shared_ptr<BVHNode> root;
};

#endif // BVH_H
