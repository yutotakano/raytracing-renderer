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

  // First add ambient light, which we estimate as the diffuse color multiplied
  // by the background color element-wise
  Color3f color = intersection->object->material->diffuseColor * scene.getBackgroundColor();

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

    // For diffuse color, we use the object's diffuse color only if there is no
    // texture, otherwise we use the texture color at the intersection point
    Color3f diffuse_color = intersection->object->material->diffuseColor;
    if (intersection->object->material->texture.has_value()) {
      
      diffuse_color = intersection->object->material->texture->getColorAtUV(intersection->uv);
    }
    float diffuse_intensity = std::max(intersection->normal.dot(light_direction), 0.0f);

    float ks = intersection->object->material->ks;
    float kd = intersection->object->material->kd;

    // Blinn-Phong light intensity needs to be scaled by the inverse square of
    // the distance to the light source for realistic falloff (this is not
    // physically accurate, but neither is the Blinn-Phong model to begin with)
    float distanceSquared = std::pow((light->position - intersection->point).length(), 2);

    color += (specular_color * std::pow(specular_intensity, specular_power) * ks + diffuse_color * diffuse_intensity * kd) * light->intensity / distanceSquared;
  }

  return color;
}
