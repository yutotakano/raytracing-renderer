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

  Color3f traceRay(const Scene scene, const Ray ray, float minDepth, float maxDepth) const override;
};

#endif // PHONG_H
