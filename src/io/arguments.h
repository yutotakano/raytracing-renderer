#include <string>

class Arguments
{
public:
  Arguments(int argc, char *argv[]);

  std::string input_file;
  bool no_preview = false;
  std::string output_file;
  std::string tonemap = "aces_fitted";
};
