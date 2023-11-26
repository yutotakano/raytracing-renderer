#include "bvhnode.h"
#include <iostream>

BVHNode::BVHNode(BoundingBox box, std::shared_ptr<Object> object) : box(box), object(object)
{
}

BVHNode::BVHNode(std::shared_ptr<BVHNode> left, std::shared_ptr<BVHNode> right) : left(left), right(right), box(left->getBoundingBox().merge(right->getBoundingBox()))
{
}

std::optional<Intersection> BVHNode::intersect(const Ray &ray, float minDepth, float maxDepth) const
{
  if (box.intersect(ray, minDepth, maxDepth))
  {
    if (object)
    {
      std::optional<Intersection> i = object->intersect(ray, minDepth, maxDepth);
      if (i.has_value())
      {
        i->object = object;
      }
      return i;
    }
    else
    {
      // If either left or right doesn't exist, complain
      if (!left || !right)
      {
        return std::nullopt;
      }
      std::optional<Intersection> leftIntersection = left->intersect(ray, minDepth, maxDepth);
      std::optional<Intersection> rightIntersection = right->intersect(ray, minDepth, maxDepth);

      if (leftIntersection && rightIntersection)
      {
        if (leftIntersection->distance < rightIntersection->distance)
        {
          return leftIntersection;
        }
        else
        {
          return rightIntersection;
        }
      }
      else if (leftIntersection)
      {
        return leftIntersection;
      }
      else if (rightIntersection)
      {
        return rightIntersection;
      }
      else
      {
        return std::nullopt;
      }
    }
  }
  else
  {
    return std::nullopt;
  }
}

std::shared_ptr<Object> BVHNode::getObject() const
{
  return object;
}

BoundingBox BVHNode::getBoundingBox() const
{
  return box;
}
