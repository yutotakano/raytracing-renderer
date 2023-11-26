#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include <optional>
#include "../vector.h"
#include "../intersection.h"
#include "../ray.h"

class BoundingBox
{
public:
  BoundingBox(Point3f min, Point3f max);

  BoundingBox merge(const BoundingBox &other) const;

  std::optional<Intersection> intersect(const Ray &ray, float minDepth, float maxDepth) const;

  Point3f getMin() const;
  Point3f getMax() const;
  Point3f getCenter() const;

private:
  Point3f min;
  Point3f max;
};

#endif // BOUNDINGBOX_H
