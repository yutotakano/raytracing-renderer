#include "mesh.h"
#include "../io/obj.h"

Mesh::Mesh(Point3f center, std::vector<Triangle> triangles, std::optional<Material> material) : Object(material), center(center)
{
  this->triangles = triangles;
  
  // Set the material of each triangle to the material of the mesh
  for (Triangle &triangle : this->triangles)
  {
    triangle.material = material;
  }
}

Mesh Mesh::fromJson(const nlohmann::json &json_data)
{
  Point3f center = Point3f(0.f, 0.f, 0.f);
  float scale = 1.f;
  std::string filename;

  if (json_data.contains("model"))
  {
    filename = json_data["model"];
  }
  else
  {
    throw std::runtime_error("Mesh must be loaded from a Wavefront OBJ model file.");
  }
  std::vector<Triangle> triangles = OBJ::loadObj(filename, center, scale);

  if (json_data.contains("center"))
  {
    center = json_data["center"];
  }

  if (json_data.contains("scale"))
  {
    scale = json_data["scale"];
  }

  std::optional<Material> material;
  if (json_data.contains("material"))
  {
    material = Material::fromJson(json_data["material"]);
  }

  return Mesh(center, triangles, material);
}

std::optional<Intersection> Mesh::intersect(const Ray ray, float minDepth, float maxDepth) const
{
  // Intersect the ray with each triangle in the mesh
  std::optional<Intersection> closest_intersection;
  for (Triangle triangle : triangles)
  {
    std::optional<Intersection> intersection = triangle.intersect(ray, minDepth, maxDepth);
    if (intersection.has_value())
    {
      if (!closest_intersection.has_value() || intersection->distance < closest_intersection->distance)
      {
        closest_intersection = intersection;
      }
    }
  }

  return closest_intersection;
}
