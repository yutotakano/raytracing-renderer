#include <vector>
#include "../vector.h"

class PPM {
public:
  static void writePPM(const std::vector<Color3f>& data, Vector2f imageSize, const std::string& filename);
  static std::pair<std::vector<Color3f>, Vector2f> readPPM(const std::string& filename);
};
