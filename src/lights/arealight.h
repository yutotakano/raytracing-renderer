#ifndef AREALIGHT_H
#define AREALIGHT_H

#include "light.h"
#include "../vector.h"
#include "../objects/object.h"

class AreaLight : public Light
{
public:
  AreaLight(Point3f position, Color3f intensity, std::shared_ptr<Object> shape);
  static AreaLight fromJson(const nlohmann::json &json_data);

  std::shared_ptr<Object> getShape() const { return shape; }

private:
  std::shared_ptr<Object> shape;
};

#endif // AREALIGHT_H
