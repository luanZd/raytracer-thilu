#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>
#include <vector>
#include <sstream>
#include <glm/vec3.hpp>

using Color = glm::vec3;

namespace Util {
    int parse_int(const std::string& value);
    float parse_float(const std::string& value);
    bool parse_bool(const std::string& value);
    Color parse_color(const std::string& value);
    std::vector<float> parse_floats(const std::string& value);
}

#endif