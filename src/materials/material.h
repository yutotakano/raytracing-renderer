#ifndef MATERIAL_H
#define MATERIAL_H

#include "../vector.h"
#include "../materials/texture.h"
#include "../random.h"
#include <optional>
#include <json/json.hpp>

/**
 * @brief Material properties for an object.
 */
class Material
{
public:
  Material(float ks, float kd, float specularExponent, Color3f diffuseColor, Color3f specularColor, bool isReflective, float reflectivity, bool isRefractive, float refractiveIndex, Color3f emittance, std::optional<TextureMap> texture = std::nullopt);

  static Material fromJson(const nlohmann::json &json_data);

  std::tuple<Color3f, float, Vector3f> sample(Vector3f wo, Point2f uv, Random &sampler) const;

  std::tuple<Color3f, float> eval(Vector3f wo, Vector3f wi, Point2f uv) const;

  float ks;
  float kd;
  float specularExponent;
  Color3f diffuseColor;
  Color3f specularColor;
  bool isReflective;
  float reflectivity;
  bool isRefractive;
  float refractiveIndex;
  Color3f emittance;
  std::optional<TextureMap> texture;
};

#endif // MATERIAL_H
