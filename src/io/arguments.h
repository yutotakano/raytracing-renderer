#include <string>

class Arguments
{
public:
  Arguments(int argc, char *argv[]);

  std::string input_file;
  bool no_preview = false;
  bool binary = false;
  std::string output_file;
};
