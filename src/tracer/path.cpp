#include "path.h"
#include "../ray.h"
#include "../intersection.h"
#include "../scene.h"

Path::Path(int bounceCount, int sampleCount, bool useRussianRoulette) : Tracer(sampleCount), bounceCount(bounceCount), useRussianRoulette(useRussianRoulette)
{
}

Path Path::fromJson(const nlohmann::json &json_data)
{
  // By default just once bounce
  int bounceCount = 1;
  if (json_data.contains("nbounces"))
  {
    bounceCount = json_data["nbounces"];
  }

  // And 64 samples per pixel
  int sampleCount = 64;
  if (json_data.contains("nsamples"))
  {
    sampleCount = json_data["nsamples"];
  }

  bool useRussianRoulette = false;
  if (json_data.contains("russian_roulette"))
  {
    useRussianRoulette = json_data["russian_roulette"];
  }
  
  return Path(bounceCount, sampleCount, useRussianRoulette);
}

Color3f Path::traceRay(const Scene &scene, const Ray &ray, float minDepth, float maxDepth, Random &sampler) const
{

}
