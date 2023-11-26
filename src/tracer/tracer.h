#ifndef TRACER_H
#define TRACER_H

#include <json/json.hpp>
#include "../vector.h"
#include "../scene.h"
#include "../ray.h"

/**
 * @brief Abstract class representing a ray tracer. This class is responsible
 * for integrating the light transport equation along a ray path.
 */
class Tracer
{
public:
  Tracer(int sampleCount);
  virtual ~Tracer() = default;

  static std::unique_ptr<Tracer> fromJson(const nlohmann::json &json_data);

  /**
   * @brief Trace a ray through the scene, returning the final color of the
   * ray. If no intersection is found, the background color is returned.
   * @param scene Scene object
   * @param ray Camera ray
   * @param minDepth Minimum ray length for intersection checks
   * @param maxDepth Maximum ray length for intersection checks
   * @param binary Whether to output a single color for intersections (red)
   * @return Color3f object
   */
  virtual Color3f traceRay(const Scene &scene, const Ray &ray, float minDepth, float maxDepth) const = 0;

  /**
   * @brief Get the number of samples per pixel for this tracer.
   * @return Number of samples per pixel
   */
  int getSampleCount() const { return sampleCount; }

protected:
  int sampleCount;
};

#endif // TRACER_H
