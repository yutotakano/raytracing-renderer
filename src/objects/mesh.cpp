#include "mesh.h"
#include "../io/obj.h"

Mesh::Mesh(Point3f center, std::vector<Triangle> triangles, std::optional<Material> material) : Object(material), center(center)
{
  // Set the material of each triangle to the material of the mesh
  for (auto &triangle : triangles)
  {
    this->triangles.push_back(std::static_pointer_cast<Object>(std::make_shared<Triangle>(triangle)));
  }

  // Set up a BVH for the mesh if it's quite a large number of triangles, since
  // it can be expensive to intersect with each triangle individually. The
  // global BVH is only used on the mesh as a whole.
  if (this->triangles.size() > 3)
  {
    this->bvh = BVH(this->triangles, std::vector<std::shared_ptr<Light>>());
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
  
  if (json_data.contains("center"))
  {
    center = json_data["center"];
  }

  if (json_data.contains("scale"))
  {
    scale = json_data["scale"];
  }

  std::vector<Triangle> triangles = OBJ::loadObj(filename, center, scale);

  std::optional<Material> material;
  if (json_data.contains("material"))
  {
    material = Material::fromJson(json_data["material"]);
  }

  return Mesh(center, triangles, material);
}

std::optional<Intersection> Mesh::intersect(const Ray &ray, float minDepth, float maxDepth) const
{
  if (bvh.has_value())
  {
    return bvh->intersect(ray, minDepth, maxDepth);
  }

  // Intersect the ray with each triangle in the mesh
  std::optional<Intersection> closest_intersection;
  for (const auto &triangle : triangles)
  {
    std::optional<Intersection> intersection = triangle->intersect(ray, minDepth, maxDepth);
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

BoundingBox Mesh::getBoundingBox() const
{
  if (bvh.has_value())
  {
    return bvh->getBoundingBox();
  }

  // Get the bounding box of each triangle in the mesh
  std::optional<BoundingBox> bounding_box;
  for (const auto &triangle : triangles)
  {
    // As there is no default constructor that we can define for a bounding box,
    // we construct it from the first triangle in the mesh
    if (!bounding_box.has_value())
    {
      bounding_box = triangle->getBoundingBox();
      continue;
    }

    bounding_box = bounding_box->merge(triangle->getBoundingBox());
  }

  if (!bounding_box.has_value())
  {
    throw std::runtime_error("Mesh has triangles to calculate a bounding box for.");
  }

  return bounding_box.value();
}
