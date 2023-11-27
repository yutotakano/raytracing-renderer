#ifndef RANDOM_H
#define RANDOM_H

#include "vector.h"

class Random
{
public:
  Random();
  
  /**
   * @brief Get a random float between 0 and 1.
   * @return float A random float between 0 and 1.
   */
  float get1D();

  /**
   * @brief Get a random 2D point between (0, 0) and (1, 1).
   * @return Point2f A random 2D point between (0, 0) and (1, 1).
   */
  Point2f get2D();

  /**
   * @brief Get a random integer between [min, max).
   * @param min The minimum value.
   * @param max The maximum value.
   * @return int Integer between [min, max).
  */
  int getInt(int min, int max);
};

#endif // RANDOM_H
