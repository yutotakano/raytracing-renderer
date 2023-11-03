#ifndef EIGEN_JSON_H
#define EIGEN_JSON_H

#include "aliases.h"
#include <json/json.hpp>

namespace nlohmann {
  template <> struct adl_serializer<Vector3f> {
    static void to_json(json& j, const Vector3f& opt) {
      j = {opt.x(), opt.y(), opt.z()};
    }

    static void from_json(const json& j, Vector3f& opt) {
      opt = Vector3f(j[0], j[1], j[2]);
    }
  };
}

#endif // EIGEN_JSON_H
