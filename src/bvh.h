#ifndef BVH_H
#define BVH_H

#include "object.h"
#include "light.h"

class BVH {
public:
  BVH(std::vector<std::shared_ptr<Object>> objects,
      std::vector<std::shared_ptr<Light>> lights);
};

#endif // BVH_H
