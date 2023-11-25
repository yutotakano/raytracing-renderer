#include "phong.h"
#include "../ray.h"
#include "../intersection.h"
#include "../scene.h"

Phong::Phong(int bounces) : Tracer()
{
}

Phong Phong::fromJson(const nlohmann::json &json_data)
{
  // By default just once bounce
  int nbounces = 1;
  if (json_data.contains("nbounces"))
  {
    nbounces = json_data["nbounces"];
  }

  return Phong(nbounces);
}

Color3f Phong::traceRay(const Scene scene, Ray ray, float minDepth, float maxDepth) const
{
  // Find closest intersection with an object in the scene
  std::optional<Intersection> intersection = scene.intersect(ray, minDepth, maxDepth);

  // If no intersection, return background color with infinite depth
  if (!intersection.has_value())
  {
    return scene.getBackgroundColor();
  }

  // Calculate color at intersection point using Blinn-Phong shading model
  Color3f color = Color3f(0.f, 0.f, 0.f);
  for (const auto& light : scene.getLights()) {
    // Check if the light is blocked
    Ray shadow_ray = Ray(intersection->point + intersection->normal * 1.f, light->position - intersection->point);
    std::optional<Intersection> shadow_intersection = scene.intersect(shadow_ray, 0.f, 1000.f);
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
    Color3f diffuse_color = intersection->object->material->diffuseColor;
    Color3f ambient_color = Color3f(0.25f, 0.25f, 0.25f); // intersection->object->material->ambientColor;
    float ambient_intensity = 1.f; // intersection->object->material->ambientIntensity;
    float diffuse_intensity = std::max(intersection->normal.dot(light_direction), 0.0f);

    float ks = intersection->object->material->ks;
    float kd = intersection->object->material->kd;

    color += (ambient_color * ambient_intensity + specular_color * std::pow(specular_intensity, specular_power) * ks + diffuse_color * diffuse_intensity * kd) * light->intensity;
  
  }

  return color;
}
