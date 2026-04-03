#include "util.hpp"
#include <algorithm> // Para o tolower no bool

namespace Util {

    int parse_int(const std::string& value) {
        return std::stoi(value);
    }

    float parse_float(const std::string& value) {
        return std::stof(value);
    }

    bool parse_bool(const std::string& value) {
        std::string val = value;
        std::transform(val.begin(), val.end(), val.begin(), ::tolower);
        return (val == "true" || val == "1" || val == "on");
    }

    Color parse_color(const std::string& value) {
        std::stringstream ss(value);
        int r = 0, g = 0, b = 0;
        if (ss >> r >> g >> b) {
            return Color(r / 255.0f, g / 255.0f, b / 255.0f);
        }
        return Color(0.0f, 0.0f, 0.0f); 
    }

    std::vector<float> parse_floats(const std::string& value) {
        std::vector<float> result;
        std::stringstream ss(value);
        float val;
        while (ss >> val) {
            result.push_back(val);
        }
        return result;
    }
}