#ifndef RT3_HPP
#define RT3_HPP

#include <string>
#include <vector>

struct RunningOpt
{
  std::string infile;
  bool help = false;
  std::string outfile;
  bool quick_render = false;
  std::vector<float> crop_window;
};

#endif 