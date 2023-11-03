#ifndef LIGHT_H
#define LIGHT_H

#include <json/json.hpp>
#include "vector.h"

class Light
{
public:
  static Light fromJson(const nlohmann::json &json_data);

  Vector3f position;
  Vector3f intensity;
};

#endif // LIGHT_H
