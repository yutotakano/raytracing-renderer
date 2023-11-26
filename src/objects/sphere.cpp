#include "sphere.h"

Sphere::Sphere(Point3f center, float radius, std::optional<Material> material) : Object(material), center(center), radius(radius)
{
}

Sphere Sphere::fromJson(const nlohmann::json &json_data)
{
  Point3f center = Point3f(0.f, 0.f, 0.f);
  float radius = 1.f;

  if (json_data.contains("center"))
  {
    center = json_data["center"];
  }
  if (json_data.contains("radius"))
  {
    radius = json_data["radius"];
  }

  std::optional<Material> material;
  if (json_data.contains("material"))
  {
    material = Material::fromJson(json_data["material"]);
  }

  return Sphere(center, radius, material);
}

std::optional<Intersection> Sphere::intersect(const Ray ray, float minDepth, float maxDepth) const
{
  Vector3f oc = ray.origin - center;
  float a = ray.direction.dot(ray.direction);
  float b = 2.f * oc.dot(ray.direction);
  float c = oc.dot(oc) - radius * radius;
  float discriminant = b * b - 4.f * a * c;

  if (discriminant < 0.f)
  {
    return std::nullopt;
  }

  float t = (-b - std::sqrt(discriminant)) / (2.f * a);
  if (t < 0.f)
  {
    t = (-b + std::sqrt(discriminant)) / (2.f * a);
  }
  if (t < 0.f)
  {
    return std::nullopt;
  }

  Point3f intersection_point = ray.origin + ray.direction * t;
  Vector3f normal = (intersection_point - center).normalized();

  Intersection i
    {
      .distance = t,
      .point = intersection_point,
      .normal = normal,
      .uv = Point2f(0.5 + std::atan2(normal.z(), normal.x()) / (2 * M_PI), 0.5 - std::asin(normal.y()) / M_PI)
    };
  return i;
}
