#ifndef RAY_H
#define RAY_H

#include "vector.h"

class Ray {
public:
  Ray(Vector3f origin, Vector3f direction) : origin(origin), direction(direction) {};

  // A ray is defined by its origin and direction
  Vector3f origin; // origin
  Vector3f direction; // direction
};

#endif // RAY_H
