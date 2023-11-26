#ifndef PATH_H
#define PATH_H

#include "tracer.h"

/**
 * @brief Tracer that implements the Monte-Carlo physically-accurate renderer.
 */
class Path : public Tracer
{
public:
  Path(int bounces, int sampleCount);
  static Path fromJson(const nlohmann::json &json_data);

  Color3f traceRay(const Scene &scene, const Ray &ray, float minDepth, float maxDepth) const override;

private:
  int bounceCount;
  int sampleCount;
};

#endif // PATH_H
