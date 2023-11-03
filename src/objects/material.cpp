#include "material.h"

Material::Material(float ks, float kd, float specularExponent, Color3f diffuseColor, Color3f specularColor, bool isReflective, float reflectivity, bool isRefractive, float refractiveIndex) : ks(ks), kd(kd), specularExponent(specularExponent), diffuseColor(diffuseColor), specularColor(specularColor), isReflective(isReflective), reflectivity(reflectivity), isRefractive(isRefractive), refractiveIndex(refractiveIndex)
{
}

Material Material::fromJson(const nlohmann::json &json_data)
{
  float ks = json_data["ks"];
  float kd = json_data["kd"];
  float specularExponent = json_data["specularexponent"];
  Color3f diffuseColor = json_data["diffusecolor"];
  Color3f specularColor = json_data["specularcolor"];
  bool isReflective = json_data["isreflective"];
  float reflectivity = json_data["reflectivity"];
  bool isRefractive = json_data["isrefractive"];
  float refractiveIndex = json_data["refractiveindex"];

  return Material(ks, kd, specularExponent, diffuseColor, specularColor, isReflective, reflectivity, isRefractive, refractiveIndex);
}
