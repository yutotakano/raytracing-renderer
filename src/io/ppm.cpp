#include "ppm.h"
#include <iostream>
#include <fstream>

void PPM::writePPM(const std::vector<Color3f>& data, Vector2f imageSize, const std::string& filename) {
  std::ofstream file(filename, std::ios::out | std::ios::binary);
  if (!file.is_open()) {
    std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
    return;
  }

  const int width = imageSize.x();
  const int height = imageSize.y();

  file << "P6\n" << width << " " << height << "\n255\n";

  for (int i = 0; i < width * height; i++) {
    
    // Generated from prompt:
    // Output to file stream a sequence of three bytes, for data[i].x(), y() and z(), which are each to be be multiplied to be in the range [0x00, 0xff] from [0,1]
    file << static_cast<char>(data[i].x() * 255);
    file << static_cast<char>(data[i].y() * 255);
    file << static_cast<char>(data[i].z() * 255);
  }

  file.close();
};
