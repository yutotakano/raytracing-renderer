#ifndef OBJECT_H
#define OBJECT_H

#include "material.h"
#include "aliases.h"
#include <json/json.hpp>

class Object
{
public:
  Object(std::optional<Material> material);
  static Object fromJson(const nlohmann::json &json_data);

  std::optional<Material> material;
};

#endif // OBJECT_H
