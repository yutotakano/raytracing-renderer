#include "path.h"
#include "../ray.h"
#include "../intersection.h"
#include "../scene.h"

Path::Path(int nbounces, int nsamples) : Tracer(nsamples), nbounces(nbounces)
{
}

Path Path::fromJson(const nlohmann::json &json_data)
{
  // By default just once bounce
  int nbounces = 1;
  if (json_data.contains("nbounces"))
  {
    nbounces = json_data["nbounces"];
  }

  // And 64 samples per pixel
  int nsamples = 64;
  if (json_data.contains("nsamples"))
  {
    nsamples = json_data["nsamples"];
  }
  
  return Path(nbounces, nsamples);
}

Color3f Path::traceRay(const Scene &scene, const Ray &ray, float minDepth, float maxDepth) const
{

}
