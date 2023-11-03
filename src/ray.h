#ifndef RAY_H
#define RAY_H

#include "vector.h"

/**
 * @brief Represents a ray in 3D space, defined by its origin and direction.
 */
class Ray {
public:
  Ray(Vector3f origin, Vector3f direction) : origin(origin), direction(direction) {};

  /**
   * @brief Origin of the ray.
   */
  Vector3f origin;

  /**
   * @brief Normalized direction of the ray.
   */
  Vector3f direction; // direction
};

#endif // RAY_H
