#ifndef TONEMAPPER_H
#define TONEMAPPER_H

#include "vector.h"

extern const Matrix3f odt_to_rgb;

/**
 * @brief Represents a tonemapper that brings [0, inf] values to [0, 1].
 */
class Tonemapper
{
public:
  /**
   * @brief Applies a linear tonemapping function to a given value.
   * @param value The color to tonemap.
   * @param exposure The exposure value.
   * @return The tonemapped color.
  */
  static Color3f tonemapLinear(Color3f value, float exposure);

  /**
   * @brief Applies a modified ACES tonemapping function to a given value.
   * @param value The color to tonemap.
   * @param exposure The exposure value.
   * @return The tonemapped color.
   */
  static Color3f tonemapACESFitted(Color3f value, float exposure);

  
};

#endif // TONEMAPPER_H
