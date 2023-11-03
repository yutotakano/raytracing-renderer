#ifndef PINHOLE_H
#define PINHOLE_H

#include "../vector.h"
#include "camera.h"

/**
 * @brief Pinhole camera model.
 */
class Pinhole : public Camera {
public:
  Pinhole(Vector2f filmSize, Vector3f position, Vector3f lookAt, Vector3f upVector, float fov, float exposure);
  static Pinhole fromJson(const nlohmann::json &json);

  Ray generateRay(Point2f filmPosition) const;

private:
  Vector3f position;
  Vector3f lookAt;
  Vector3f upVector;
  float fov;
  float exposure;
};

#endif // PINHOLE_H
