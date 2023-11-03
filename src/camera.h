#ifndef CAMERA_H
#define CAMERA_H

#include "vector.h"
#include "ray.h"

class Camera {
public:
  Camera(Vector2f filmSize) : filmSize(filmSize) {};
  virtual ~Camera() = default;

  static std::unique_ptr<Camera> fromJson(const nlohmann::json &json);
  virtual Ray generateRay(Point2f filmPosition) const = 0;
  Vector2f getFilmSize() const;

protected:
  Vector2f filmSize;
};

#endif // CAMERA_H
