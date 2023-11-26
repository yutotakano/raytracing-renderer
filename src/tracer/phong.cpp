#include "phong.h"
#include "../ray.h"
#include "../intersection.h"
#include "../scene.h"
#include <iostream>

Phong::Phong(int bounceCount) : Tracer(1), bounceCount(bounceCount)
{
}

Phong Phong::fromJson(const nlohmann::json &json_data)
{
  // By default just once bounce
  int bounceCount = 1;
  if (json_data.contains("nbounces"))
  {
    bounceCount = json_data["nbounces"];
  }
  return Phong(bounceCount);
}

Color3f Phong::traceRay(const Scene &scene, const Ray &ray, float minDepth, float maxDepth) const
{
  return traceRayRecursive(scene, ray, minDepth, maxDepth, 0);
}

Color3f Phong::traceRayRecursive(const Scene &scene, const Ray &ray, float minDepth, float maxDepth, int bounce) const
{
  // Abort early if we've reached the maximum number of bounces already
  if (bounce > bounceCount)
  {
    return scene.getBackgroundColor();
  }

  // Find closest intersection with an object in the scene
  std::optional<Intersection> intersection = scene.intersect(ray, minDepth, maxDepth);

  // If no intersection, return background color with infinite depth
  if (!intersection.has_value())
  {
    return scene.getBackgroundColor();
  }

  // Calculate color at intersection point using Blinn-Phong shading model

  // For diffuse color (used for ambient light too, so pre-calculated), we use
  // the object's diffuse color only if there is no texture, otherwise we use
  // the texture color at the intersection point
  Color3f diffuse_color = intersection->object->material->diffuseColor;
  if (intersection->object->material->texture.has_value()) {
    diffuse_color = intersection->object->material->texture->getColorAtUV(intersection->uv);
  }

  // First add ambient light, which we estimate as the diffuse color multiplied
  // by the background color element-wise
  Color3f color = diffuse_color * scene.getBackgroundColor();

  // Loop through all lights in the scene and add their contribution
  for (const auto& light : scene.getLights()) {
    // Check if the light is blocked, if so ignore it. The shadow ray is cast
    // from a slightly offset point (using the normal) to avoid self-intersection.
    Ray shadow_ray = Ray(intersection->point + intersection->normal * 0.0001f, light->position - intersection->point);
    std::optional<Intersection> shadow_intersection = scene.intersect(shadow_ray, 0.f, 1000.f);

    // Make sure the shadow ray intersection was closer than the light
    if (shadow_intersection.has_value() && shadow_intersection->distance < (light->position - intersection->point).length()) {
      continue;
    }

    // Calculate Blinn-Phong shading contribution
    Vector3f light_direction = (light->position - intersection->point).normalized();
    Vector3f view_direction = ray.direction.normalized() * -1.f;
    Vector3f half_vector = (light_direction + view_direction).normalized();
    float specular_intensity = std::max(intersection->normal.dot(half_vector), 0.0f);
    float specular_power = intersection->object->material->specularExponent;
    Color3f specular_color = intersection->object->material->specularColor;
    float diffuse_intensity = std::max(intersection->normal.dot(light_direction), 0.0f);

    float ks = intersection->object->material->ks;
    float kd = intersection->object->material->kd;

    // Blinn-Phong light intensity needs to be scaled by the inverse square of
    // the distance to the light source for realistic falloff (this is not
    // physically accurate, but neither is the Blinn-Phong model to begin with)
    float distanceSquared = std::pow((light->position - intersection->point).length(), 2);

    color += (specular_color * std::pow(specular_intensity, specular_power) * ks + diffuse_color * diffuse_intensity * kd) * light->intensity / distanceSquared;
  }

  // Add refraction contribution
  if (intersection->object->material->isRefractive && bounce < bounceCount)
  {
    // Calculate the refracted ray direction, adapted from:
    // https://paulbourke.net/geometry/reflected/
    float n1 = 1.f;
    float n2 = intersection->object->material->refractiveIndex;
    Vector3f normal = intersection->normal;
    if (ray.direction.dot(intersection->normal) > 0.f)
    {
      // Ray is from inside the object, so we need to flip the normal and swap
      // the refractive indices
      std::swap(n1, n2);
      normal = intersection->normal * -1.f;
    }
    float n = n1 / n2;
    float cosI = -normal.dot(ray.direction);
    float sinT2 = n * n * (1.0 - cosI * cosI);
    if (sinT2 > 1.0)
    {
      // Total internal reflection
      return color;
    }

    float cosT = std::sqrt(1.0 - sinT2);
    Vector3f refracted_ray_direction = ray.direction * n + normal * (n * cosI - cosT);

    // Recursively find the refracted ray color until we reach the maximum
    // number of bounces
    Color3f refracted_ray_color = traceRayRecursive(scene, Ray(intersection->point - normal * 0.0001f, refracted_ray_direction), 0.f, 1000.f, bounce + 1);

    // Add the refracted ray color to the current color
    color = refracted_ray_color;
  }

  // Add reflection contribution
  if (intersection->object->material->isReflective)
  {
    // Calculate the reflected ray direction, adapted from:
    // https://paulbourke.net/geometry/reflected/
    Vector3f reflected_ray_direction = ray.direction - intersection->normal * 2.f * ray.direction.dot(intersection->normal);

    Vector3f normal = intersection->normal;
    if (ray.direction.dot(intersection->normal) > 0.f)
    {
      // Ray is from inside the object, so we need to flip the normal and swap
      // the refractive indices
      normal = intersection->normal * -1.f;
    }

    // Recursively find the reflected ray color until we reach the maximum
    // number of bounces
    Color3f reflected_ray_color = traceRayRecursive(scene, Ray(intersection->point + intersection->normal * 0.0001f, reflected_ray_direction), 0.f, 1000.f, bounce + 1);

    // We could add the reflected ray color to the current color, but this will
    // result in very unrealistic bright reflectance surfaces. Instead, we
    // combine the Blinn-Phong color and the refletance color with weights.
    color = color * (1.0f - intersection->object->material->reflectivity) + reflected_ray_color * intersection->object->material->reflectivity;
  }

  return color;
}
