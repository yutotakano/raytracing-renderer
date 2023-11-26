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
  // Infinite Cylinder equation:
  // || (p - c) - ((p - c) . a) * a || = r
  // where:
  //   p is a point on the cylinder
  //   c is the center of the cylinder
  //   a is the axis of the cylinder
  //   r is the radius of the cylinder
  //
  // Just cap the projection of (p - c) onto a to the height of the cylinder
  // to get a capped cylinder. (and then also check for intersections with the
  // caps)

  // Check if the ray intersects with the caps of the cylinder

  // Bottom Cap
  float t_cap1 = (center - axis * height - ray.origin).dot(axis) / ray.direction.dot(axis);
  if (t_cap1 > minDepth && t_cap1 < maxDepth)
  {
    Point3f intersection_point = ray.origin + ray.direction * t_cap1;
    float distance_squared = (intersection_point - center).dot(intersection_point - center);
    if (distance_squared <= radius * radius)
    {
      Intersection i
        {
          .distance = t_cap1,
          .point = intersection_point,
          .normal = (axis * -1.f).normalized()
        };

      return i;
    }
  }

  // Top Cap
  float t_cap2 = (center + axis * height - ray.origin).dot(axis) / ray.direction.dot(axis);
  if (t_cap2 > minDepth && t_cap2 < maxDepth)
  {
    Point3f intersection_point = ray.origin + ray.direction * t_cap2;
    float distance_squared = (intersection_point - center - axis * height).dot(intersection_point - center - axis * height);
    if (distance_squared <= radius * radius)
    {
      Intersection i
        {
          .distance = t_cap2,
          .point = intersection_point,
          .normal = axis.normalized()
        };

      return i;
    }
  }

  // Calculate the vector from the ray origin to the center of the cylinder
  Vector3f oc = ray.origin - center;

  // Calculate the coefficients for the quadratic equation.
  float A = ray.direction.dot(ray.direction) - pow(ray.direction.dot(axis), 2);
  float B = 2.0f * (ray.direction.dot(oc) - ray.direction.dot(axis) * oc.dot(axis));
  float C = oc.dot(oc) - pow(oc.dot(axis), 2) - radius * radius;

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
            .normal = (intersection_point - center - (axis * projected_y)).normalized()
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
            .normal = (intersection_point - center - (axis * projected_y)).normalized()
          };

        return i;
      }
    }
  }

  return std::nullopt;
}

