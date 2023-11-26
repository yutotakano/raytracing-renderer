#include "triangle.h"
#include <limits>

const float EPSILON = std::numeric_limits<float>::epsilon();

Triangle::Triangle(Point3f v0, Point3f v1, Point3f v2, std::optional<Material> material) : Object(material), v0(v0), v1(v1), v2(v2)
{
}

Triangle Triangle::fromJson(const nlohmann::json &json_data)
{
  Point3f v0 = Point3f(0.f, 0.f, 0.f);
  Point3f v1 = Point3f(0.f, 0.f, 0.f);
  Point3f v2 = Point3f(0.f, 0.f, 0.f);

  if (json_data.find("v0") != json_data.end())
  {
    v0 = json_data["v0"];
  }
  if (json_data.find("v1") != json_data.end())
  {
    v1 = json_data["v1"];
  }
  if (json_data.find("v2") != json_data.end())
  {
    v2 = json_data["v2"];
  }

  std::optional<Material> material;
  if (json_data.contains("material"))
  {
    material = Material::fromJson(json_data["material"]);
  }

  return Triangle(v0, v1, v2, material);
}

std::optional<Intersection> Triangle::intersect(const Ray ray, float minDepth, float maxDepth) const
{
  Vector3f edge1 = v1 - v0;
  Vector3f edge2 = v2 - v0;
  Vector3f h = ray.direction.cross(edge2);
  float a = edge1.dot(h);

  if (a > -EPSILON && a < EPSILON)
  {
    return std::nullopt;
  }

  float f = 1.f / a;
  Vector3f s = ray.origin - v0;
  float u = f * s.dot(h);

  if (u < 0.f || u > 1.f)
  {
    return std::nullopt;
  }

  Vector3f q = s.cross(edge1);
  float v = f * ray.direction.dot(q);

  if (v < 0.f || u + v > 1.f)
  {
    return std::nullopt;
  }

  float t = f * edge2.dot(q);

  if (t > EPSILON && t >= minDepth && t <= maxDepth)
  {
    Point3f intersection_point = ray.origin + ray.direction * t;
    Vector3f normal = edge1.cross(edge2).normalized();

    // Calculate the third barycentric coordinate
    float w = 1 - u - v;

    // Interpolate the UV coordinates of the vertices
    float u_uv = w * u + u * u + v * u;
    float v_uv = w * v + u * v + v * v;

    Intersection i
      {
        .distance = t,
        .point = intersection_point,
        .normal = normal,
        .uv = Point2f(u_uv, v_uv),
      };

    return i;
  }

  return std::nullopt;
}
