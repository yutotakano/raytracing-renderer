#ifndef BVHNODE_H
#define BVHNODE_H

#include "boundingbox.h"
#include "../objects/object.h"

class BVHNode
{
public:
  BVHNode(BoundingBox box, std::shared_ptr<Object> object);
  BVHNode(std::shared_ptr<BVHNode> left, std::shared_ptr<BVHNode> right);

  std::optional<Intersection> intersect(const Ray &ray, float minDepth, float maxDepth) const;

  std::shared_ptr<Object> getObject() const;

  BoundingBox getBoundingBox() const;

  std::shared_ptr<BVHNode> left;
  std::shared_ptr<BVHNode> right;

private:
  BoundingBox box;
  std::shared_ptr<Object> object;
};

#endif // BVHNODE_H
