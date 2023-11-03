#ifndef MATERIAL_H
#define MATERIAL_H

#include "../vector.h"
#include <json/json.hpp>

/**
 * @brief Material properties for an object.
 */
class Material
{
public:
  Material(float ks, float kd, float specularExponent, Color3f diffuseColor, Color3f specularColor, bool isReflective, float reflectivity, bool isRefractive, float refractiveIndex);

  static Material fromJson(const nlohmann::json &json_data);

  float ks;
  float kd;
  float specularExponent;
  Color3f diffuseColor;
  Color3f specularColor;
  bool isReflective;
  float reflectivity;
  bool isRefractive;
  float refractiveIndex;
};

#endif // MATERIAL_H
