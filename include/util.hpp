#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>
#include <sstream>
#include <glm/vec3.hpp>

using Color = glm::vec3;

namespace Util {
    
    // Converte um texto ("800") num inteiro (800)
    int parse_int(const std::string& value);

    // Converte um texto ("3.14") num float (3.14f)
    float parse_float(const std::string& value);

    // Converte texto ("255 128 0") numa Color normalizada
    Color parse_color(const std::string& value);

}

#endif