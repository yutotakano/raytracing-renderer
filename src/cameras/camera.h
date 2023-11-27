#ifndef CAMERA_H
#define CAMERA_H

#include "../vector.h"
#include "../ray.h"
#include "../random.h"

/**
 * @brief Generic camera model with a fixed film size.
 */
class Camera {
public:
  Camera(Vector2f filmSize) : filmSize(filmSize) {};
  virtual ~Camera() = default;

  static std::unique_ptr<Camera> fromJson(const nlohmann::json &json);

  /**
   * @brief Generate a ray from the camera origin through the given film
   * position, where the film position is in integer coordinates within the
   * given filmSize for this class.
   * @param filmPosition [0, filmSize.x()] x [0, filmSize.y()]
   * @param sampler Random sampler for any sampling
   * @return Ray from the camera origin through the given film position
   */
  virtual Ray generateRay(Point2f filmPosition, Random &sampler) const = 0;

  /**
   * @brief Get the film size for this camera.
   * @return Film size in pixels
   */
  Vector2f getFilmSize() const;

  /**
   * @brief Get the exposure for this camera, used for tonemapping.
   * @return Exposure bias
   */
  float getExposure() const { return 1.0f; }

protected:
  Vector2f filmSize;
};

#endif // CAMERA_H
