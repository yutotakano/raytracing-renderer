#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <json/json.hpp>
#include "objects/object.h"
#include "cameras/camera.h"
#include "lights/light.h"
#include "vector.h"
#include "ray.h"
#include "intersection.h"
#include "bvh.h"

/**
 * @brief Represents a scene, containing objects and lights. Includes an
 * acceleration structure for fast ray tracing, as well as methods for testing
 * intersections.
 */
class Scene
{
public:
  Scene();
  static Scene fromJson(const nlohmann::json &json_data);

  /**
   * @brief Add an object to the scene.
   * @param object Shared pointer to the object (so that it isn't copied unnecessarily)
   */
  void addObject(std::shared_ptr<Object> object);

  /**
   * @brief Add a light to the scene.
   * @param object Shared pointer to the light (so that it isn't copied unnecessarily)
   */
  void addLight(std::shared_ptr<Light> light);

  /**
   * @brief Build the Bounding Volume Hierarchy for the scene, for fast
   * ray-scene intersection checks. Must be called after all objects have been
   * added to the scene.
   */
  void buildBVH();

  /**
   * @brief Intersect a ray with the scene, returning the closest intersection.
   * The intersection will have a hit value of false if the ray did not find
   * anything.
   * @param ray Camera ray
   * @param minDepth Minimum ray length for intersection checks
   * @param maxDepth Maximum ray length for intersection checks
   * @return Optional intersection object
   */
  std::optional<Intersection> intersect(const Ray ray, float minDepth, float maxDepth) const;

  /**
   * @brief Get the background color of the scene.
   * @return Color3f object
   */
  Color3f getBackgroundColor() const;

private:
  Color3f background_color;
  std::vector<std::shared_ptr<Object>> objects;
  std::vector<std::shared_ptr<Light>> lights;

  std::optional<BVH> bvh;
};

#endif // SCENE_H
