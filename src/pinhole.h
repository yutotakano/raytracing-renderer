#include "vector.h"
#include "camera.h"

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