#ifndef MATERIAL_H
#define MATERIAL_H

#include "../vector.h"
#include "../texture.h"
#include <optional>
#include <json/json.hpp>

/**
 * @brief Material properties for an object.
 */
class Material
{
public:
  Material(float ks, float kd, float specularExponent, Color3f diffuseColor, Color3f specularColor, bool isReflective, float reflectivity, bool isRefractive, float refractiveIndex, std::optional<TextureMap> texture = std::nullopt);

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
  std::optional<TextureMap> texture;
};

#endif // MATERIAL_H
