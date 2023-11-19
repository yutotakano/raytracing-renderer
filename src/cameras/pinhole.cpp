#include "pinhole.h"

Pinhole::Pinhole(Vector2f filmSize, Vector3f position, Vector3f lookAt, Vector3f upVector, float fov, float exposure) : Camera(filmSize), position(position), lookAt(lookAt), upVector(upVector), fov(fov), exposure(exposure) {};

Pinhole Pinhole::fromJson(const nlohmann::json &json) {
  return Pinhole(Vector2f(json["width"], json["height"]), json["position"], json["lookAt"], json["upVector"], json["fov"], json["exposure"]);
}

Ray Pinhole::generateRay(Point2f filmPosition) const {
  // filmPosition is in [0, filmSize.x] x [0, filmSize.y]
  float aspectRatio = filmSize.x() / filmSize.y();
  float halfWidth = std::tan(fov / 2.0f);
  float halfHeight = halfWidth / aspectRatio;

  // w is the direction from camera origin to lookAt
  Vector3f w = (position - lookAt).normalized();
  // u is the direction from camera origin to the left of the image
  Vector3f u = upVector.cross(w).normalized();
  // v is the direction from camera origin to the top of the image, perpendicular to u and w
  // This can be different from the upVector if the upVector is not perpendicular to w
  Vector3f v = w.cross(u);

  // direction is the direction from camera origin to the filmPosition
  Vector3f direction = u * (filmPosition.x() / filmSize.x() - 0.5f) * 2.0f * halfWidth + v * (filmPosition.y() / filmSize.y() - 0.5f) * 2.0f * halfHeight - w;
  return Ray(position, direction.normalized());
}
