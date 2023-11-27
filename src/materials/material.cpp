#include "material.h"
#include "../io/ppm.h"

Material::Material(float ks, float kd, float specularExponent, Color3f diffuseColor, Color3f specularColor, bool isReflective, float reflectivity, bool isRefractive, float refractiveIndex, Color3f emittance, std::optional<TextureMap> texture) : ks(ks), kd(kd), specularExponent(specularExponent), diffuseColor(diffuseColor), specularColor(specularColor), isReflective(isReflective), reflectivity(reflectivity), isRefractive(isRefractive), refractiveIndex(refractiveIndex), emittance(emittance), texture(texture)
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

  Color3f emittance = Color3f(0.f, 0.f, 0.f);
  if (json_data.contains("emittance"))
  {
    emittance = json_data["emittance"];
  }

  std::optional<TextureMap> texture = std::nullopt;
  if (json_data.contains("texture"))
  {
    std::pair<std::vector<Color3f>, Vector2f> data = PPM::readPPM(json_data["texture"]);
    PPM::writePPM(data.first, data.second, "test.ppm");
    texture = TextureMap(data.first, data.second);
  }
  
  return Material(ks, kd, specularExponent, diffuseColor, specularColor, isReflective, reflectivity, isRefractive, refractiveIndex, emittance, texture);
}

std::tuple<Color3f, float, Vector3f> Material::sample(Vector3f wo, Point2f uv, Random &sampler) const
{
  if (isReflective)
  {
    float test = sampler.get1D();
    if (test < reflectivity)
    {
      // Mirror material
      Vector3f wi = Vector3f(-wo.x(), -wo.y(), wo.z());
      return std::make_tuple(diffuseColor, 1.0f, wi);
    }
  }
  if (isRefractive)
  {
    // Glass material
    float cosTheta = wo.z();
    float eta = refractiveIndex;
    if (cosTheta < 0.0f)
    {
      cosTheta = -cosTheta;
      eta = 1.0f / eta;
    }
    float k = 1.0f - eta * eta * (1.0f - cosTheta * cosTheta);
    if (k < 0.0f)
    {
      // Total internal reflection
      Vector3f wi = Vector3f(-wo.x(), -wo.y(), wo.z());
      return std::make_tuple(diffuseColor, 0.0f, wi);
    }
    else
    {
      // Refraction
      float cosThetaT = std::sqrt(k);
      Vector3f wi = Vector3f(-eta * wo.x(), -eta * wo.y(), cosThetaT);
      return std::make_tuple(diffuseColor, 0.0f, wi);
    }
  }

  // Return the BSDF, the PDF for it, and the incoming direction of light where
  // we should send a ray next. The PDF and direction should be found by
  // sampling over the hemisphere using the cosine distribution.

  // If the material has a texture, use it to find the diffuse color.
  Color3f diffuseColor = this->diffuseColor;
  if (texture.has_value())
  {
    diffuseColor = texture->getColorAtUV(uv);
  }

  // Calculate the uniform direction on a hemisphere.
  Point2f rand = sampler.get2D();
  float theta = 2.0f * M_PI * rand.x();
  float phi = std::acos(1.0f - rand.y());
  // cosine-weighted
  // float phi = std::acos(std::sqrt(rand.y()));

  Vector3f direction = Vector3f(std::sin(phi) * std::cos(theta), std::sin(phi) * std::sin(theta), std::cos(phi));

  return std::make_tuple(diffuseColor / M_PI, 1.0f / (2.0f * M_PI), direction);
}

std::tuple<Color3f, float> Material::eval(Vector3f wo, Vector3f wi, Point2f uv) const
{
  if (isReflective)
  {
    // Mirror material, pdf of 1 if the wi is the perfect reflection of wo.
    // otherwise 0
    Vector3f reflected = Vector3f(-wo.x(), -wo.y(), wo.z());
    float pdf = (wi == reflected) ? 1.0f : 0.0f;
    return std::make_tuple(specularColor, pdf);
  }
  if (isRefractive)
  {
    // Mirror material
    return std::make_tuple(Color3f(0.f, 0.f, 0.f), 0.0f);
  }
  // If the material has a texture, use it to find the diffuse color.
  Color3f diffuseColor = this->diffuseColor;
  if (texture.has_value())
  {
    diffuseColor = texture->getColorAtUV(uv);
  }

  // Calculate the cosine of the angle between the normal and the incoming
  // direction.
  float cosTheta = wi.dot(Vector3f(0.0f, 0.0f, 1.0f));

  // Return the BSDF and the PDF for it.
  if (cosTheta > 0.f)
  {
    return std::make_tuple(diffuseColor / M_PI, 1.0f / (2.0f * M_PI));
  }
  else
  {
    return std::make_tuple(Color3f(0.f, 0.f, 0.f), 0.f);
  }
}
