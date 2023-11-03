#ifndef OBJECT_H
#define OBJECT_H

#include "material.h"
#include <optional>
#include "../vector.h"
#include <json/json.hpp>

/**
 * @brief Abstract class representing an object in the scene.
 */
class Object
{
public:
  Object(std::optional<Material> material);
  virtual ~Object() = default;

  static std::unique_ptr<Object> fromJson(const nlohmann::json &json_data);

  std::optional<Material> material;
};

#endif // OBJECT_H
