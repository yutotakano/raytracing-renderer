#include <vector>
#include "../vector.h"

class PPM {
public:
  static void writePPM(const std::vector<Color3f>& data, Vector2f imageSize, const std::string& filename);
};
