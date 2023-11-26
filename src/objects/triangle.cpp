#include "triangle.h"
#include <limits>

const float EPSILON = std::numeric_limits<float>::epsilon();

Triangle::Triangle(Point3f v0, Point3f v1, Point3f v2, std::optional<Material> material) : Object(material), v0(v0), v1(v1), v2(v2)
{
}

Triangle::Triangle(Point3f v0, Point3f v1, Point3f v2, Point3f uv0, Point3f uv1, Point3f uv2, std::optional<Material> material) : Object(material), v0(v0), v1(v1), v2(v2), uv0(uv0), uv1(uv1), uv2(uv2)
{
}

Triangle::Triangle(Point3f v0, Point3f v1, Point3f v2, Point3f uv0, Point3f uv1, Point3f uv2, Vector3f n0, Vector3f n1, Vector3f n2, std::optional<Material> material) : Object(material), v0(v0), v1(v1), v2(v2), uv0(uv0), uv1(uv1), uv2(uv2), n0(n0), n1(n1), n2(n2)
{
}

Triangle Triangle::fromJson(const nlohmann::json &json_data)
{
  Point3f v0 = Point3f(0.f, 0.f, 0.f);
  Point3f v1 = Point3f(0.f, 0.f, 0.f);
  Point3f v2 = Point3f(0.f, 0.f, 0.f);

  Point3f uv0 = Point3f(0.f, 0.f, 0.f);
  Point3f uv1 = Point3f(0.f, 0.f, 0.f);
  Point3f uv2 = Point3f(0.f, 0.f, 0.f);

  Vector3f n0 = Vector3f(0.f, 0.f, 0.f);
  Vector3f n1 = Vector3f(0.f, 0.f, 0.f);
  Vector3f n2 = Vector3f(0.f, 0.f, 0.f);

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
  

  if (json_data.find("uv0") != json_data.end() &&
      json_data.find("uv1") != json_data.end() &&
      json_data.find("uv2") != json_data.end())
  {
    uv0 = json_data["uv0"];
    uv1 = json_data["uv1"];
    uv2 = json_data["uv2"];

    if (json_data.find("n0") != json_data.end() &&
        json_data.find("n1") != json_data.end() &&
        json_data.find("n2") != json_data.end())
    {
      n0 = json_data["n0"];
      n1 = json_data["n1"];
      n2 = json_data["n2"];
      return Triangle(v0, v1, v2, uv0, uv1, uv2, n0, n1, n2, material);
    }

    return Triangle(v0, v1, v2, uv0, uv1, uv2, material);
  }

  return Triangle(v0, v1, v2, material);
}

std::optional<Intersection> Triangle::intersect(const Ray &ray, float minDepth, float maxDepth) const
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
    Vector3f normal;
    float u_uv, v_uv;

    if (uv0.has_value() && uv1.has_value() && uv2.has_value() &&
        n0.has_value() && n1.has_value() && n2.has_value())
    {
      // This whole block generated from prompt:
      // Interpolate vertex normals and UV coordinates using uv0 (uvw for vertex 0), uv1 (uvw for vertex 1) and uv2 (uvw for vertex 2) and n0 to n2. Output should be intersection with Point2f uv
      normal = (n0.value() * (1 - u - v) + n1.value() * u + n2.value() * v).normalized();

      // Interpolate the UV coordinates of the vertices
      u_uv = (uv0.value().x() * (1 - u - v) + uv1.value().x() * u + uv2.value().x() * v);
      v_uv = (uv0.value().y() * (1 - u - v) + uv1.value().y() * u + uv2.value().y() * v);
    }
    else 
    {
      normal = edge1.cross(edge2).normalized();
      // Calculate the third barycentric coordinate
      float w = 1 - u - v;

      // Interpolate the UV coordinates of the vertices
      u_uv = w * u + u * u + v * u;
      v_uv = w * v + u * v + v * v;
    }

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

BoundingBox Triangle::getBoundingBox() const
{
  float min_x = std::min(v0.x(), std::min(v1.x(), v2.x()));
  float min_y = std::min(v0.y(), std::min(v1.y(), v2.y()));
  float min_z = std::min(v0.z(), std::min(v1.z(), v2.z()));

  float max_x = std::max(v0.x(), std::max(v1.x(), v2.x()));
  float max_y = std::max(v0.y(), std::max(v1.y(), v2.y()));
  float max_z = std::max(v0.z(), std::max(v1.z(), v2.z()));

  return BoundingBox(Point3f(min_x, min_y, min_z), Point3f(max_x, max_y, max_z));
}
