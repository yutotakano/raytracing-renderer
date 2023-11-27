#ifndef LIGHT_H
#define LIGHT_H

#include <json/json.hpp>
#include "../vector.h"

class Light
{
public:
  Light(Point3f position, Color3f intensity);

  static Light fromJson(const nlohmann::json &json_data);

  Point3f getPosition() const { return position; }
  Color3f getIntensity() const { return intensity; }

private:
  Vector3f position;
  Vector3f intensity;
};

#endif // LIGHT_H
