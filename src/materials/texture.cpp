#include "texture.h"

TextureMap::TextureMap(std::vector<Color3f> data, Point2f size) : size(size), data(data)
{
}

Color3f TextureMap::getColorAtUV(Point2f uv) const
{
  // Multiply uv to be within imageSize
  uv.set_x(fmod(uv.x() * size.x(), size.x()));
  uv.set_y(fmod(uv.y() * size.y(), size.y()));
  
  // Wrap around if negative values are passed in
  if (uv.x() < 0)
    uv.set_x(uv.x() + size.x());
  if (uv.y() < 0)
    uv.set_y(uv.y() + size.y());
  
  // Find the nearest pixel
  int pixelX = static_cast<int>(uv.x());
  int pixelY = static_cast<int>(uv.y());
  
  // Return the color of the nearest pixel
  return data[pixelY * size.x() + pixelX];
}
