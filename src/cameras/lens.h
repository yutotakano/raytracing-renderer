#ifndef LENS_H
#define LENS_H

#include "../vector.h"
#include "camera.h"

/**
 * @brief Lens camera model for physically accurate renders.
 */
class Lens : public Camera {
public:
  Lens(Vector2f filmSize, Vector3f position, Vector3f lookAt, Vector3f upVector, float fov, float exposure);
  static Lens fromJson(const nlohmann::json &json);

  Ray generateRay(Point2f filmPosition, Random &sampler) const override;

  float getExposure() const;

private:
  Vector3f position;
  Vector3f lookAt;
  Vector3f upVector;
  float fov;
  float exposure;
};

#endif // LENS_H
