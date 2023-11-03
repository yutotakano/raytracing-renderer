#include "camera.h"
#include "pinhole.h"

std::unique_ptr<Camera> Camera::fromJson(const nlohmann::json &json) {
  std::string type = json["type"];
  if (type == "pinhole") {
    return std::make_unique<Pinhole>(Pinhole::fromJson(json));
  } else {
    throw std::runtime_error("Unknown camera type: " + type);
  }
}

Vector2f Camera::getFilmSize() const {
  return filmSize;
}
