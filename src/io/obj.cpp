#include "obj.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::vector<Triangle> OBJ::loadObj(std::string filename, Point3f center, float scale)
{
  std::vector<Triangle> triangles;
  std::vector<Point3f> vertices;
  std::vector<Vector3f> normals;
  std::vector<Point3f> texCoords;

  // Open the object file
  std::ifstream file(filename);
  if (!file.is_open())
  {
    // Handle file opening error
    std::cerr << "Error opening file: " << filename << std::endl;
    return triangles;
  }

  std::string line;
  while (std::getline(file, line))
  {
    std::istringstream iss(line);
    std::string type;
    iss >> type;

    if (type == "v")
    {
      // Parse vertex coordinates
      float x, y, z;
      iss >> x >> y >> z;
      // Create a vertex object and add it to the vertices vector
      vertices.push_back(Point3f(x, y, z) * scale + center);
    }
    else if (type == "vn")
    {
      // Parse vertex normal coordinates
      float nx, ny, nz;
      iss >> nx >> ny >> nz;
      // Create a normal vector object and add it to the normals vector
      normals.push_back(Vector3f(nx, ny, nz).normalized());
    }
    else if (type == "vt")
    {
      // Parse texture coordinates
      float u, v;
      iss >> u >> v;
      // Parse the w coordinate if it exists, otherwise if the line ends without it,
      // leave it as 0
      float w = 0.0f;
      if (iss >> w)
      {
        // Do nothing
      }

      // Create a texture coordinate object and add it to the texCoords vector
      texCoords.push_back(Point3f(u, v, w));
    }
    else if (type == "f")
    {
      // Parse face indices
      std::string v1, v2, v3;
      iss >> v1 >> v2 >> v3;

      // Extract vertex, normal, and texture coordinate indices
      int vIndex1, vIndex2, vIndex3;
      int nIndex1 = -1, nIndex2 = -1, nIndex3 = -1;
      int tIndex1 = -1, tIndex2 = -1, tIndex3 = -1;

      // Check the number of slashes in the string
      if (std::count(v1.begin(), v1.end(), '/') == 2)
      {
        sscanf(v1.c_str(), "%d/%d/%d", &vIndex1, &tIndex1, &nIndex1);
        sscanf(v2.c_str(), "%d/%d/%d", &vIndex2, &tIndex2, &nIndex2);
        sscanf(v3.c_str(), "%d/%d/%d", &vIndex3, &tIndex3, &nIndex3);

        triangles.push_back(Triangle(
          vertices[vIndex1 - 1], vertices[vIndex2 - 1], vertices[vIndex3 - 1],
          texCoords[tIndex1 - 1], texCoords[tIndex2 - 1], texCoords[tIndex3 - 1],
          normals[nIndex1 - 1], normals[nIndex2 - 1], normals[nIndex3 - 1],
          std::nullopt));
      }
      else if (std::count(v1.begin(), v1.end(), '/') == 1)
      {
        sscanf(v1.c_str(), "%d/%d", &vIndex1, &tIndex1);
        sscanf(v2.c_str(), "%d/%d", &vIndex2, &tIndex2);
        sscanf(v3.c_str(), "%d/%d", &vIndex3, &tIndex3);

        triangles.push_back(Triangle(
          vertices[vIndex1 - 1], vertices[vIndex2 - 1], vertices[vIndex3 - 1],
          texCoords[tIndex1 - 1], texCoords[tIndex2 - 1], texCoords[tIndex3 - 1],
          std::nullopt));
      }
      else
      {
        sscanf(v1.c_str(), "%d", &vIndex1);
        sscanf(v2.c_str(), "%d", &vIndex2);
        sscanf(v3.c_str(), "%d", &vIndex3);

        triangles.push_back(Triangle(
          vertices[vIndex1 - 1], vertices[vIndex2 - 1], vertices[vIndex3 - 1],
          std::nullopt));
      }
}
  }

  // Close the object file
  file.close();

  return triangles;
}
