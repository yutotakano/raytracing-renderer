#ifndef BVH_H
#define BVH_H

#include "objects/object.h"
#include "lights/light.h"

class BVH {
public:
  BVH(std::vector<std::shared_ptr<Object>> objects,
      std::vector<std::shared_ptr<Light>> lights);
};

#endif // BVH_H
