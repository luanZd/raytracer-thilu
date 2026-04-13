#ifndef RT3_HPP
#define RT3_HPP

#include <string>
#include <vector>

using Point3 = glm::vec3;  
using Vector3 = glm::vec3;

struct RunningOpt
{
  std::string infile;
  bool help = false;
  std::string outfile;
  bool quick_render = false;
  std::vector<float> crop_window;
};

#endif 