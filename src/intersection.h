#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "vector.h"

class Object;

/**
 * @brief Represents an intersection between a ray and an object.
 */
class Intersection {
public:
  /**
   * @brief The distance from the ray origin to the intersection point.
   */
  float distance;

  /**
   * @brief The intersection point.
   */
  Point3f point;

  /**
   * @brief The normal vector at the intersection point.
   */
  Vector3f normal;

  /**
   * @brief The object that was intersected.
   */
  std::shared_ptr<Object> object = nullptr;

  /**
   * @brief The local UV coordinates of the intersection point.
   */
  Point2f uv;
};

#endif // INTERSECTION_H
