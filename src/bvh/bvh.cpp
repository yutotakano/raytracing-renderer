#include "bvh.h"
#include <iostream>

BVH::BVH(std::vector<std::shared_ptr<Object>> objects,
         std::vector<std::shared_ptr<Light>> lights)
{
  std::vector<std::shared_ptr<BVHNode>> nodes;

  // For each object, create a BVHNode and add it to the nodes vector
  for (auto &object : objects)
  {
    nodes.push_back(std::make_shared<BVHNode>(BVHNode(object->getBoundingBox(), object)));
  }

  // Construct the BVH tree
  root = constructBVHTree(nodes, 0, nodes.size());
}

std::shared_ptr<BVHNode> BVH::constructBVHTree(std::vector<std::shared_ptr<BVHNode>> &nodes, int start, int end)
{
  // If there is only one node, return it
  if (start == end - 1)
  {
    return nodes[start];
  }

  // If there are two nodes, return a node with the two nodes as children
  if (start == end - 2)
  {
    return std::make_shared<BVHNode>(nodes[start], nodes[start + 1]);
  }

  // Otherwise, split the nodes into two groups and recursively construct the
  // tree. The index to split at will be calculated by finding the axis with
  // the largest difference. We can do this by merging all the bounding boxes
  // into one and finding the largest axis.

  // We are guaranteed that there are at more than 2 nodes, so assign the first
  // bounding box (we don't have a default constructor for BoundingBox).
  BoundingBox box = nodes[start]->getBoundingBox();
  for (int i = start + 1; i < end; i++)
  {
    box = box.merge(nodes[i]->getBoundingBox());
  }

  // Find the largest axis
  Vector3f size = box.getMax() - box.getMin();
  int largest_axis = 0;
  if (size.y() > size.x())
  {
    largest_axis = 1;
  }
  if (size.z() > size.y() && size.z() > size.x())
  {
    largest_axis = 2;
  }

  // Split in the middle by that axis
  float split = (box.getMin()[largest_axis] + box.getMax()[largest_axis]) / 2.f;

  // Partition the nodes into two groups based on the split, essentially doing
  // a quicksort partition.
  int mid = start;
  for (int i = start; i < end; i++)
  {
    if (nodes[i]->getBoundingBox().getCenter()[largest_axis] < split)
    {
      std::swap(nodes[i], nodes[mid]);
      mid++;
    }
  }

  // If the split is invalid (e.g. if all centroids were on one side of the split
  // value, or if everything is at the same place), just split in the middle
  if (mid == start || mid == end)
  {
    mid = (start + end) / 2;
  }

  auto left = constructBVHTree(nodes, start, mid);
  auto right = constructBVHTree(nodes, mid, end);
  return std::make_shared<BVHNode>(left, right);
}

std::optional<Intersection> BVH::intersect(const Ray &ray, float minDepth, float maxDepth) const
{
  return root->intersect(ray, minDepth, maxDepth);
}

BoundingBox BVH::getBoundingBox() const
{
  return root->getBoundingBox();
}
