#ifndef PHONG_H
#define PHONG_H

#include "tracer.h"

/**
 * @brief Tracer that implements the Blinn-Phong illumination model.
 */
class Phong : public Tracer
{
public:
  Phong(int bounces);
  static Phong fromJson(const nlohmann::json &json_data);

  Color3f traceRay(const Scene &scene, const Ray &ray, float minDepth, float maxDepth) const override;

private:

  /**
   * @brief Recursive helper function for traceRay, which adds the bounce arg.
   * @param scene Scene object
   * @param ray Camera ray
   * @param minDepth Minimum ray length for intersection checks
   * @param maxDepth Maximum ray length for intersection checks
   * @param bounce Number of bounces so far
  */
  Color3f traceRayRecursive(const Scene &scene, const Ray &ray, float minDepth, float maxDepth, int bounce) const;

  int nbounces;
};

#endif // PHONG_H
