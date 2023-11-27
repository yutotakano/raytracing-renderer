#ifndef PATH_H
#define PATH_H

#include "tracer.h"

/**
 * @brief Tracer that implements the Monte-Carlo physically-accurate renderer.
 */
class Path : public Tracer
{
public:
  Path(int bounces, int sampleCount, bool useRussianRoulette);
  static Path fromJson(const nlohmann::json &json_data);

  /**
   * This function is called multiple times per pixel with a slightly different
   * ray each time. The result is averaged by the caller.
   * 
   * The tracer should integrate the light along the ray and perform recursive
   * Monte-Carlo sampling for everywhere the ray can scatter. The maximum bounces
   * is specified by the bounceCount argument, but the actual count might be
   * lower if russian roulette is used.
   * @param scene Scene object
   * @param ray Camera ray
   * @param minDepth Minimum ray length for intersection checks
   * @param maxDepth Maximum ray length for intersection checks
   * @param sampler Random number generator
  */
  Color3f traceRay(const Scene &scene, const Ray &ray, float minDepth, float maxDepth, Random &sampler) const override;

private:
  int bounceCount;
  int sampleCount;
  bool useRussianRoulette;
};

#endif // PATH_H
