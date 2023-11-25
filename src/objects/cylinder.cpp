#include "cylinder.h"

Cylinder::Cylinder(Point3f center, Vector3f axis, float radius, float height, std::optional<Material> material) : Object(material), center(center), axis(axis), radius(radius), height(height)
{
}

Cylinder Cylinder::fromJson(const nlohmann::json &json_data)
{
  Point3f center = Point3f(0.f, 0.f, 0.f);
  Vector3f axis = Vector3f(0.f, 1.f, 0.f);
  float radius = 1.f;
  float height = 1.f;

  if (json_data.contains("center"))
  {
    center = json_data["center"];
  }
  if (json_data.contains("axis"))
  {
    axis = json_data["axis"];
  }
  if (json_data.contains("radius"))
  {
    radius = json_data["radius"];
  }
  if (json_data.contains("height"))
  {
    height = json_data["height"];
  }

  std::optional<Material> material;
  if (json_data.contains("material"))
  {
    material = Material::fromJson(json_data["material"]);
  }

  return Cylinder(center, axis, radius, height, material);
}

std::optional<Intersection> Cylinder::intersect(const Ray ray, float minDepth, float maxDepth) const
{
  // Calculate the direction vector of the ray
  Vector3f ray_direction = ray.direction;

  // Calculate the vector from the ray origin to the center of the cylinder
  Vector3f oc = ray.origin - center;

  // Calculate the dot product of the ray direction and the axis of the cylinder
  float a = ray_direction.dot(axis);

  // Calculate the dot product of the oc vector and the axis of the cylinder
  float b = oc.dot(axis);

  // Calculate the coefficients for the quadratic equation
  float A = (ray_direction - axis * a).dot(ray_direction - axis * a);
  float B = 2.0f * (ray_direction - axis * a).dot(oc - axis * b);
  float C = (oc - axis * b).dot(oc - axis * b) - radius * radius;

  // Calculate the discriminant
  float discriminant = B * B - 4.0f * A * C;

  // Check if the ray intersects with the cylinder
  if (discriminant > 0)
  {
    // Calculate the solutions for t
    float t1 = (-B - sqrt(discriminant)) / (2.0f * A);
    float t2 = (-B + sqrt(discriminant)) / (2.0f * A);

    // Check if the solutions are within the valid range
    if (t1 > minDepth && t1 < maxDepth)
    {
      // Calculate the intersection point
      Point3f intersection_point = ray.origin + ray.direction * t1;

      // Project onto the axis of the cylinder
      float projected_y = (intersection_point - center).dot(axis) / axis.dot(axis);

      // Check if the intersection point is within the height of the cylinder
      if (projected_y >= -height && projected_y <= height)
      {
        Intersection i
          {
            .distance = t1,
            .point = intersection_point,
            .normal = (intersection_point - center - axis * b) * (1.0f / radius)
          };

        return i;
      }
    }

    if (t2 > minDepth && t2 < maxDepth)
    {
      // Calculate the intersection point
      Point3f intersection_point = ray.origin + ray.direction * t2;

      // Project onto the axis of the cylinder
      float projected_y = (intersection_point - center).dot(axis) / axis.dot(axis);

      // Check if the intersection point is within the height of the cylinder
      if (projected_y >= -height && projected_y <= height)
      {
        Intersection i
          {
            .distance = t2,
            .point = intersection_point,
            .normal = (intersection_point - center - axis * b) * (1.0f / radius)
          };

        return i;
      }
    }
  }

  return std::nullopt;
}

