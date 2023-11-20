#include "tracer.h"
#include "binary.h"
#include "phong.h"

Tracer::Tracer()
{
}

std::unique_ptr<Tracer> Tracer::fromJson(const nlohmann::json &json_data)
{
  std::string rendermode = json_data["rendermode"];

  if (rendermode == "binary")
  {
    return std::make_unique<Binary>(Binary::fromJson(json_data));
  }
  else if (rendermode == "phong")
  {
    return std::make_unique<Phong>(Phong::fromJson(json_data));
  }
  else
  {
    throw std::runtime_error("Invalid object type specified in JSON file.");
  }
}
