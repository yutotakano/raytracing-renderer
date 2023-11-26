#ifndef TEXTURE_H
#define TEXTURE_H

#include "../vector.h"

/**
 * @brief A texture map.
 */
class TextureMap
{
public:
  TextureMap(std::vector<Color3f> data, Point2f size);

  /**
   * @brief Get the color at the given UV coordinates.
   * 
   * @param uv The UV coordinates.
   * @return Color3f The color at the given UV coordinates.
   */
  Color3f getColorAtUV(Point2f uv) const;

private:
  Point2f size;
  std::vector<Color3f> data;
};

#endif // TEXTURE_H
