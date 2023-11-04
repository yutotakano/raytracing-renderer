#include "arguments.h"
#include <vector>
#include <stdexcept>
#include <filesystem>
#include <iostream>

Arguments::Arguments(int argc, char *argv[])
{
  std::vector<std::string> arguments(argv, argv + argc);

  for (int i = 0; i < argc; i++)
  {
    if (arguments[i].find(".json"))
    {
      input_file = arguments[i];
    }
    else if (arguments[i] == "--no-preview")
    {
      no_preview = true;
    }
    else if (arguments[i] == "--output" || arguments[i] == "-o")
    {
      i++;
      if (i >= argc)
      {
        throw std::invalid_argument("Missing --output value.");
      }
      output_file = arguments[i];
    }
  }

  if (input_file.empty())
  {
    throw std::invalid_argument("An input file has to be specified.");
  }

  if (output_file.empty())
  {
    std::filesystem::path input_path(input_file);
    output_file = input_path.replace_extension(std::filesystem::path(".ppm")).u8string();
  }
}
