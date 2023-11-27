#include "lens.h"
#include <iostream>

Lens::Lens(Vector2f filmSize, Vector3f position, Vector3f lookAt, Vector3f upVector, float fov, float exposure, float aperture) : Camera(filmSize), position(position), lookAt(lookAt), upVector(upVector), fov(fov), exposure(exposure), aperture(aperture) {};

Lens Lens::fromJson(const nlohmann::json &json) {
  return Lens(Vector2f(json["width"], json["height"]), json["position"], json["lookAt"], json["upVector"], json["fov"], json["exposure"], json["aperture"]);
}

Ray Lens::generateRay(Point2f filmPosition, Random &sampler) const {
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

  // Jitter the film position for anti-aliasing (pixel sampling)
  Point2f jittered_filmPosition = filmPosition + sampler.get2D() - Vector2f(0.5f, 0.5f);

  // direction is the direction from camera origin to the filmPosition
  Vector3f direction = u * (1.0f - jittered_filmPosition.x() / filmSize.x() - 0.5f) * 2.0f * halfWidth + v * (1.0f - jittered_filmPosition.y() / filmSize.y() - 0.5f) * 2.0f * halfHeight - w;

  // Lens sampling
  float lensRadius = aperture / 2.0f;
  Point2f lensSample = sampler.get2D() * lensRadius;

  // Keep focus point of original direction so we can shoot new ray to it
  float focusDistance = (lookAt - position).length();
  Point3f focusPoint = position + direction.normalized() * focusDistance;

  // New direction from lens sample to focus point
  Vector3f newDirection = (focusPoint - (position + u * lensSample.x() + v * lensSample.y())).normalized();
  return Ray(position + u * lensSample.x() + v * lensSample.y(), newDirection);
}

float Lens::getExposure() const {
  return exposure;
}
