#include "path.h"
#include "../ray.h"
#include "../intersection.h"
#include "../scene.h"
#include "../lights/arealight.h"
#include <iostream>

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
  return this->traceRayRecursive(scene, ray, minDepth, maxDepth, sampler, 0);
}

Color3f Path::traceRayRecursive(const Scene &scene, const Ray &ray, float minDepth, float maxDepth, Random &sampler, int depth) const
{
  // If we've reached the maximum number of bounces, stop
  if (depth > bounceCount)
  {
    return Color3f(0.f, 0.f, 0.f);
  }

  std::optional<Intersection> intersection = scene.intersect(ray, minDepth, maxDepth);

  if (!intersection.has_value())
  {
    return scene.getBackgroundColor();
  }

  // If the ray hit a surface, sample the next ray direction using the BSDF
  // to sample over the hemisphere. If the Material isn't a complex BSDF,
  // just treat is as Lambertian.
  const std::optional<Material> mat = intersection->object->material;
  if (!mat.has_value())
  {
    return Color3f(0.f, 0.f, 0.f);
  }

  Color3f bsdfSamplingColor = Color3f(0.f, 0.f, 0.f);
  float bsdfSamplingPdf = 0.f;
  Color3f lightSamplingColor = Color3f(0.f, 0.f, 0.f);
  float lightSamplingPdf = 0.f;

  // ----------------------------------------------------
  // Multiple Importance Sampling: BSDF Sampling
  // ----------------------------------------------------
  
  // Find wo in the coordinate system of the surface
  Vector3f wo = ray.direction * -1.f;
  std::tuple<Vector3f, Vector3f, Vector3f> coordinateSystem = this->coordinateSystem(intersection->normal);
  Vector3f woLocal = toLocal(wo, coordinateSystem);

  // Find the BSDF, PDF, and wiLocal
  std::tuple<Color3f, float, Vector3f> sampledBSDF = mat->sample(woLocal, intersection->uv, sampler);
  Color3f brdf = std::get<0>(sampledBSDF);
  float pdf = std::get<1>(sampledBSDF);
  Vector3f wiLocal = std::get<2>(sampledBSDF);

  // Convert wiLocal to wi in world space
  Vector3f wi = toWorld(wiLocal, coordinateSystem);

  // Update the ray and recurse
  Ray newRay = Ray(intersection->point + intersection->normal * 0.0001f, wi);
  Color3f incomingColor = traceRayRecursive(scene, newRay, minDepth, maxDepth, sampler, depth + 1);
  bsdfSamplingColor = brdf * incomingColor * std::abs(wi.dot(intersection->normal));
  bsdfSamplingPdf = pdf;

  // ----------------------------------------------------
  // Multiple Importance Sampling: Light Sampling
  // ----------------------------------------------------

  const auto& light = scene.getLights()[sampler.getInt(0, scene.getLights().size())];
  float distance = (light->getPosition() - intersection->point).length();
  Vector3f wiLight = (light->getPosition() - intersection->point).normalized();
  Vector3f wiLightLocal = toLocal(wiLight, coordinateSystem);

  // Check if the light is visible
  Ray shadowRay = Ray(intersection->point + intersection->normal * 0.0001f, wiLight);
  std::optional<Intersection> shadowIntersection = scene.intersect(shadowRay, 0.0001f, distance);
  // Evaluate the light source
  std::tuple<Color3f, float> lightBSDF = mat->eval(wiLightLocal, woLocal, intersection->uv);
  lightSamplingPdf = 1.f / (scene.getLights().size() * distance * distance);
  lightSamplingColor = std::get<0>(lightBSDF) * light->getIntensity() * std::abs(wi.dot(intersection->normal));
  
  if (shadowIntersection.has_value())
  {
    // If the light is not visible, set the color to black
    lightSamplingColor = Color3f(0.f, 0.f, 0.f);
  }

  // ----------------------------------------------------
  // Multiple Importance Sampling: Weighting
  // ----------------------------------------------------

  // Compute the weight for the BSDF sampling
  float bsdfSamplingWeight = 1.f;
  if (bsdfSamplingPdf > 0.f)
  {
    bsdfSamplingWeight = (bsdfSamplingPdf * bsdfSamplingPdf) / (bsdfSamplingPdf * bsdfSamplingPdf + lightSamplingPdf * lightSamplingPdf);
  }

  // Compute the weight for the light sampling
  float lightSamplingWeight = 1.f;
  if (lightSamplingPdf > 0.f)
  {
    lightSamplingWeight = (lightSamplingPdf * lightSamplingPdf) / (bsdfSamplingPdf * bsdfSamplingPdf + lightSamplingPdf * lightSamplingPdf);
  }

  // ----------------------------------------------------
  // Multiple Importance Sampling: Final Color
  // ----------------------------------------------------

  Color3f finalColor = mat->emittance + bsdfSamplingColor * bsdfSamplingWeight + lightSamplingColor * lightSamplingWeight;
  return finalColor;
}

std::tuple<Vector3f, Vector3f, Vector3f> Path::coordinateSystem(const Vector3f &normal) const
{
  // Find the tangent and bitangent vectors for the coordinate system
  Vector3f tangent = Vector3f(1, 0, 0);
  if (std::abs(normal.x()) > std::abs(normal.y()))
  {
    tangent = Vector3f(0, 1, 0);
  }
  Vector3f bitangent = normal.cross(tangent).normalized();
  tangent = bitangent.cross(normal).normalized();

  // Return the coordinate system as a matrix
  return std::make_tuple(tangent, bitangent, normal);
}

Vector3f Path::toLocal(const Vector3f &v, std::tuple<Vector3f, Vector3f, Vector3f> coordinateSystem) const
{
  return Vector3f(
    std::get<0>(coordinateSystem).dot(v),
    std::get<1>(coordinateSystem).dot(v),
    std::get<2>(coordinateSystem).dot(v)
  );
}

Vector3f Path::toWorld(const Vector3f &v, std::tuple<Vector3f, Vector3f, Vector3f> coordinateSystem) const
{
  return Vector3f(
    std::get<0>(coordinateSystem).dot(v),
    std::get<1>(coordinateSystem).dot(v),
    std::get<2>(coordinateSystem).dot(v)
  );
}
