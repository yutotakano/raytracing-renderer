#include "pinhole.h"

Pinhole::Pinhole(Vector2f filmSize, Vector3f position, Vector3f lookAt, Vector3f upVector, float fov, float exposure) : Camera(filmSize), position(position), lookAt(lookAt), upVector(upVector), fov(fov), exposure(exposure) {};

Pinhole Pinhole::fromJson(const nlohmann::json &json) {
  return Pinhole(Vector2f(json["width"], json["height"]), json["position"], json["lookAt"], json["upVector"], json["fov"], json["exposure"]);
}

Ray Pinhole::generateRay(Point2f filmPosition) const {
  Vector3f origin = position;
  Vector3f direction = Vector3f(filmPosition.x(), filmPosition.y(), -1) - position;
  return Ray(origin, direction.normalized());
}
