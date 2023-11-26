#include "ppm.h"
#include <iostream>
#include <fstream>

void PPM::writePPM(const std::vector<Color3f>& data, Vector2f imageSize, const std::string& filename)
{
  std::ofstream file(filename, std::ios::out | std::ios::binary);
  if (!file.is_open()) {
    std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
    return;
  }

  const int width = imageSize.x();
  const int height = imageSize.y();

  file << "P6\n" << width << " " << height << "\n255\n";

  for (int i = 0; i < width * height; i++) {
    file << static_cast<unsigned char>(data[i].x() * 255);
    file << static_cast<unsigned char>(data[i].y() * 255);
    file << static_cast<unsigned char>(data[i].z() * 255);
  }

  file.close();
};

std::pair<std::vector<Color3f>, Vector2f> PPM::readPPM(const std::string& filename)
{
  std::ifstream file(filename, std::ios::in | std::ios::binary);
  if (!file.is_open()) {
    std::cerr << "Error: Could not open file " << filename << " for reading." << std::endl;
    return {};
  }

  std::string magicNumber;
  int width, height, maxValue;
  file >> magicNumber >> width >> height >> maxValue >> std::ws;

  float maxValueFloat = static_cast<float>(maxValue);

  if (magicNumber != "P6") {
    std::cerr << "Error: Invalid PPM file format." << std::endl;
    return {};
  }

  Vector2f imageSize(width, height);

  std::vector<Color3f> data(width * height);

  for (int i = 0; i < width * height; i++) {
    unsigned char r, g, b;
    file.read(reinterpret_cast<char*>(&r), sizeof(unsigned char));
    file.read(reinterpret_cast<char*>(&g), sizeof(unsigned char));
    file.read(reinterpret_cast<char*>(&b), sizeof(unsigned char));

    data[i] = Color3f(r / maxValueFloat, g / maxValueFloat, b / maxValueFloat);
  }

  file.close();

  return std::make_pair(data, imageSize);
}
