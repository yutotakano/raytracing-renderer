#ifndef RAY_H
#define RAY_H

#include "vector.h"

class Ray {
public:
  // A ray is defined by its origin and direction
  Vector3f origin; // origin
  Vector3f direction; // direction
};

#endif // RAY_H
