#ifndef TONEMAPPER_H
#define TONEMAPPER_H

#include "vector.h"

/**
 * @brief Represents a tonemapper that brings [0, inf] values to [0, 1].
 */
class Tonemapper
{
public:
  /**
   * @brief Applies the tonemapping function to a given value.
   * @param value The color to tonemap.
   * @param exposure The exposure value.
   * @return The tonemapped color.
   */
  static Color3f tonemapACESFitted(Color3f value, float exposure);
};

#endif // TONEMAPPER_H
