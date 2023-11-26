#ifndef BINARY_H
#define BINARY_H

#include "tracer.h"

/**
 * @brief Tracer that outputs a single color (red) for intersections.
 */
class Binary : public Tracer
{
public:
  Binary();
  static Binary fromJson(const nlohmann::json &json_data);

  Color3f traceRay(const Scene &scene, const Ray &ray, float minDepth, float maxDepth) const override;
};

#endif // BINARY_H
