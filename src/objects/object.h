#ifndef OBJECT_H
#define OBJECT_H

#include <optional>
#include <json/json.hpp>
#include "material.h"
#include "../vector.h"
#include "../intersection.h"
#include "../ray.h"

/**
 * @brief Abstract class representing an object in the scene.
 */
class Object
{
public:
  Object(std::optional<Material> material);
  virtual ~Object() = default;

  static std::unique_ptr<Object> fromJson(const nlohmann::json &json_data);

  /**
   * @brief Intersect the object with a ray.
   * 
   * @param ray The ray to intersect with.
   * @return std::optional<Intersection> The intersection with the object, if any.
   */
  virtual std::optional<Intersection> intersect(const Ray ray, float minDepth, float maxDepth) const = 0;

  std::optional<Material> material;
};

#endif // OBJECT_H
