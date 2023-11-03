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
    file << data[i].x() << data[i].y() << data[i].z();
  }

  file.close();
};
