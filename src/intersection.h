#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "vector.h"

/**
 * @brief Represents an intersection between a ray and an object.
 */
class Intersection {
public:

  /**
   * @brief Whether the ray hit an object.
   */
  bool hit;

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
};

#endif // INTERSECTION_H
