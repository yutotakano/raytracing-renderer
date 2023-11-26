#ifndef OBJ_H
#define OBJ_H

#include <vector>
#include "../vector.h"
#include "../objects/triangle.h"

/**
 * @brief Represents operations to be done with a Wavefront OBJ file.
 */
class OBJ
{
public:
  /**
   * @brief Loads a Wavefront OBJ file into a vector of triangles.
   * @param filename The name of the file to load.
   * @param center The center of the object.
   * @param scale The scale of the object.
   * @return A vector of triangles.
   */
  static std::vector<Triangle> loadObj(std::string filename, Point3f center, float scale);
};

#endif // OBJ_H
