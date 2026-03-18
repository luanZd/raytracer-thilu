#include <string>
#include <vector>

struct RunningOpt
{
  bool help = false;
  std::string outfile;
  bool quick_render = false;
  std::vector<float> crop_window;
};
