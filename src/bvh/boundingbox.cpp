#include "boundingbox.h"
#include <iostream>

BoundingBox::BoundingBox(Point3f min, Point3f max) : min(min), max(max)
{
}

BoundingBox BoundingBox::merge(const BoundingBox &other) const
{
  return BoundingBox(
    Point3f(
      std::min(min.x(), other.min.x()),
      std::min(min.y(), other.min.y()),
      std::min(min.z(), other.min.z())
    ),
    Point3f(
      std::max(max.x(), other.max.x()),
      std::max(max.y(), other.max.y()),
      std::max(max.z(), other.max.z())
    )
  );
}

std::optional<Intersection> BoundingBox::intersect(const Ray &ray, float minDepth, float maxDepth) const
{
  float tmin, tmax;
  if (ray.direction.x() != 0)
  {
    tmin = (min.x() - ray.origin.x()) / ray.direction.x();
    tmax = (max.x() - ray.origin.x()) / ray.direction.x();

    if (tmin > tmax)
    {
      std::swap(tmin, tmax);
    }
  }
  else
  {
    if (ray.origin.x() < min.x() || ray.origin.x() > max.x())
    {
      return std::nullopt;
    }
    tmin = -std::numeric_limits<float>::infinity();
    tmax = std::numeric_limits<float>::infinity();
  }

  float tymin, tymax;
  if (ray.direction.y() != 0)
  {
    tymin = (min.y() - ray.origin.y()) / ray.direction.y();
    tymax = (max.y() - ray.origin.y()) / ray.direction.y();

    if (tymin > tymax)
    {
      std::swap(tymin, tymax);
    }
  }
  else
  {
    if (ray.origin.y() < min.y() || ray.origin.y() > max.y())
    {
      return std::nullopt;
    }
    tymin = -std::numeric_limits<float>::infinity();
    tymax = std::numeric_limits<float>::infinity();
  }

  if ((tmin > tymax) || (tymin > tmax))
  {
    return std::nullopt;
  }

  if (tymin > tmin)
  {
    tmin = tymin;
  }

  if (tymax < tmax)
  {
    tmax = tymax;
  }

  float tzmin, tzmax;
  if (ray.direction.z() != 0)
  {
    tzmin = (min.z() - ray.origin.z()) / ray.direction.z();
    tzmax = (max.z() - ray.origin.z()) / ray.direction.z();

    if (tzmin > tzmax)
    {
      std::swap(tzmin, tzmax);
    }
  }
  else
  {
    if (ray.origin.z() < min.z() || ray.origin.z() > max.z())
    {
      return std::nullopt;
    }
    tzmin = -std::numeric_limits<float>::infinity();
    tzmax = std::numeric_limits<float>::infinity();
  }

  if ((tmin > tzmax) || (tzmin > tmax))
  {
    return std::nullopt;
  }

  if (tzmin > tmin)
  {
    tmin = tzmin;
  }

  if (tzmax < tmax)
  {
    tmax = tzmax;
  }

  if (tmin < maxDepth && tmax > minDepth)
  {
    Intersection i
      {
        .distance = tmin,
        .point = ray.origin + ray.direction * tmin,
        .normal = (ray.origin + ray.direction * tmin - getCenter()).normalized(),
        .object = nullptr
      };
    return i;
  }
  else
  {
    return std::nullopt;
  }
}

Point3f BoundingBox::getMin() const
{
  return min;
}

Point3f BoundingBox::getMax() const
{
  return max;
}

Point3f BoundingBox::getCenter() const
{
  return (min + max) / 2;
}
